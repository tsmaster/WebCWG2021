
files = """
bdg_math.cpp    
bdg_math.h
bdg_random.cpp
bdg_random.h
button.cpp
button.h
city.cpp
city.h         
constants.h
coord.cpp
coord.h
gameclock.cpp
gameclock.h
hsv.cpp
hsv.h             
kruskal.cpp
kruskal.h
layers.h
main.cpp
mode_highway.cpp
mode_highway.h
modes.h
node.cpp
node.h
nodemgr.cpp
nodemgr.h
screen_bg.cpp
screen_bg.h
sound_test.cpp
sparkle.cpp
""".split()


total = 0

for f in files:
    fn = f.strip()
    print(fn)

    with open(fn) as fileobj:
        lines = fileobj.readlines()
        count = len(lines)
        print("line count:", count)

        total += count

print ("total line count:", total)
