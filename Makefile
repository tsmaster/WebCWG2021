# Makefile examples
# https://earthly.dev/blog/g++-makefile/
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean

# make -j 4 <targets>

DEPDIR := Dependencies
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

#COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

#%.o : %.c
#%.o : %.c $(DEPDIR)/%.d | $(DEPDIR)
#        $(COMPILE.c) $(OUTPUT_OPTION) $<


_CWG_CPPS = arena_barrel.cpp arena_ai_controller.cpp astar.cpp bdg_car.cpp bdg_math.cpp bdg_random.cpp bicycle_car_physics.cpp button.cpp camera.cpp carswithguns.cpp city.cpp citymap.cpp citynames.cpp coord.cpp gameclock.cpp hsv.cpp kruskal.cpp main.cpp mission.cpp mode_arena.cpp mode_building.cpp mode_city.cpp mode_highway.cpp mode_track.cpp modemgr.cpp names.cpp node.cpp nodemgr.cpp part_phys_syst.cpp person.cpp popup_dialog.cpp primes.cpp screen_bg.cpp world_geom.cpp

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
	rm -f cwg cwg-opt cwg-dbg cwg.js cwg.html cwg.wasm cwg.data *~ Build/*.o Dependencies/*

cwg-opt: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) $(CLIBS) $(COPTFLAGS)

cwg-dbg: $(CWG_CPPS) $(CWG_HS)
	$(CXX) -o $@ $(CWG_CPPS) $(CLIBS) $(CDBGFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(CXX) $(DEPFLAGS) -c -o $@ $< $(CFLAGS)

cwg: $(CWG_OBJS)
	$(CXX) -o $@ $^ $(CLIBS) $(CFLAGS)



cwg.html: $(CWG_CPPS) $(CWG_HS)
	$(EMXX) $(COPTFLAGS) -lopenal -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s ASSERTIONS=1 $(CWG_CPPS) -o $@ --preload-file ./Assets

run-cwg: cwg.html
	emrun cwg.html

sound_test: $(SOUND_TEST_CPPS) $(SOUND_TEST_HS)
	$(CXX) -o $@ $(SOUND_TEST_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17


$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(_CWG_CPPS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))

