"""
bundlePng.py
============
Extrai todas as texturas (Texture2D) de Unity AssetBundles (.bundle)
e salva como PNG na mesma pasta dos bundles.

Dependência:
    pip install UnityPy
"""

import os
import UnityPy

# ============================================================
# CONFIGURE AQUI A PASTA DOS SEUS BUNDLES
# ============================================================
BUNDLE_DIR = r"C:\snesdev\snes-examples\games\FinalFantasy\teste\FINAL FANTASY V_Data\StreamingAssets\aa\StandaloneWindows64"
# ============================================================

def extract_bundle(bundle_path, out_dir):
    env = UnityPy.load(bundle_path)
    count = 0

    # Prefixo baseado no nome do bundle (só a parte do mapa, sem o hash)
    bundle_prefix = os.path.basename(bundle_path)
    bundle_prefix = bundle_prefix.split("_assets_")[0]  # ex: map_00000, mo_ff5_b051_c00

    for path, obj in env.container.items():
        if obj.type.name != "Texture2D":
            continue
        data = obj.read()
        img = data.image

        name = os.path.basename(path)
        if not name.lower().endswith(".png"):
            name += ".png"

        # Nome final: prefixo__nome.png  ex: map_00000__wmap_chip_000.png
        final_name = f"{bundle_prefix}__{name}"
        out_path = os.path.join(out_dir, final_name)
        img.save(out_path)
        print(f"  [OK] {final_name}")
        count += 1

    return count

def main():
    if not os.path.isdir(BUNDLE_DIR):
        print(f"Pasta nao encontrada: {BUNDLE_DIR}")
        return

    bundles = sorted([
        os.path.join(BUNDLE_DIR, f)
        for f in os.listdir(BUNDLE_DIR)
        if f.endswith(".bundle")
    ])

    if not bundles:
        print("Nenhum arquivo .bundle encontrado.")
        return

    total = 0
    for bundle in bundles:
        print(f"\nProcessando: {os.path.basename(bundle)}")
        n = extract_bundle(bundle, BUNDLE_DIR)
        if n == 0:
            print("  (nenhuma textura)")
        total += n

    print(f"\nPronto! {total} imagem(ns) extraida(s) em:\n{BUNDLE_DIR}")

if __name__ == "__main__":
    main()