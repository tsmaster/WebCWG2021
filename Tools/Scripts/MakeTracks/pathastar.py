#probably just do a flood fill, despite the filename


deltas = [(0, 1),
          (1, 0),
          (0, -1),
          (-1, 0)]

def tracePath(firstPosn, lastPosn, distances):
    firstPosn = firstPosn[:2]
    lastPosn = lastPosn[:2]
    #print("tracing fp:", firstPosn, "lp:", lastPosn)
    curPos = lastPosn
    backPath = [lastPosn]
    while True:
        bestPos = None
        bestDist = -1

        for dx, dy in deltas:
            nx = curPos[0] + dx
            ny = curPos[1] + dy

            curDist = distances[curPos]

            newPos = (nx, ny)

            if not newPos in distances:
                continue
            newDist = distances[newPos]

            if newDist == curDist - 1:
                bestPos = newPos
                bestDist = newDist
                break
        if bestPos is None:
            print ("error!")
            return None
        curPos = bestPos
        #print ("tracing through", curPos)
        backPath.append(curPos)
        if curPos == firstPosn:
            backPath.reverse()
            return backPath

    return [firstPosn, lastPosn]

def findShortestPath(path, maxDist):
    distances = {}
    
    for pi, posn in enumerate(path):
        posnX = posn[0]
        posnY = posn[1]

        distances[(posnX, posnY)] = pi

    #print ("start distances:")
    #print (distances)

    firstPosn = path[0][:2]
    lastPosn = path[-1][:2]
    openPosns = [lastPosn]

    destPosn = path[0][:2]

    # TODO make this smarter
    destPosn = (-1, 0)

    if (destPosn == lastPosn):
        if len(path) <= maxDist:
            return path
        else:
            return None

    while openPosns:
        posn = openPosns.pop(0)
        oldDist = distances[posn]
        newDist = oldDist + 1

        #print("considering pos",posn, " with dist ", oldDist)

        if newDist > maxDist:
            continue

        for dx, dy in deltas:
            newX = posn[0] + dx
            newY = posn[1] + dy

            newPosn = (newX, newY)

            canPlace = False
            
            if not (newPosn in distances):
                canPlace = True
            else:
                newPosnDist = distances[newPosn]
                if newPosnDist > newDist:
                    canPlace = True

            if canPlace:
                distances[newPosn] = newDist

                if newPosn == destPosn:
                    #print("tracing path")
                    #for dk in distances:
                    #    print(dk, distances[dk])

                    return tracePath(firstPosn, destPosn, distances)[1:]
                else:
                    openPosns.append(newPosn)
    return None



def test():
    p0 = (0, 0)
    p1 = (1, 0)
    p2 = (2, 0)
    p3 = (2, 1)

    path = [p0, p1, p2, p3]

    print (findShortestPath(path, 10))



if __name__ == "__main__":
    test()
