# Makefile examples
# https://earthly.dev/blog/g++-makefile/
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean

# make -j 4 <targets>

_CWG_CPPS = astar.cpp bdg_math.cpp bdg_random.cpp button.cpp carswithguns.cpp city.cpp citymap.cpp citynames.cpp coord.cpp gameclock.cpp hsv.cpp kruskal.cpp main.cpp mode_city.cpp mode_highway.cpp names.cpp mission.cpp modemgr.cpp node.cpp nodemgr.cpp person.cpp popup_dialog.cpp primes.cpp screen_bg.cpp

_CWG_HS = astar.h bdg_math.h bdg_random.h button.h carswithguns.h city.h citymap.h constants.h coord.h entt.hpp gameclock.h hsv.h kruskal.h layers.h mission.h mode_city.h mode_highway.h modemgr.h modes.h names.h node.h nodemgr.h olc_pgex_sound.h olcPixelGameEngine.h person.h popup_dialog.h primes.h screen_bg.h 

_CWG_OBJS=$(_CWG_CPPS:.cpp=.o)


SOUND_TEST_CPPS = sound_test.cpp
SOUND_TEST_HS = olc_pgex_sound.h

CXX = g++
EMXX = em++

SDIR=Source
IDIR=Source/Include
ODIR=Build

CWG_CPPS = $(patsubst %,$(SDIR)/%,$(_CWG_CPPS))
CWG_HS = $(patsubst %,$(IDIR)/%,$(_CWG_HS))
CWG_OBJS = $(patsubst %,$(ODIR)/%,$(_CWG_OBJS))

CLIBS = -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal
CFLAGS = -std=c++17 -I$(IDIR)
COPTFLAGS = -std=c++17 -O2 -I$(IDIR)
CDBGFLAGS = -std=c++17 -Og -ggdb -I$(IDIR)


.PHONY: all clean

all: cwg cwg.html

clean:
	rm -f cwg cwg-opt cwg-dbg cwg.js cwg.html cwg.wasm cwg.data *~ Build/*.o

cwg-opt: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) $(CLIBS) $(COPTFLAGS)

cwg-dbg: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) $(CLIBS) $(CDBGFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(CWG_HS)
	$(CXX) -c -o $@ $< $(CFLAGS)

cwg: $(CWG_OBJS)
	$(CXX) -o $@ $^ $(CLIBS) $(CFLAGS)



cwg.html: $(CWG_CPPS) $(CWG_HS)
	$(EMXX) $(COPTFLAGS) -lopenal -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s ASSERTIONS=1 $(CWG_CPPS) -o $@ --preload-file ./Assets

run-cwg: cwg.html
	emrun cwg.html

sound_test: $(SOUND_TEST_CPPS) $(SOUND_TEST_HS)
	$(CXX) -o $@ $(SOUND_TEST_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17
