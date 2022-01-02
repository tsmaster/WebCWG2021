

def printAtDepth(depth, *varargs):
    if depth == 0:
        print(*varargs)
    else:
        prefix = " " * depth
        print(prefix, *varargs)


