"""
spc2it.py
=========
Converte um arquivo .spc para .it (Impulse Tracker) com exatamente 8 canais.
Pasta padrao: C:\\snesdev\\snes-examples\\games\\FinalFantasy\\res\\music

Uso:
    python spc2it.py <nome_do_arquivo>
    python spc2it.py 07a_Main_Theme
    python spc2it.py 07a_Main_Theme.spc
"""

import sys
import os
import struct

MUSIC_DIR = r"C:\snesdev\snes-examples\games\FinalFantasy\res\music"
MAX_BYTES = 54 * 1024

# ─────────────────────────────────────────────────────────────────────────────
# BRR → PCM
# ─────────────────────────────────────────────────────────────────────────────

def extract_brr(ram, addr):
    brr = bytearray()
    visited = set()
    while addr < len(ram):
        if addr in visited:
            break
        visited.add(addr)
        if addr + 9 > len(ram):
            break
        header = ram[addr]
        brr   += ram[addr:addr+9]
        if header & 0x01:
            break
        addr += 9
    return bytes(brr)


def brr_to_pcm(brr_data):
    pcm = []
    p1 = p2 = 0
    i = 0
    while i + 9 <= len(brr_data):
        header   = brr_data[i]
        shift    = (header >> 4) & 0x0F
        filter_n = (header >> 2) & 0x03
        for b in range(8):
            byte = brr_data[i + 1 + b]
            for nibble in ((byte >> 4) & 0x0F, byte & 0x0F):
                if nibble >= 8:
                    nibble -= 16
                if shift > 12:
                    raw = nibble >> 3
                else:
                    raw = nibble << shift
                if   filter_n == 0: s = raw
                elif filter_n == 1: s = raw + p1 - (p1 >> 4)
                elif filter_n == 2: s = raw + 2*p1 - (p1 >> 3) - p2 + (p2 >> 4)
                else:               s = raw + 2*p1 - (3*p1 >> 4) - p2 + (3*p2 >> 5)
                s = max(-32768, min(32767, s))
                pcm.append(s)
                p2, p1 = p1, s
        i += 9
    return pcm


# ─────────────────────────────────────────────────────────────────────────────
# Leitura do SPC
# ─────────────────────────────────────────────────────────────────────────────

def load_spc(path):
    with open(path, 'rb') as f:
        data = f.read()
    assert data[:27] == b'SNES-SPC700 Sound File Data', "Nao e um arquivo SPC valido"
    ram   = data[256:256+65536]
    dsp   = data[65792:65792+128]
    title = data[46:77].decode('ascii', errors='replace').rstrip('\x00 ')
    game  = data[77:108].decode('ascii', errors='replace').rstrip('\x00 ')
    return ram, dsp, title, game


def parse_channels(ram, dsp):
    DIR      = dsp[0x5D] << 8
    channels = []
    for ch in range(8):
        b    = ch * 0x10
        srcn = dsp[b + 0x04]
        de   = DIR + srcn * 4
        if de + 3 < len(ram):
            sample_addr = ram[de]   | (ram[de+1] << 8)
            loop_addr   = ram[de+2] | (ram[de+3] << 8)
        else:
            sample_addr = loop_addr = 0
        channels.append({
            'ch':          ch,
            'vol_l':       dsp[b + 0x00],
            'vol_r':       dsp[b + 0x01],
            'pitch':       dsp[b + 0x02] | (dsp[b + 0x03] << 8),
            'srcn':        srcn,
            'adsr1':       dsp[b + 0x05],
            'adsr2':       dsp[b + 0x06],
            'sample_addr': sample_addr,
            'loop_addr':   loop_addr,
        })
    return channels, DIR


def extract_samples(ram, dsp, channels):
    DIR     = dsp[0x5D] << 8
    srcns   = sorted(set(ch['srcn'] for ch in channels))
    samples = {}
    total   = 0
    for srcn in srcns:
        de = DIR + srcn * 4
        if de + 3 >= len(ram):
            continue
        sample_addr = ram[de]   | (ram[de+1] << 8)
        loop_addr   = ram[de+2] | (ram[de+3] << 8)
        brr         = extract_brr(ram, sample_addr)
        pcm         = brr_to_pcm(brr)
        loop_offset = loop_addr - sample_addr
        loop_sample = (loop_offset // 9) * 16 if loop_offset > 0 and loop_offset % 9 == 0 else 0
        available   = MAX_BYTES - total
        max_s       = available // 2
        if len(pcm) > max_s:
            pcm = pcm[:max_s]
            print(f"  AVISO: SRCN {srcn:02X} cortado para {len(pcm)} samples")
        total += len(pcm) * 2
        samples[srcn] = {'pcm': pcm, 'loop_sample': loop_sample}
        print(f"  SRCN {srcn:02X}: {len(brr)}B BRR -> {len(pcm)} samples PCM "
              f"({len(pcm)*2} bytes) loop@{loop_sample}")
    print(f"  Total: {total} bytes ({total/1024:.1f} KB)")
    return samples


# ─────────────────────────────────────────────────────────────────────────────
# Helpers de conversao
# ─────────────────────────────────────────────────────────────────────────────

def adsr_to_it(adsr1, adsr2):
    if adsr1 & 0x80:
        attack  = min(64, ((adsr1 & 0x0F) * 2 + 1) * 2)
        decay   = max(1, 64 - ((adsr1 >> 4) & 0x07) * 8)
        sustain = ((adsr2 >> 5) & 0x07) * 8
        release = max(1, 64 - (adsr2 & 0x1F) * 2)
    else:
        attack = 0; decay = 64; sustain = 64; release = 64
    return attack, decay, sustain, release


def pitch_to_c5speed(pitch_reg):
    if pitch_reg == 0:
        return 8363
    return max(256, min(65535, int(pitch_reg * 32000 / 0x1000)))


def vol_to_it(v):
    v = v if v < 128 else v - 256
    return max(0, min(64, abs(v) >> 1))


# ─────────────────────────────────────────────────────────────────────────────
# Montagem do .it
# ─────────────────────────────────────────────────────────────────────────────

def build_it(channels, samples, title):
    NUM_CH      = 8
    srcn_list   = sorted(samples.keys())
    srcn_to_idx = {s: i for i, s in enumerate(srcn_list)}
    num_instr   = len(srcn_list)
    num_samples = len(srcn_list)

    # Offsets
    orders_size    = 2
    instr_off_size  = num_instr   * 4
    sample_off_size = num_samples * 4
    pat_off_size    = 1           * 4
    base = 192 + orders_size + instr_off_size + sample_off_size + pat_off_size

    INSTR_SIZE    = 554
    SAMPLE_HDR    = 80
    instrs_start  = base
    smphdrs_start = instrs_start  + num_instr   * INSTR_SIZE
    pat_start     = smphdrs_start + num_samples  * SAMPLE_HDR

    # Header IMPM
    hdr = bytearray(192)
    hdr[0:4]   = b'IMPM'
    hdr[4:4+min(26, len(title))] = title.encode('ascii', errors='replace')[:26]
    hdr[32:34] = struct.pack('<H', 1)
    hdr[34:36] = struct.pack('<H', num_instr)
    hdr[36:38] = struct.pack('<H', num_samples)
    hdr[38:40] = struct.pack('<H', 1)
    hdr[42:44] = struct.pack('<H', 0x0214)
    hdr[44:46] = struct.pack('<H', 0x0214)
    hdr[46]    = 0x01
    hdr[48]    = 128
    hdr[49]    = 128
    hdr[50]    = 125
    hdr[51]    = 6
    for ch in range(NUM_CH):
        hdr[64  + ch] = 32
        hdr[104 + ch] = 64

    # Orders
    orders = bytes([0, 255])

    # Offsets de instrumentos
    instr_offsets = bytearray()
    for i in range(num_instr):
        instr_offsets += struct.pack('<I', instrs_start + i * INSTR_SIZE)

    # Offsets de samples
    sample_offsets = bytearray()
    for i in range(num_samples):
        sample_offsets += struct.pack('<I', smphdrs_start + i * SAMPLE_HDR)

    # Offset do padrao
    pat_offset = struct.pack('<I', pat_start)

    # Instrumentos IMPi
    def make_instrument(idx, srcn, ch_info):
        ins = bytearray(554)
        ins[0:4] = b'IMPi'
        name = f'SRCN_{srcn:02X}'.encode('ascii')
        ins[4:4+len(name)] = name
        ins[28:30] = struct.pack('<H', 128)
        att, dec, sus, rel = adsr_to_it(ch_info['adsr1'], ch_info['adsr2'])
        ins[130] = 0x03
        ins[131] = 3
        ins[132] = att;  ins[133:135] = struct.pack('<H', 0)
        ins[135] = sus;  ins[136:138] = struct.pack('<H', 10)
        ins[138] = rel;  ins[139:141] = struct.pack('<H', 20)
        smp_num = idx + 1
        for note in range(120):
            off = 256 + note * 2
            ins[off]     = note
            ins[off + 1] = smp_num
        return ins

    instr_blocks = bytearray()
    for i, srcn in enumerate(srcn_list):
        ch_info = next(c for c in channels if c['srcn'] == srcn)
        instr_blocks += make_instrument(i, srcn, ch_info)

    # Sample headers IMPs + data
    sample_hdr_list    = []
    sample_data_blocks = []

    for i, srcn in enumerate(srcn_list):
        s       = samples[srcn]
        pcm     = s['pcm']
        ch_info = next(c for c in channels if c['srcn'] == srcn)
        c5speed = pitch_to_c5speed(ch_info['pitch'])
        vol     = max(vol_to_it(ch_info['vol_l']), vol_to_it(ch_info['vol_r']))
        if vol == 0:
            vol = 64
        loop_start = s['loop_sample']
        loop_end   = len(pcm)
        has_loop   = loop_start < loop_end
        flags = 0x01 | 0x02 | (0x10 if has_loop else 0)

        h = bytearray(80)
        h[0:4]   = b'IMPS'
        name = f'SRCN_{srcn:02X}'.encode('ascii')
        h[4:4+len(name)] = name
        h[17]    = vol
        h[18]    = flags
        h[20:24] = struct.pack('<I', len(pcm))
        h[24:28] = struct.pack('<I', loop_start if has_loop else 0)
        h[28:32] = struct.pack('<I', loop_end   if has_loop else 0)
        h[32:36] = struct.pack('<I', c5speed)
        h[36:40] = struct.pack('<I', 0)
        h[40:44] = struct.pack('<I', 0)
        h[44:48] = struct.pack('<I', 0)  # placeholder

        sample_hdr_list.append(h)
        raw = bytearray()
        for v in pcm:
            raw += struct.pack('<h', v)
        sample_data_blocks.append(bytes(raw))

    # Padrao: 64 rows, row 0 tem nota C-5 em cada canal
    pat_data = bytearray()
    for ch in range(NUM_CH):
        srcn = channels[ch]['srcn']
        inst = srcn_to_idx.get(srcn, 0) + 1
        pat_data += bytes([(ch + 1) | 0x80, 0x03, 60, inst])
    pat_data += bytes([0])
    for _ in range(63):
        pat_data += bytes([0])

    pattern = struct.pack('<HHI', len(pat_data), 64, 0) + pat_data

    # Calcula offsets reais dos sample data
    offset = pat_start + len(pattern)
    for i in range(num_samples):
        sample_hdr_list[i][44:48] = struct.pack('<I', offset)
        offset += len(sample_data_blocks[i])

    smp_hdr_block = bytearray()
    for h in sample_hdr_list:
        smp_hdr_block += h

    # Junta tudo
    out  = bytes(hdr)
    out += orders
    out += bytes(instr_offsets)
    out += bytes(sample_offsets)
    out += pat_offset
    out += bytes(instr_blocks)
    out += bytes(smp_hdr_block)
    out += bytes(pattern)
    for blk in sample_data_blocks:
        out += blk

    return out


# ─────────────────────────────────────────────────────────────────────────────
# Main
# ─────────────────────────────────────────────────────────────────────────────

def main():
    if len(sys.argv) < 2:
        print("Uso: python spc2it.py <nome_do_arquivo>")
        print("Exemplo: python spc2it.py 07a_Main_Theme")
        sys.exit(1)

    name = sys.argv[1]
    if not name.lower().endswith('.spc'):
        name += '.spc'

    spc_path = os.path.join(MUSIC_DIR, name)
    it_path  = os.path.join(MUSIC_DIR, os.path.splitext(name)[0] + '.it')

    if not os.path.exists(spc_path):
        print(f"Erro: arquivo nao encontrado: {spc_path}")
        sys.exit(1)

    print(f"[1/4] Lendo SPC: {spc_path}")
    ram, dsp, title, game = load_spc(spc_path)
    print(f"      Titulo: {title}  |  Jogo: {game}")

    print(f"[2/4] Parseando canais DSP...")
    channels, DIR = parse_channels(ram, dsp)
    for ch in channels:
        print(f"      CH{ch['ch']}: SRCN={ch['srcn']:02X} pitch=0x{ch['pitch']:04X} "
              f"volL={ch['vol_l']:02X} volR={ch['vol_r']:02X}")

    print(f"[3/4] Extraindo samples BRR...")
    samples = extract_samples(ram, dsp, channels)

    print(f"[4/4] Montando .it...")
    it_data = build_it(channels, samples, title)

    with open(it_path, 'wb') as f:
        f.write(it_data)

    print(f"\nOK! Salvo em: {it_path}")
    print(f"   Tamanho: {len(it_data)} bytes ({len(it_data)/1024:.1f} KB)")
    print(f"   Canais: 8  |  Instrumentos: {len(samples)}  |  Samples: {len(samples)}")

if __name__ == "__main__":
    main()