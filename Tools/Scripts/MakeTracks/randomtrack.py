import random
from enum import Enum

from PIL import Image

import pathastar

class Turn(Enum):
    LEFT = 1
    STRAIGHT = 2
    RIGHT = 3

def extendPosns(posns, e):
    lastPosn = posns[-1]
    lastDir = lastPosn[3]
    deltas = [(1, 0),
              (0, 1),
              (-1, 0),
              (0, -1)]
    dirDelta = {Turn.LEFT: 1,
                Turn.STRAIGHT: 0,
                Turn.RIGHT: 3}
    newDir = (lastDir + dirDelta[e]) % 4
    deltaPosn = deltas[lastDir]
    newXY = (lastPosn[0] + deltaPosn[0],
             lastPosn[1] + deltaPosn[1])
    return (newXY[0], newXY[1], lastDir, newDir)

def hasOverlap(posns):
    posSet = set()
    for p in posns:
        pxy = p[:2]
        if pxy in posSet:
            return True
        posSet.add(pxy)
    return False

def canClose(posns, final_loop_len):
    sp = pathastar.findShortestPath(posns, final_loop_len)
    if sp is None:
        return False
    return len(sp) <= final_loop_len

def makeTrackRecursive(final_loop_len, posns):
    # TODO make this smarter
    if posns[-1][:2] == (-1, 0):
        lastPosn = posns[-1]
        lX = lastPosn[0]
        lY = lastPosn[1]
        inDir = lastPosn[2]
        outDir = posns[0][2]
        posns[-1] = (lX, lY, inDir, outDir)
        return posns

    if (len(posns) == final_loop_len):
        return None

    print("track so far")
    printTrack(posns)
    print("current len:", len(posns))
    print("target len: ", final_loop_len)

    extensions = [Turn.LEFT, Turn.STRAIGHT, Turn.RIGHT]
    random.shuffle(extensions)

    for e in extensions:
        print (e)

        newPosns = posns + [extendPosns(posns, e)]
        #print ("new posns:", newPosns)

        if hasOverlap(newPosns):
            #print("has overlap, rejecting")
            continue

        if not canClose(newPosns, final_loop_len):
            #print("cannot close, rejecting")
            continue
        
        newSoln = makeTrackRecursive(final_loop_len, newPosns)
        if not (newSoln is None):
            return newSoln
    return None

def printTrack(posns):
    min_x = posns[0][0]
    min_y = posns[0][1]
    max_x = posns[0][0]
    max_y = posns[0][1]

    for p in posns:
        min_x = min(min_x, p[0])
        min_y = min(min_y, p[1])
        max_x = max(max_x, p[0])
        max_y = max(max_y, p[1])

    for y in range(max_y + 1, min_y - 1, -1):
        s = ""
        for x in range(min_x, max_x+1):
            foundPos = False
            for p in posns:
                if p[0]==x and p[1]==y:
                    foundPos = True
                    break
            if p == posns[0]:
                s += '>'
                continue
            if foundPos:
                turns = {(0, 0): '-',
                         (2, 2): '-',
                         (1, 1): '|',
                         (3, 3): '|',
                         (0, 1): 'J',
                         (0, 3): '\\',
                         (1, 2): '\\',
                         (1, 0): 'r',
                         (2, 1): 'L',
                         (2, 3): 'r',
                         (3, 2): 'J',
                         (3, 0): 'L'
                         }

                dirPair = p[2:]
                if dirPair in turns:
                    s += turns[dirPair]
                else:
                    s += '+'

            else:
                s += '.'
        print(s)


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

def drawPosn(im, posn, x_off, y_off, width, height):
    key = posn[2:]

    tiles = {(0, 0): straightEWTile,
             (1, 1): straightNSTile,
             (2, 2): straightEWTile,
             (3, 3): straightNSTile,
             (0, 1): tightLeft0,
             (0, 3): tightRight0,
             (1, 0): tightRight1,
             (1, 2): tightLeft1,
             (2, 1): tightRight2,
             (2, 3): tightLeft2,
             (3, 0): tightLeft3,
             (3, 2): tightRight3,
             }

    if key in tiles:
        px = 240 * (posn[0] + x_off)
        py = height - 240 * (posn[1] + y_off + 1)
        
        t = tiles[key]
        im.paste(t, (px, py))

def drawTrack(track, png_filename):
    min_x = track[0][0]
    max_x = min_x
    min_y = track[0][1]
    max_y = min_y
    
    for posn in track:
        min_x = min(min_x, posn[0])
        min_y = min(min_y, posn[1])
        max_x = max(max_x, posn[0])
        max_y = max(max_y, posn[1])

    width = max_x - min_x + 3
    height = max_y - min_y + 3

    im_width = 240 * width
    im_height = 240 * height

    x_off = 1 - min_x
    y_off = 1 - min_y
                    
    im = Image.new("RGB",
                   (im_width, im_height), (0, 255, 0))

    for ex in range(0, im_width, 240):
        for ey in range(0, im_height, 240):
            im.paste(emptyTile, (ex, ey))
    
    for posn in track:
        drawPosn(im, posn, x_off, y_off, im_width, im_height)

    im.save(png_filename)
    

def makeTrack(loop_len, png_filename):
    posns=[(0,0,0,0)]

    track = makeTrackRecursive(loop_len, posns)
    if track is None:
        print ("no track")
        return
    print ("got good track")
    printTrack(track)
    drawTrack(track, png_filename)

if __name__ == "__main__":
    makeTrack(25, "random.png")
