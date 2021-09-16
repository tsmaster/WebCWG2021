// layers.h

// layers for layered tiled procedural generation

#ifndef layers_h
#define layers_h

enum class TileLayer {
  EMPTY,
    
  WATER,
  H1_FRACTAL_LAND_COLOR,
  H1_CITY_CANDIDATE_LOCN,
  H1_CITY_FINAL_LOCN,
  H0_CITY_LOCN,  //5
  H2_CITY_POPULATION_DISTRIBUTION, // 6
  CITY_POPULATION,
  H1_LOCAL_ROADS,
  H1_CROSS_TILE_ROADS,
  H0_FINAL,

  Last,
};

#endif //layers_h
