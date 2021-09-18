// layers.h

// layers for layered tiled procedural generation

#ifndef layers_h
#define layers_h

enum class TileLayer {
  EMPTY,
    
  WATER,
  H1_CITY_CANDIDATE_LOCN,
  H1_CITY_FINAL_LOCN,
  H2_CITY_POPULATION_DISTRIBUTION, // 4
  H0_CITY_LOCN_NAME_POP,  // 5
  H1_LOCAL_ROADS,
  H1_CROSS_TILE_ROADS,
  H0_ROAD,
  FRACTAL_LAND_COLOR, // 9
  H0_FINAL,

  Last,
};

#endif //layers_h
