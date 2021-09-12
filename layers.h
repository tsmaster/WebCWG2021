// layers.h

// layers for layered tiled procedural generation

#ifndef layers_h
#define layers_h

enum class TileLayer {
  EMPTY,
    
  WATER,
  CITY_CANDIDATE_LOCN,
  CITY_FINAL_LOCN,
  H2_CITY_POPULATION_DISTRIBUTION,
  CITY_POPULATION,
  H1_LOCAL_ROADS,
  H1_CROSS_TILE_ROADS,

  Last,
};

#endif //layers_h
