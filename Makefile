# Makefile examples
# https://earthly.dev/blog/g++-makefile/
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

# make -j 4 <targets>

_CWG_CPPS = main.cpp bdg_math.cpp bdg_random.cpp button.cpp city.cpp citynames.cpp coord.cpp gameclock.cpp hsv.cpp kruskal.cpp mode_city.cpp mode_highway.cpp node.cpp nodemgr.cpp popup_dialog.cpp screen_bg.cpp

_CWG_HS = bdg_math.h bdg_random.h button.h city.h constants.h coord.h entt.hpp gameclock.h hsv.h kruskal.h layers.h mode_city.h mode_highway.h modes.h node.h nodemgr.h olc_pgex_sound.h olcPixelGameEngine.h popup_dialog.h screen_bg.h 

_CWG_OBJS = main.o bdg_math.o bdg_random.o button.o city.o citynames.o coord.o gameclock.o hsv.o kruskal.o mode_city.o mode_highway.o node.o nodemgr.o popup_dialog.o screen_bg.o


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

all: sparkle cwg cwg.html

clean:
	rm -f sparkle cwg cwg-opt cwg-dbg cwg.js cwg.html cwg.wasm cwg.data *.o *~ Build/*.o

sparkle: sparkle.cpp
	$(CXX) -o sparkle sparkle.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

cwg-old: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17

cwg-opt: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) $(CLIBS) $(COPTFLAGS)

cwg-dbg: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) $(CLIBS) $(CDBGFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

cwg: $(CWG_OBJS)
	$(CXX) -o $@ $^ $(CLIBS) $(CFLAGS)



cwg.html: $(CWG_CPPS) $(CWG_HS)
	$(EMXX) -std=c++17 -O2 -lopenal -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s ASSERTIONS=1 $(CWG_CPPS) -o $@ --preload-file ./Assets

run-cwg: cwg.html
	emrun cwg.html

sound_test: $(SOUND_TEST_CPPS) $(SOUND_TEST_HS)
	$(CXX) -o $@ $(SOUND_TEST_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17
