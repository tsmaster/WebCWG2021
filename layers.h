// layers.h

// layers for layered tiled procedural generation

#ifndef layers_h
#define layers_h

enum class TileLayers {
  WATER = 0,
  CITY_CANDIDATE_LOCN = 1,
  CITY_FINAL_LOCN = 2,
  H2_CITY_POPULATION_DISTRIBUTION = 3,
  CITY_POPULATION = 4,
  H1_LOCAL_ROADS = 5,
  H1_CROSS_TILE_ROADS = 6,
};

#endif //layers_h
