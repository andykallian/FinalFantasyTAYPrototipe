from PIL import Image, ImageDraw, ImageFont
import os

OUT = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx\splash.bmp"

img = Image.new("RGB", (256, 224), (0, 0, 0))
draw = ImageDraw.Draw(img)

try:
    font_small  = ImageFont.truetype("C:/Windows/Fonts/arial.ttf", 10)
    font_medium = ImageFont.truetype("C:/Windows/Fonts/arial.ttf", 14)
    font_large  = ImageFont.truetype("C:/Windows/Fonts/arial.ttf", 20)
except:
    font_small  = ImageFont.load_default()
    font_medium = ImageFont.load_default()
    font_large  = ImageFont.load_default()

gray   = (160, 160, 160)
white  = (255, 255, 255)
dimmed = (80,  80,  80)

draw.text((128, 60),  "P R O T O T Y P E",  font=font_small,  fill=gray,   anchor="mm")
draw.line([(78, 74), (178, 74)],  fill=dimmed, width=1)

draw.text((128, 100), "This prototype was created", font=font_medium, fill=gray,  anchor="mm")
draw.text((128, 118), "for demonstration to",       font=font_medium, fill=gray,  anchor="mm")

draw.text((128, 150), "Jacks", font=font_large, fill=white, anchor="mm")

draw.line([(78, 166), (178, 166)], fill=dimmed, width=1)

img = img.quantize(colors=16, method=Image.Quantize.MEDIANCUT)
img = img.convert("RGB")
img.save(OUT, format="BMP")

print(f"splash.bmp gerado em: {OUT}")
print(f"Tamanho: {img.size}, Modo: {img.mode}")