CWG_CPPS = main.cpp bdg_math.cpp bdg_random.cpp button.cpp city.cpp coord.cpp gameclock.cpp hsv.cpp kruskal.cpp mode_highway.cpp node.cpp nodemgr.cpp popup_dialog.cpp screen_bg.cpp 
CWG_HS = bdg_math.h bdg_random.h button.h city.h constants.h coord.h entt.hpp gameclock.h hsv.h kruskal.h layers.h mode_highway.h modes.h node.h nodemgr.h olc_pgex_sound.h olcPixelGameEngine.h popup_dialog.h screen_bg.h 

SOUND_TEST_CPPS = sound_test.cpp
SOUND_TEST_HS = olc_pgex_sound.h

all: sparkle cwg cwg.html

clean:
	rm -f sparkle cwg cwg-opt cwg.js cwg.html cwg.wasm cwg.data

sparkle: sparkle.cpp
	g++ -o sparkle sparkle.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

cwg: $(CWG_CPPS) $(CWG_HS)
	g++ -o $@ $(CWG_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17

cwg-opt: $(CWG_CPPS) $(CWG_HS)
	g++ -o $@ $(CWG_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17 -O2

cwg.html: $(CWG_CPPS) $(CWG_HS)
	em++ -std=c++17 -O2 -lopenal -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s ASSERTIONS=1 $(CWG_CPPS) -o $@ --preload-file ./Assets

run-cwg: cwg.html
	emrun cwg.html

sound_test: $(SOUND_TEST_CPPS) $(SOUND_TEST_HS)
	g++ -o $@ $(SOUND_TEST_CPPS) -lX11 -lGL -lpthread -lpng -lstdc++fs -lopenal -std=c++17
