import csv
import glob
import math

from PIL import Image

filenames = ["sampletrack.tsv",
             "fuji.tsv"]

DRAW_DPI = 20

emptyTile = Image.open("empty.png")
straightEWTile = Image.open("1x1straight3lane.png")
straightNSTile = straightEWTile.rotate(90)
tightLeft0 = Image.open("1x1left903lane.png")
tightLeft1 = tightLeft0.rotate(90)
tightLeft2 = tightLeft1.rotate(90)
tightLeft3 = tightLeft2.rotate(90)
tightRight0 = Image.open("1x1right903lane.png")
tightRight1 = tightRight0.rotate(90)
tightRight2 = tightRight1.rotate(90)
tightRight3 = tightRight2.rotate(90)
mediumLeft0 = Image.open("2x2left903lane.png")
mediumLeft1 = mediumLeft0.rotate(90)
mediumLeft2 = mediumLeft1.rotate(90)
mediumLeft3 = mediumLeft2.rotate(90)
mediumRight0 = Image.open("2x2right903lane.png")
mediumRight1 = mediumRight0.rotate(90)
mediumRight2 = mediumRight1.rotate(90)
mediumRight3 = mediumRight2.rotate(90)

def placeTile(im, row, col, label):
    print (row, col, label)

    px = col * 12 * DRAW_DPI
    py = row * 12 * DRAW_DPI

    if label == 'E':
        im.paste(emptyTile, (px, py))
    elif ((label == 'S 0') or (label == 'S 2')):
        im.paste(straightEWTile, (px, py))
    elif ((label == 'S 1') or (label == 'S 3')):
        im.paste(straightNSTile, (px, py))
    elif (label == 'L1 0'):
        im.paste(tightLeft0, (px, py))
    elif (label == 'L1 1'):
        im.paste(tightLeft1, (px, py))
    elif (label == 'L1 2'):
        im.paste(tightLeft2, (px, py))
    elif (label == 'L1 3'):
        im.paste(tightLeft3, (px, py))
    elif (label == 'R1 0'):
        im.paste(tightRight0, (px, py))
    elif (label == 'R1 1'):
        im.paste(tightRight1, (px, py))
    elif (label == 'R1 2'):
        im.paste(tightRight2, (px, py))
    elif (label == 'R1 3'):
        im.paste(tightRight3, (px, py))
    elif (label == 'L2 0'):
        im.paste(mediumLeft0, (px, py))
    elif (label == 'L2 1'):
        im.paste(mediumLeft1, (px, py))
    elif (label == 'L2 2'):
        im.paste(mediumLeft2, (px, py))
    elif (label == 'L2 3'):
        im.paste(mediumLeft3, (px, py))
    elif (label == 'R2 0'):
        im.paste(mediumRight0, (px, py))
    elif (label == 'R2 1'):
        im.paste(mediumRight1, (px, py))
    elif (label == 'R2 2'):
        im.paste(mediumRight2, (px, py))
    elif (label == 'R2 3'):
        im.paste(mediumRight3, (px, py))


        

def drawTrack(tsvFn, pngFn):
    with open(fn) as tsvfile:
        tsvreader = csv.reader(tsvfile, delimiter='\t')

        labels = {}
        maxRow = 0
        maxCol = 0
        
        for rowNum, row in enumerate(tsvreader):
            maxRow = max(rowNum, maxRow)
            for colNum, label in enumerate(row):
                maxCol = max(colNum, maxCol)

                labels[(rowNum, colNum)] = label

        im = Image.new("RGB", (DRAW_DPI * 12 * (maxCol + 1),
                               DRAW_DPI * 12 * (maxRow + 1)), (200, 200, 0))

        for rc in labels.keys():
            row, col = rc
            label = labels[rc].strip()
            if label:
                placeTile(im, row, col, label)


        im.save(pngFn)


for fn in filenames:
    drawTrack(fn, fn[:-3]+"png")
                
