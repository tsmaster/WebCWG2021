import csv
import glob
import math

from PIL import Image

TSV_FILENAME = "tiledesc.tsv"

DRAW_DPI = 20

def makeTile(desc,
             width, height,
             enterSide, exitSide,
             enterWidth, exitWidth,
             enterOffset, exitOffset):

    width = float(width)
    height = float(height)
    enterSide = int(enterSide)
    exitSide = int(exitSide)
    enterWidth = float(enterWidth)
    exitWidth = float(exitWidth)
    enterOffset = float(enterOffset)
    exitOffset = float(exitOffset)
    
    fn = (desc+'.png').replace(' ','')
    print ("making tile %s" % fn)
    
    im = Image.new("RGB", (int(float(width)*DRAW_DPI),
                           int(float(height)*DRAW_DPI)), (0, 255, 0))

    segments = []

    if fn == "1x1straight3lane.png":
        segments.append(Straight(0, height - enterOffset, enterWidth,
                                 width, exitOffset, exitWidth))

    elif fn == "1x1left903lane.png":
        segments.append(Arc(0, 0, width/2.0,
                            270, 360, enterWidth, exitWidth))

    elif fn == "1x1right903lane.png":
        segments.append(Arc(0, height, width/2.0,
                            270, 360, enterWidth, exitWidth))

    elif fn == "2x2left903lane.png":
        segments.append(Arc(0, 0, enterOffset,
                            270, 360, enterWidth, exitWidth))

    elif fn == "2x2right903lane.png":
        segments.append(Arc(0, height, height - enterOffset,
                            270, 360, enterWidth, exitWidth))

        

        

    renderSegments(im, segments)

    im.save(fn)

class Straight:
    def __init__(self, enterX, enterY, enterWidth,
                 exitX, exitY, exitWidth):
        self.enterPos = (enterX, enterY)
        self.exitPos = (exitX, exitY)
        self.enterWidth = enterWidth
        self.exitWidth = exitWidth

    def distToLine(self, x, y):
        # todo fix
        midY = (self.enterPos[1] + self.exitPos[1]) / 2.0
        return (abs(y - midY) , x)

    def getWidthAtParam(self, p):
        # todo fix
        midW = (self.enterWidth + self.exitWidth) / 2.0
        return midW

class Arc:
    def __init__(self, centerX, centerY, radius,
                 beginDegrees, endDegrees, beginWidth, endWidth):
        self.center = (centerX, centerY)
        self.radius = radius
        self.beginRadians = math.radians(beginDegrees)
        self.endRadians = math.radians(endDegrees)
        self.beginWidth = beginWidth
        self.endWidth = endWidth

    def distToLine(self, x, y):
        dx = x - self.center[0]
        dy = y - self.center[1]

        #todo fix arc
        distSqrToCenter = dx*dx + dy*dy
        distToCenter = math.sqrt(distSqrToCenter)

        #todo fix param
        return (abs(distToCenter - self.radius), 0)

    def getWidthAtParam(self, param):
        #todo fix param
        return self.beginWidth

    

def renderSegments(im, segments):
    imWidth, imHeight = im.size
    for x in range(imWidth):
        fx = x / float(DRAW_DPI)
        for y in range(imHeight):
            fy = y / float(DRAW_DPI)

            bestSegment = None
            closestDist = -1
            bestParam = -1
            
            for s in segments:
                segDist,lineParam = s.distToLine(fx, fy)
                if ((bestSegment is None) or
                    (segDist < closestDist)):
                    bestSegment = s
                    closestDist = segDist
                    bestParam = lineParam
            c = (0, 200, 0)
            if bestSegment:
                trackWidth = bestSegment.getWidthAtParam(bestParam)
                if closestDist < trackWidth:
                    c = (64, 64, 64)
                elif (closestDist < trackWidth + 0.5):
                    c = (128, 0, 0)
                else:
                    c = (0, 200, 0)

            im.putpixel((x, y), c)

def readFile(fn):
    with open(fn) as tsvfile:
        tsvreader = csv.reader(tsvfile, delimiter='\t')
        for rowNum, row in enumerate(tsvreader):
            if rowNum != 0:
                print(','.join(row))
                makeTile(*row)

readFile(TSV_FILENAME)
