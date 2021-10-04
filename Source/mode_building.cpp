#include "mode_building.h"

#include "bdg_random.h"
#include "carswithguns.h"

void BuildingGameMode::init(olc::Sprite* menuSprite,
			    olc::Sprite* faceSprite,
			    olc::Sprite* hairSprite,
			    olc::Sprite* pantsSprite,
			    olc::Sprite* shirtsSprite,
			    olc::Sprite* shoesSprite,
			    olc::Sprite* skinSprite)
{
  m_menuSprite = menuSprite;
  m_faceSprite = faceSprite;
  m_hairSprite = hairSprite;
  m_pantsSprite = pantsSprite;
  m_shirtsSprite = shirtsSprite;
  m_shoesSprite = shoesSprite;
  m_skinSprite = skinSprite;

  m_faceDecal = new olc::Decal(m_faceSprite);
  m_hairDecal = new olc::Decal(m_hairSprite);
  m_pantsDecal = new olc::Decal(m_pantsSprite);
  m_shirtsDecal = new olc::Decal(m_shirtsSprite);
  m_shoesDecal = new olc::Decal(m_shoesSprite);
  m_skinDecal = new olc::Decal(m_skinSprite);

  m_bDrawTorso = true;
  m_bDrawPelvis = true;
}

bool BuildingGameMode::update(CarsWithGuns* game, float elapsedSeconds)
{
  handleUserInput(game);
  return true;
}

void BuildingGameMode::handleUserInput(CarsWithGuns* game)
{
  if (game->GetKey(olc::Key::K1).bPressed) {
    m_bDrawTorso = !m_bDrawTorso;
  }

  if (game->GetKey(olc::Key::K2).bPressed) {
    m_bDrawPelvis = !m_bDrawPelvis;
  }

  if (game->GetKey(olc::Key::RIGHT).bPressed) {
    ++m_seed;
  }

  if (game->GetKey(olc::Key::LEFT).bPressed) {
    --m_seed;
  }

  
}

void BuildingGameMode::draw(CarsWithGuns* game)
{
  game->Clear(olc::BLUE);

  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

  int pcx = sw / 2;
  int pcy = sh / 2;
  
  drawPerson(game, pcx / 2, pcy);
}

void BuildingGameMode::drawPerson(CarsWithGuns* game, int x, int y)
{
  srand(m_seed);
  
  std::vector<SpriteCoords> armSprites {
    {173, 608, 170, 136},  // tint1_arm.png
    {343, 472, 170, 136},  // tint2_arm.png
    {173, 472, 170, 136},  // tint3_arm.png
    {173, 336, 170, 136},  // tint4_arm.png
    {343, 336, 170, 136},  // tint5_arm.png
    {173, 744, 170, 136},  // tint6_arm.png
    {173, 880, 170, 136},  // tint7_arm.png
    {343, 608, 170, 136},  // tint8_arm.png
  };

  std::vector<SpriteCoords> handSprites {
    {439, 908, 61, 71},  // tint1_hand.png
    {346, 201, 61, 71},  // tint2_hand.png
    {407, 201, 61, 71},  // tint3_hand.png
    {593, 0, 61, 71},  // tint4_hand.png
    {593, 71, 61, 71},  // tint5_hand.png
    {532, 71, 61, 71},  // tint6_hand.png
    {606, 142, 61, 71},  // tint7_hand.png
    {532, 0, 61, 71},  // tint8_hand.png
  };

  std::vector<SpriteCoords> headSprites {
    {173, 0, 173, 168},  // tint1_head.png
    {0, 672, 173, 168},  // tint2_head.png
    {0, 504, 173, 168},  // tint3_head.png
    {0, 336, 173, 168},  // tint4_head.png
    {0, 0, 173, 168},  // tint5_head.png
    {0, 168, 173, 168},  // tint6_head.png
    {173, 168, 173, 168},  // tint7_head.png
    {0, 840, 173, 168},  // tint8_head.png
  };

  std::vector<SpriteCoords> legSprites {
    {439, 37, 93, 164},  // tint1_leg.png
    {532, 857, 93, 164},  // tint2_leg.png
    {513, 365, 93, 164},  // tint3_leg.png
    {513, 529, 93, 164},  // tint4_leg.png
    {513, 201, 93, 164},  // tint5_leg.png
    {532, 693, 93, 164},  // tint6_leg.png
    {439, 744, 93, 164},  // tint7_leg.png
    {346, 37, 93, 164},  // tint8_leg.png
  };

  std::vector<SpriteCoords> neckSprites {
    {343, 744, 96, 37},  // tint1_neck.png
    {343, 929, 96, 37},  // tint2_neck.png
    {343, 855, 96, 37},  // tint3_neck.png
    {343, 818, 96, 37},  // tint4_neck.png
    {343, 966, 96, 37},  // tint5_neck.png
    {346, 0, 96, 37},  // tint6_neck.png
    {343, 781, 96, 37},  // tint7_neck.png
    {343, 892, 96, 37},  // tint8_neck.png
  };


  // shoes

  std::vector<SpriteCoords> shoeSprites {
    {0, 378, 94, 42}, // "blackShoe1.png" 
    {0, 336, 94, 42}, // "blackShoe2.png" 
    {0, 294, 94, 42}, // "blackShoe3.png" 
    {0, 252, 94, 42}, // "blackShoe4.png" 
    {0, 210, 94, 42}, // "blackShoe5.png" 
    {0, 168, 94, 42}, // "blueShoe1.png" 
    {0, 126, 94, 42}, // "blueShoe2.png" 
    {0, 84, 94, 42}, // "blueShoe3.png" 
    {0, 42, 94, 42}, // "blueShoe4.png" 
    {0, 0, 94, 42}, // "blueShoe5.png" 
    {188, 210, 94, 42}, // "brown2Shoe1.png" 
    {188, 168, 94, 42}, // "brown2Shoe2.png" 
    {188, 126, 94, 42}, // "brown2Shoe3.png" 
    {188, 84, 94, 42}, // "brown2Shoe4.png" 
    {188, 42, 94, 42}, // "brown2Shoe5.png" 
    {94, 210, 94, 42}, // "brownShoe1.png" 
    {188, 378, 94, 42}, // "brownShoe2.png" 
    {188, 336, 94, 42}, // "brownShoe3.png" 
    {188, 294, 94, 42}, // "brownShoe4.png" 
    {188, 252, 94, 42}, // "brownShoe5.png" 
    {188, 0, 94, 42}, // "greyShoe1.png" 
    {94, 462, 94, 42}, // "greyShoe2.png" 
    {94, 420, 94, 42}, // "greyShoe3.png" 
    {94, 378, 94, 42}, // "greyShoe4.png" 
    {94, 336, 94, 42}, // "greyShoe5.png" 
    {94, 294, 94, 42}, // "redShoe1.png" 
    {94, 252, 94, 42}, // "redShoe2.png" 
    {188, 420, 94, 42}, // "redShoe3.png" 
    {94, 168, 94, 42}, // "redShoe4.png" 
    {94, 126, 94, 42}, // "redShoe5.png" 
    {94, 84, 94, 42}, // "tanShoe1.png" 
    {94, 42, 94, 42}, // "tanShoe2.png" 
    {94, 0, 94, 42}, // "tanShoe3.png" 
    {0, 462, 94, 42}, // "tanShoe4.png" 
    {0, 420, 94, 42}, // "tanShoe5.png" 
  };

  // pants

  std::vector<std::vector<SpriteCoords>> pantsLegSprites{
    {
      { 417, 448, 111, 166}, // "pantsBlue1_long.png"
      { 635, 782, 107, 118}, // "pantsBlue1_short.png"
      { 746, 433, 104, 105}, // "pantsBlue1_shorter.png"
    },
    {
      { 306, 282, 111, 166}, // "pantsBlue2_long.png"
      { 528, 900, 107, 118}, // "pantsBlue2_short.png"
      { 784, 0, 104, 105}, // "pantsBlue2_shorter.png"
    },
    {
      { 528, 166, 111, 166}, // "pantsBrown_long.png"
      { 639, 236, 107, 118}, // "pantsBrown_short.png"
      { 846, 643, 104, 105}, // "pantsBrown_shorter.png"
    },
    {
      { 417, 780, 111, 166}, // "pantsGreen_long.png"
      { 639, 472, 107, 118}, // "pantsGreen_short.png"
      { 746, 223, 104, 105}, // "pantsGreen_shorter.png"
    },
    {
      { 459, 0, 111, 166}, // "pantsGrey_long.png"
      { 639, 354, 107, 118}, // "pantsGrey_short.png"
      { 742, 590, 104, 105}, // "pantsGrey_shorter.png"
    },
    {
      { 528, 498, 111, 166}, // "pantsLightBlue_long.png"
      { 635, 664, 107, 118}, // "pantsLightBlue_short.png"
      { 742, 905, 104, 105}, // "pantsLightBlue_shorter.png"
    },
    {
      { 528, 332, 111, 166}, // "pantsNavy_long.png"
      { 570, 0, 107, 118}, // "pantsNavy_short.png"
      { 742, 800, 104, 105}, // "pantsNavy_shorter.png"
    },
    {
      { 306, 780, 111, 166}, // "pantsPine_long.png"
      { 528, 782, 107, 118}, // "pantsPine_short.png"
      { 742, 695, 104, 105}, // "pantsPine_shorter.png"
    },
    {
      { 306, 614, 111, 166}, // "pantsRed_long.png"
      { 528, 664, 107, 118}, // "pantsRed_short.png"
      { 846, 748, 104, 105}, // "pantsRed_shorter.png"
    },
    {
      { 417, 282, 111, 166}, // "pantsTan_long.png"
      { 677, 0, 107, 118}, // "pantsTan_short.png"
      { 746, 328, 104, 105}, // "pantsTan_shorter.png"
    },
    {
      { 306, 448, 111, 166}, // "pantsWhite_long.png"
      { 635, 900, 107, 118}, // "pantsWhite_short.png"
      { 846, 538, 104, 105}, // "pantsWhite_shorter.png"
    },
    {
      { 417, 614, 111, 166}, // "legYellow_long.png"
      { 639, 118, 107, 118}, // "legYellow_short.png"
      { 746, 118, 104, 105}, // "legYellow_shorter.png"
    },
  };

  std::vector<std::vector<SpriteCoords>> pantsCrotchSprites{
    {
      { 0, 940, 153, 47}, // "pantsBlue11.png"
      { 0, 893, 153, 47}, // "pantsBlue12.png"
      { 0, 846, 153, 47}, // "pantsBlue13.png"
      { 0, 799, 153, 47}, // "pantsBlue14.png"
    },
    {
      { 0, 611, 153, 47}, // "pantsBlue21.png"
      { 0, 564, 153, 47}, // "pantsBlue22.png"
      { 0, 517, 153, 47}, // "pantsBlue23.png"
      { 0, 470, 153, 47}, // "pantsBlue24.png"
    },
    {
      { 0, 282, 153, 47}, // "pantsBrown1.png"
      { 0, 235, 153, 47}, // "pantsBrown2.png"
      { 0, 188, 153, 47}, // "pantsBrown3.png"
      { 0, 141, 153, 47}, // "pantsBrown4.png"
    },
    {
      { 0, 47, 153, 47}, // "pantsGreen1.png"
      { 0, 94, 153, 47}, // "pantsGreen2.png"
      { 0, 705, 153, 47}, // "pantsGreen3.png"
      { 0, 329, 153, 47}, // "pantsGreen4.png"
    },
    {
      { 153, 188, 153, 47}, // "pantsGrey1.png"
      { 153, 329, 153, 47}, // "pantsGrey2.png"
      { 0, 376, 153, 47}, // "pantsGrey3.png"
      { 306, 47, 153, 47}, // "pantsGrey4.png"
    },
    {
      { 153, 282, 153, 47}, // "pantsLightBlue1.png"
      { 0, 752, 153, 47}, // "pantsLightBlue2.png"
      { 153, 235, 153, 47}, // "pantsLightBlue3.png"
      { 153, 376, 153, 47}, // "pantsLightBlue4.png"
    },
    {
      { 153, 799, 153, 47}, // "pantsNavy1.png"
      { 153, 705, 153, 47}, // "pantsNavy2.png"
      { 153, 846, 153, 47}, // "pantsNavy3.png"
      { 306, 0, 153, 47}, // "pantsNavy4.png"
    },
    {
      { 153, 658, 153, 47}, // "pantsPine1.png"
      { 153, 940, 153, 47}, // "pantsPine2.png"
      { 153, 893, 153, 47}, // "pantsPine3.png"
      { 306, 141, 153, 47}, // "pantsPine4.png"
    },
    {
      { 306, 235, 153, 47}, // "pantsRed1.png"
      { 306, 188, 153, 47}, // "pantsRed2.png"
      { 306, 94, 153, 47}, // "pantsRed3.png"
      { 153, 752, 153, 47}, // "pantsRed4.png"
    },
    {
      { 0, 0, 153, 47}, // "pantsTan1.png"
      { 153, 423, 153, 47}, // "pantsTan2.png"
      { 0, 658, 153, 47}, // "pantsTan3.png"
      { 0, 423, 153, 47}, // "pantsTan4.png"
    },
    {
      { 153, 611, 153, 47}, // "pantsWhite1.png"
      { 153, 564, 153, 47}, // "pantsWhite2.png"
      { 153, 517, 153, 47}, // "pantsWhite3.png"
      { 153, 470, 153, 47}, // "pantsWhite4.png"
    },
    {
      { 153, 141, 153, 47}, // "pantsYellow1.png"
      { 153, 94, 153, 47}, // "pantsYellow2.png"
      { 153, 47, 153, 47}, // "pantsYellow3.png"
      { 153, 0, 153, 47}, // "pantsYellow4.png"
    }
  };

  // Shirt torsos
  std::vector<SpriteCoords> shirtTorsoSprites {
    {477, 0, 153, 174}, // blueShirt1.png
    {475, 1392, 153, 174}, // blueShirt2.png
    {475, 1218, 153, 174}, // blueShirt3.png
    {0, 1484, 161, 174}, // blueShirt4.png
    {467, 1740, 153, 174}, // blueShirt5.png
    {467, 1566, 153, 174}, // blueShirt6.png
    {324, 870, 153, 174}, // blueShirt7.png
    {324, 696, 153, 174}, // blueShirt8.png

    {324, 0, 153, 174}, // greenShirt1.png
    {322, 1392, 153, 174}, // greenShirt2.png
    {322, 1218, 153, 174}, // greenShirt3.png
    {161, 1484, 161, 174}, // greenShirt4.png
    {314, 1832, 153, 174}, // greenShirt5.png
    {475, 1044, 153, 174}, // greenShirt6.png
    {171, 870, 153, 174}, // greenShirt7.png
    {477, 348, 153, 174}, // greenShirt8.png

    {322, 1044, 153, 174}, // greyShirt1.png
    {161, 1832, 153, 174}, // greyShirt2.png
    {171, 522, 153, 174}, // greyShirt3.png
    {0, 1658, 161, 174}, // greyShirt4.png
    {161, 1658, 153, 174}, // greyShirt5.png
    {171, 0, 153, 174}, // greyShirt6.png
    {171, 174, 153, 174}, // greyShirt7.png
    {171, 348, 153, 174}, // greyShirt8.png

    {314, 1658, 153, 174}, // navyShirt1.png
    {324, 348, 153, 174}, // navyShirt2.png
    {324, 522, 153, 174}, // navyShirt3.png
    {0, 1310, 161, 174}, // navyShirt4.png
    {324, 174, 153, 174}, // navyShirt5.png
    {171, 696, 153, 174}, // navyShirt6.png
    {477, 174, 153, 174}, // navyShirt7.png
    {477, 696, 153, 174}, // navyShirt8.png

    {628, 1044, 153, 174}, // pineShirt1.png
    {630, 174, 153, 174}, // pineShirt2.png
    {781, 1044, 153, 174}, // pineShirt3.png
    {0, 1136, 161, 174}, // pineShirt4.png
    {630, 522, 153, 174}, // pineShirt5.png
    {934, 1044, 153, 174}, // pineShirt6.png
    {783, 348, 153, 174}, // pineShirt7.png
    {781, 1218, 153, 174}, // pineShirt8.png    
    
    {783, 174, 153, 174}, // redShirt1.png
    {926, 1740, 153, 174}, // redShirt2.png
    {926, 1566, 153, 174}, // redShirt3.png
    {161, 1310, 161, 174}, // redShirt4.png
    {783, 522, 153, 174}, // redShirt5.png
    {934, 1218, 153, 174}, // redShirt6.png
    {783, 870, 153, 174}, // redShirt7.png
    {783, 696, 153, 174}, // redShirt8.png
    
    {630, 0, 153, 174}, // shirtYellow1.png
    {628, 1392, 153, 174}, // shirtYellow2.png
    {628, 1218, 153, 174}, // shirtYellow3.png
    {0, 1832, 161, 174}, // shirtYellow4.png
    {620, 1740, 153, 174}, // shirtYellow5.png
    {620, 1566, 153, 174}, // shirtYellow6.png
    {477, 870, 153, 174}, // shirtYellow7.png
    {477, 522, 153, 174}, // shirtYellow8.png
    
    {783, 0, 153, 174}, // whiteShirt1.png
    {781, 1392, 153, 174}, // whiteShirt2.png
    {630, 348, 153, 174}, // whiteShirt3.png
    {161, 1136, 161, 174}, // whiteShirt4.png
    {773, 1740, 153, 174}, // whiteShirt5.png
    {773, 1566, 153, 174}, // whiteShirt6.png
    {630, 870, 153, 174}, // whiteShirt7.png
    {630, 696, 153, 174}, // whiteShirt8.png
    
  };

  // shirt arms
  std::vector<std::vector<SpriteCoords>> shirtArmSprites {
    {
      {0, 0, 171, 142}, // blueArm_long.png
      {936, 0, 118, 96}, // blueArm_short.png
      {936, 460, 66, 86}, // blueArm_shorter.png
    },

    {
      {0, 710, 171, 142}, // greenArm_long.png
      {585, 1914, 118, 96}, // greenArm_short.png
      {322, 1566, 67, 86}, // greenArm_shorter.png
    },    
    
    {
      {0, 142, 171, 142}, // greyArm_long.png
      {936, 96, 118, 96}, // greyArm_short.png
      {936, 374, 66, 86}, // greyArm_shorter.png
    },

    {
      {0, 994, 171, 142}, // navyArm_long.png
      {934, 1392, 118, 96}, // navyArm_short.png
      {238, 1044, 67, 86}, // navyArm_shorter.png
    },

    {
      {0, 284, 171, 142}, // pineArm_long.png
      {936, 192, 118, 96}, // pineArm_short.png
      {389, 1566, 67, 86}, // pineArm_shorter.png
    },

    {
      {0, 852, 171, 142}, // redArm_long.png
      {821, 1914, 118, 96}, // redArm_short.png
      {936, 288, 66, 86}, // redArm_shorter.png
    },

    {
      {0, 426, 171, 142}, // armWhite_long.png
      {703, 1914, 118, 96}, // armWhite_short.png
      {171, 1044, 67, 86}, // armWhite_shorter.png
    },

    {
      {0, 568, 171, 142}, // armYellow_long.png
      {467, 1914, 118, 96}, // armYellow_short.png
      {936, 546, 66, 86}, // armYellow_shorter.png
    },
  };
  
  // face

  std::vector<SpriteCoords> browSprites {
    {41, 429, 40, 17}, // blackBrow1.png
    {0, 427, 41, 11}, // blackBrow2.png
    {41, 395, 40, 17}, // blackBrow3.png
    {81, 378, 40, 17}, // blondeBrow1.png
    {0, 372, 41, 11}, // blondeBrow2.png
    {80, 463, 40, 17}, // blondeBrow3.png
    {80, 446, 40, 17}, // brown1Brow1.png
    {0, 361, 41, 11}, // brown1Brow2.png
    {80, 480, 40, 17}, // brown1Brow3.png
    {0, 483, 40, 17}, // brown2Brow1.png
    {0, 383, 41, 11}, // brown2Brow2.png
    {40, 466, 40, 17}, // brown2Brow3.png
    {0, 449, 40, 17}, // greyBrow1.png
    {0, 416, 41, 11}, // greyBrow2.png
    {0, 466, 40, 17}, // greyBrow3.png
    {40, 449, 40, 17}, // redBrow1.png
    {0, 394, 41, 11}, // redBrow2.png
    {41, 361, 40, 17}, // redBrow3.png
    {41, 412, 40, 17}, // tanBrow1.png
    {0, 405, 41, 11}, // tanBrow2.png
    {81, 361, 40, 17}, // tanBrow3.png
    {40, 483, 40, 17}, // whiteBrow1.png
    {0, 438, 41, 11}, // whiteBrow2.png
    {41, 378, 40, 17}, // whiteBrow3.png    
  };
  
  std::vector<SpriteCoords> eyeSprites {
    {129, 266, 21, 21}, // eyeBlack_large.png
    {131, 168, 15, 16}, // eyeBlack_small.png
    {121, 365, 21, 21}, // eyeBlue_large.png
    {122, 236, 15, 16}, // eyeBlue_small.png
    {129, 287, 21, 21}, // eyeBrown_large.png
    {131, 152, 15, 16}, // eyeBrown_small.png
    {129, 329, 21, 21}, // eyeGreen_large.png
    {131, 215, 15, 16}, // eyeGreen_small.png
    {129, 308, 21, 21}, // eyePine_large.png
    {131, 184, 15, 16}, // eyePine_small.png
  };

  /*
    {0, 152, 100, 101}, // face1.png
    {0, 253, 98, 108}, // face2.png
    {0, 0, 112, 65}, // face3.png
    {0, 65, 111, 87}, // face4.png
  */

  std::vector<SpriteCoords> mouthSprites {
    {98, 253, 34, 13}, // mouth_glad.png
    {81, 421, 34, 13}, // mouth_happy.png
    {131, 200, 15, 15}, // mouth_oh.png
    {80, 497, 34, 13}, // mouth_sad.png
    {0, 500, 36, 6}, // mouth_straight.png
    {81, 395, 34, 13}, // mouth_teethLower.png
    {81, 408, 34, 13}, // mouth_teethUpper.png
  };

  std::vector<SpriteCoords> noseSprites {
    {98, 266, 31, 21}, // tint1Nose1.png
    {111, 65, 24, 24}, // tint1Nose2.png
    {120, 482, 22, 15}, // tint1Nose3.png
    {100, 173, 31, 21}, // tint2Nose1.png
    {111, 89, 24, 24}, // tint2Nose2.png
    {120, 467, 22, 15}, // tint2Nose3.png
    {100, 152, 31, 21}, // tint3Nose1.png
    {111, 113, 24, 24}, // tint3Nose2.png
    {114, 497, 22, 15}, // tint3Nose3.png
    {100, 215, 31, 21}, // tint4Nose1.png
    {112, 0, 24, 24}, // tint4Nose2.png
    {100, 236, 22, 15}, // tint4Nose3.png
    {100, 194, 31, 21}, // tint5Nose1.png
    {115, 419, 24, 24}, // tint5Nose2.png
    {111, 137, 22, 15}, // tint5Nose3.png
    {98, 287, 31, 21}, // tint6Nose1.png
    {112, 24, 24, 24}, // tint6Nose2.png
    {112, 48, 22, 15}, // tint6Nose3.png
    {98, 329, 31, 21}, // tint7Nose1.png
    {120, 443, 24, 24}, // tint7Nose2.png
    {136, 497, 22, 15}, // tint7Nose3.png
    {98, 308, 31, 21}, // tint8Nose1.png
    {115, 395, 24, 24}, // tint8Nose2.png
    {121, 350, 22, 15}, // tint8Nose3.png
  };

  // hair
  std::vector<SpriteCoords> hairSprites {
    {979, 524, 158, 119}, // blackMan1.png
    {1454, 119, 158, 138}, // blackMan2.png
    {1454, 1381, 158, 119}, // blackMan3.png
    {1454, 1262, 158, 119}, // blackMan4.png
    {0, 910, 171, 130}, // blackMan5.png
    {1454, 0, 158, 119}, // blackMan6.png
    {1453, 1922, 158, 119}, // blackMan7.png
    {821, 405, 158, 47}, // blackMan8.png
    {171, 454, 165, 227}, // blackWoman1.png
    {1453, 1637, 158, 285}, // blackWoman2.png
    {501, 227, 160, 227}, // blackWoman3.png
    {1298, 690, 158, 286}, // blackWoman4.png
    {168, 1466, 168, 213}, // blackWoman5.png
    {336, 908, 164, 213}, // blackWoman6.png
    {823, 1087, 159, 119}, // blondeMan1.png
    {979, 1206, 159, 138}, // blondeMan2.png
    {979, 1344, 159, 119}, // blondeMan3.png
    {979, 1463, 159, 119}, // blondeMan4.png
    {0, 260, 171, 130}, // blondeMan5.png
    {979, 1582, 159, 119}, // blondeMan6.png
    {979, 1701, 159, 119}, // blondeMan7.png
    {634, 2001, 158, 47}, // blondeMan8.png
    {1296, 1114, 158, 285}, // blondeWoman1.png
    {501, 0, 160, 227}, // blondeWoman2.png
    {1295, 404, 158, 286}, // blondeWoman3.png
    {336, 227, 165, 227}, // blondeWoman4.png
    {336, 1334, 164, 213}, // blondeWoman5.png
    {168, 1040, 168, 213}, // blondeWoman6.png
    {1138, 1590, 158, 119}, // brown1Man1.png
    {1138, 1452, 158, 138}, // brown1Man2.png
    {1137, 1820, 158, 119}, // brown1Man3.png
    {1296, 119, 158, 119}, // brown1Man4.png
    {0, 650, 171, 130}, // brown1Man5.png
    {1295, 1828, 158, 119}, // brown1Man6.png
    {982, 1047, 158, 119}, // brown1Man7.png
    {476, 2001, 158, 47}, // brown1Man8.png
    {982, 762, 158, 285}, // brown1Woman1.png
    {661, 0, 160, 227}, // brown1Woman2.png
    {1137, 405, 158, 286}, // brown1Woman3.png
    {336, 0, 165, 227}, // brown1Woman4.png
    {500, 1121, 164, 213}, // brown1Woman5.png
    {0, 1040, 168, 213}, // brown1Woman6.png
    {979, 405, 158, 119}, // brown2Man1.png
    {979, 1820, 158, 138}, // brown2Man2.png
    {980, 0, 158, 119}, // brown2Man3.png
    {979, 643, 158, 119}, // brown2Man4.png
    {0, 130, 171, 130}, // brown2Man5.png
    {1296, 1399, 158, 119}, // brown2Man6.png
    {1296, 0, 158, 119}, // brown2Man7.png
    {661, 1952, 158, 47}, // brown2Man8.png
    {1140, 829, 158, 285}, // brown2Woman1.png
    {661, 227, 160, 227}, // brown2Woman2.png
    {1138, 1166, 158, 286}, // brown2Woman3.png
    {336, 454, 165, 227}, // brown2Woman4.png
    {500, 1334, 164, 213}, // brown2Woman5.png
    {0, 1466, 168, 213}, // brown2Woman6.png
    {823, 968, 159, 119}, // greyMan1.png
    {820, 1857, 159, 138}, // greyMan2.png
    {820, 1738, 159, 119}, // greyMan3.png
    {820, 1619, 159, 119}, // greyMan4.png
    {0, 390, 171, 130}, // greyMan5.png
    {664, 1215, 159, 119}, // greyMan6.png
    {664, 1096, 159, 119}, // greyMan7.png
    {318, 2001, 158, 47}, // greyMan8.png
    {1138, 0, 158, 285}, // greyWoman1.png
    {501, 454, 160, 227}, // greyWoman2.png
    {980, 119, 158, 286}, // greyWoman3.png
    {336, 681, 165, 227}, // greyWoman4.png
    {336, 1760, 164, 213}, // greyWoman5.png
    {168, 1253, 168, 213}, // greyWoman6.png
    {664, 858, 159, 119}, // redMan1.png
    {823, 830, 159, 138}, // redMan2.png
    {821, 286, 159, 119}, // redMan3.png
    {664, 977, 159, 119}, // redMan4.png
    {0, 780, 171, 130}, // redMan5.png
    {159, 1892, 159, 119}, // redMan6.png
    {661, 1833, 159, 119}, // redMan7.png
    {792, 1999, 158, 47}, // redMan8.png
    {661, 454, 159, 285}, // redWoman1.png
    {500, 1547, 161, 227}, // redWoman2.png
    {661, 1547, 159, 286}, // redWoman3.png
    {171, 681, 165, 227}, // redWoman4.png
    {500, 908, 164, 213}, // redWoman5.png
    {0, 1679, 168, 213}, // redWoman6.png
    {1138, 285, 158, 119}, // tanMan1.png
    {1140, 691, 158, 138}, // tanMan2.png
    {1454, 257, 158, 119}, // tanMan3.png
    {1295, 1709, 158, 119}, // tanMan4.png
    {0, 520, 171, 130}, // tanMan5.png
    {1296, 1518, 158, 119}, // tanMan6.png
    {1296, 238, 158, 119}, // tanMan7.png
    {1296, 357, 158, 47}, // tanMan8.png
    {1453, 404, 158, 285}, // tanWoman1.png
    {501, 681, 160, 227}, // tanWoman2.png
    {168, 1679, 168, 213}, // tanWoman3.png
    {1454, 976, 158, 286}, // tanWoman4.png
    {171, 0, 165, 227}, // tanWoman5.png
    {336, 1121, 164, 213}, // tanWoman6.png
    {171, 908, 159, 119}, // whiteMan1.png
    {820, 692, 159, 138}, // whiteMan2.png
    {820, 573, 159, 119}, // whiteMan3.png
    {661, 739, 159, 119}, // whiteMan4.png
    {0, 0, 171, 130}, // whiteMan5.png
    {0, 1892, 159, 119}, // whiteMan6.png
    {820, 454, 159, 119}, // whiteMan7.png
    {950, 1995, 158, 47}, // whiteMan8.png
    {820, 1334, 159, 285}, // whiteWoman1.png
    {500, 1774, 161, 227}, // whiteWoman2.png
    {821, 0, 159, 286}, // whiteWoman3.png
    {171, 227, 165, 227}, // whiteWoman4.png
    {336, 1547, 164, 213}, // whiteWoman5.png
    {0, 1253, 168, 213}, // whiteWoman6.png
  };

  BoneFrame skeleton[] = {
    {-1, 0, 0}, // 0 - torso
    {0, 60, -55}, // 1 - r arm
    {0, -60, -55}, // 2 - l arm
    {1, 144, 86}, // 3 - r hand
    {2, -144, 86}, // 4 - l hand
    {0, 0, -76}, // 5 - neck
    {5, 0, -20}, // 6 - head
    {6, 0, -115}, // 7 - hair
    {0, 0, 100}, // 8 - crotch
    {8, 36, 0}, // 9 - r leg
    {8, -36, 0}, // 10 - l leg
    {9, 32, 145}, // 11 - r foot
    {10, -32, 145}, // 12 - l foot
    {6, 24, -60}, // 13 - r eye
    {6, -24, -60}, // 14 - l eye
    {6, 0, -40}, // 15 - nose
    {6, 30, -80}, // 16 - r brow
    {6, -30, -80}, // 17 - l brow
    {6, 0, -15}, // 18 - mouth
  };

  std::vector<float> mouthProbabilities {
    1.0f,
    1.0f,
    0.8f,
    0.1f,
    0.2f,
    0.6f,
    0.6f
  };

  mouthProbabilities = normalizeProbabilities(mouthProbabilities);
  

  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);
  float scale = 0.45f;

  int skinIndex = randomrange(0, armSprites.size());
  SpriteCoords armSpriteCoord = armSprites[skinIndex];
  SpriteCoords handSpriteCoord = handSprites[skinIndex];
  SpriteCoords neckSpriteCoord = neckSprites[skinIndex];
  SpriteCoords headSpriteCoord = headSprites[skinIndex];
  SpriteCoords legSpriteCoord = legSprites[skinIndex];

  int shoeIndex = randomrange(0,shoeSprites.size());
  SpriteCoords shoeSpriteCoord = shoeSprites[shoeIndex];

  int shirtTorsoIndex = randomrange(0, shirtTorsoSprites.size());
  SpriteCoords shirtTorsoSpriteCoord = shirtTorsoSprites[shirtTorsoIndex];

  int pantsLegColorIndex = randomrange(0, pantsLegSprites.size());
  int pantsLegStyleIndex = randomrange(0, pantsLegSprites[pantsLegColorIndex].size());
  SpriteCoords pantsLegSpriteCoord = pantsLegSprites[pantsLegColorIndex][pantsLegStyleIndex];

  int pantsCrotchColorIndex = pantsLegColorIndex;
  int pantsCrotchStyleIndex = randomrange(0, pantsCrotchSprites[pantsCrotchColorIndex].size());
  SpriteCoords pantsCrotchSpriteCoord = pantsCrotchSprites[pantsCrotchColorIndex][pantsCrotchStyleIndex];

  int torsoColorIndex = randomrange(0, shirtTorsoSprites.size());
  int shirtArmColorIndex = randomrange(0, shirtArmSprites.size());
  int shirtArmStyleIndex = randomrange(0, shirtArmSprites[shirtArmColorIndex].size());
  SpriteCoords torsoSpriteCoord = shirtTorsoSprites[torsoColorIndex];
  SpriteCoords shirtArmSpriteCoord = shirtArmSprites[shirtArmColorIndex][shirtArmStyleIndex];

  int hairIndex = randomrange(0, hairSprites.size());
  SpriteCoords hairSpriteCoord = hairSprites[hairIndex];

  // brows
  int browIndex = randomrange(0, browSprites.size());
  SpriteCoords browSpriteCoord = browSprites[browIndex];
  
  // eyes
  int eyeIndex = randomrange(0, eyeSprites.size());
  SpriteCoords eyeSpriteCoord = eyeSprites[eyeIndex];
  
  // nose
  int noseIndex = randomrange(0, noseSprites.size());
  SpriteCoords noseSpriteCoord = noseSprites[noseIndex];
  
  // mouth
  int mouthIndex = randomFromDistribution(mouthProbabilities);
  SpriteCoords mouthSpriteCoord = mouthSprites[mouthIndex];
  
  
  olc::vf2d vSourceArmPos = {float(armSpriteCoord.x), float(armSpriteCoord.y)};
  olc::vf2d vSourceArmSize = {float(armSpriteCoord.width), float(armSpriteCoord.height)};
    
  olc::vf2d vSourceTorsoPos = {float(torsoSpriteCoord.x), float(torsoSpriteCoord.y)};
  olc::vf2d vSourceTorsoSize = {float(torsoSpriteCoord.width), float(torsoSpriteCoord.height)};

  olc::vf2d vSourceShirtArmPos = {float(shirtArmSpriteCoord.x), float(shirtArmSpriteCoord.y)};
  olc::vf2d vSourceShirtArmSize = {float(shirtArmSpriteCoord.width), float(shirtArmSpriteCoord.height)};

  olc::vf2d vSourceHandPos = {float(handSpriteCoord.x), float(handSpriteCoord.y)};
  olc::vf2d vSourceHandSize = {float(handSpriteCoord.width), float(handSpriteCoord.height)};

  olc::vf2d vSourceNeckPos = {float(neckSpriteCoord.x), float(neckSpriteCoord.y)};
  olc::vf2d vSourceNeckSize = {float(neckSpriteCoord.width), float(neckSpriteCoord.height)};      

  olc::vf2d vSourceHeadPos = {float(headSpriteCoord.x), float(headSpriteCoord.y)};
  olc::vf2d vSourceHeadSize = {float(headSpriteCoord.width), float(headSpriteCoord.height)};      

  olc::vf2d vSourceLegPos = {float(legSpriteCoord.x), float(legSpriteCoord.y)};
  olc::vf2d vSourceLegSize = {float(legSpriteCoord.width), float(legSpriteCoord.height)};

  olc::vf2d vSourcePantsLegPos = {float(pantsLegSpriteCoord.x), float(pantsLegSpriteCoord.y)};
  olc::vf2d vSourcePantsLegSize = {float(pantsLegSpriteCoord.width), float(pantsLegSpriteCoord.height)};
  
  olc::vf2d vSourcePelvisPos = {float(pantsCrotchSpriteCoord.x), float(pantsCrotchSpriteCoord.y)};
  olc::vf2d vSourcePelvisSize = {float(pantsCrotchSpriteCoord.width), float(pantsCrotchSpriteCoord.height)};  
  
  olc::vf2d vSourceShoePos = {float(shoeSpriteCoord.x), float(shoeSpriteCoord.y)};
  olc::vf2d vSourceShoeSize = {float(shoeSpriteCoord.width), float(shoeSpriteCoord.height)};

  olc::vf2d vSourceShirtTorsoPos = {float(shirtTorsoSpriteCoord.x), float(shirtTorsoSpriteCoord.y)};
  olc::vf2d vSourceShirtTorsoSize = {float(shirtTorsoSpriteCoord.width), float(shirtTorsoSpriteCoord.height)};

  olc::vf2d vSourceHairPos = {float(hairSpriteCoord.x), float(hairSpriteCoord.y)};
  olc::vf2d vSourceHairSize = {float(hairSpriteCoord.width), float(hairSpriteCoord.height)};

  olc::vf2d vSourceBrowPos = {float(browSpriteCoord.x), float(browSpriteCoord.y)};
  olc::vf2d vSourceBrowSize = {float(browSpriteCoord.width), float(browSpriteCoord.height)};

  olc::vf2d vSourceEyePos = {float(eyeSpriteCoord.x), float(eyeSpriteCoord.y)};
  olc::vf2d vSourceEyeSize = {float(eyeSpriteCoord.width), float(eyeSpriteCoord.height)};

  olc::vf2d vSourceNosePos = {float(noseSpriteCoord.x), float(noseSpriteCoord.y)};
  olc::vf2d vSourceNoseSize = {float(noseSpriteCoord.width), float(noseSpriteCoord.height)};

  olc::vf2d vSourceMouthPos = {float(mouthSpriteCoord.x), float(mouthSpriteCoord.y)};
  olc::vf2d vSourceMouthSize = {float(mouthSpriteCoord.width), float(mouthSpriteCoord.height)};

  


  olc::vf2d vTorsoOffset = vSourceTorsoSize / 2.0f;
  olc::vf2d vPelvisOffset = vSourcePelvisSize / 2.0f;
  olc::vf2d vRightLegOffset = {42.0f, 16.0f};
  olc::vf2d vLeftLegOffset = {-42.0f, 16.0f};
  olc::vf2d vRightFootOffset = {30.0f, 7.0f};
  olc::vf2d vLeftFootOffset = {-30.0f, 7.0f};
  olc::vf2d vNeckOffset = vSourceNeckSize / 2.0f;
  olc::vf2d vHeadOffset = {vSourceHeadSize.x / 2.0f, 158.0f};
  olc::vf2d vRightArmOffset = {20.0f, 40.0f};
  olc::vf2d vLeftArmOffset = {-20.0f, 40.0f};
  olc::vf2d vRightHandOffset = {24.0f, 13.0f};
  olc::vf2d vLeftHandOffset = {-24.0f, 13.0f};
  olc::vf2d vHairOffset = {vSourceHairSize.x / 2.0f, 75.0f};
  olc::vf2d vRightBrowOffset = vSourceBrowSize / 2.0f;
  olc::vf2d vLeftBrowOffset = {-vSourceBrowSize.x / 2.0f, vSourceBrowSize.y / 2.0f};
  olc::vf2d vRightEyeOffset = vSourceEyeSize / 2.0f;
  olc::vf2d vLeftEyeOffset = {-vSourceEyeSize.x / 2.0f, vSourceEyeSize.y /2.0f};
  olc::vf2d vNoseOffset = vSourceNoseSize / 2.0f;
  olc::vf2d vMouthOffset = vSourceMouthSize / 2.0f;
  

  olc::vf2d vTorsoScreenLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 0) - vTorsoOffset);
  olc::vf2d vPelvisScreenLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 8) - vPelvisOffset);
  olc::vf2d vRightArmScreenLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 1) - vRightArmOffset);
  olc::vf2d vLeftArmScreenLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 2) - vLeftArmOffset);
  olc::vf2d vRightHandLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 3) - vRightHandOffset);
  olc::vf2d vLeftHandLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 4) - vLeftHandOffset);
  olc::vf2d vLeftLegLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 10) - vLeftLegOffset);
  olc::vf2d vRightLegLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 9) - vRightLegOffset);
  olc::vf2d vNeckLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 5) - vNeckOffset);
  olc::vf2d vHeadLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 6) - vHeadOffset);
  olc::vf2d vLeftShoeLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 12) - vLeftFootOffset);
  olc::vf2d vRightShoeLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 11) - vRightFootOffset);
  olc::vf2d vHairLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 7) - vHairOffset);
  olc::vf2d vRightBrowLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 16) - vRightBrowOffset);
  olc::vf2d vLeftBrowLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 17) - vLeftBrowOffset);
  olc::vf2d vRightEyeLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 13) - vRightEyeOffset);
  olc::vf2d vLeftEyeLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 14) - vLeftEyeOffset);
  olc::vf2d vNoseLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 15) - vNoseOffset);
  olc::vf2d vMouthLocation = olc::vf2d(x, y) + scale * (calcScreenLocation(skeleton, 18) - vMouthOffset);

  game->DrawPartialRotatedDecal(vRightLegLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceLegPos,
				vSourceLegSize,
				{scale, scale},
				olc::WHITE);
  
  game->DrawPartialRotatedDecal(vLeftLegLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceLegPos,
				vSourceLegSize,
				{-scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vRightArmScreenLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceArmPos,
				vSourceArmSize,
				{scale, scale},
				olc::WHITE);
  
  game->DrawPartialRotatedDecal(vLeftArmScreenLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceArmPos,
				vSourceArmSize,
				{-scale, scale},
				olc::WHITE);

  
  
  game->DrawPartialRotatedDecal(vLeftShoeLocation,
				m_shoesDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceShoePos,
				vSourceShoeSize,
				{-scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vRightShoeLocation,
				m_shoesDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceShoePos,
				vSourceShoeSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vLeftLegLocation,
				m_pantsDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourcePantsLegPos,
				vSourcePantsLegSize,
				{-scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vRightLegLocation,
				m_pantsDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourcePantsLegPos,
				vSourcePantsLegSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vRightHandLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceHandPos,
				vSourceHandSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vLeftHandLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceHandPos,
				vSourceHandSize,
				{-scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vNeckLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceNeckPos,
				vSourceNeckSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vHeadLocation,
				m_skinDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceHeadPos,
				vSourceHeadSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vHairLocation,
				m_hairDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceHairPos,
				vSourceHairSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vRightEyeLocation,
				m_faceDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceEyePos,
				vSourceEyeSize,
				{scale, scale},
				olc::WHITE);  
  
  game->DrawPartialRotatedDecal(vLeftEyeLocation,
				m_faceDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceEyePos,
				vSourceEyeSize,
				{-scale, scale},
				olc::WHITE);
  /*
  game->DrawPartialRotatedDecal(vRightBrowLocation,
				m_faceDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceBrowPos,
				vSourceBrowSize,
				{scale, scale},
				olc::WHITE);  
  
  game->DrawPartialRotatedDecal(vLeftBrowLocation,
				m_faceDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceBrowPos,
				vSourceBrowSize,
				{-scale, scale},
				olc::WHITE);
  */

  game->DrawPartialRotatedDecal(vNoseLocation,
				m_faceDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceNosePos,
				vSourceNoseSize,
				{scale, scale},
				olc::WHITE);  
  
  game->DrawPartialRotatedDecal(vMouthLocation,
				m_faceDecal,
				0.0f,
				{0.0f, 0.0f}, // center
				vSourceMouthPos,
				vSourceMouthSize,
				{scale, scale},
				olc::WHITE);  
  
  
  

  game->DrawPartialRotatedDecal(vRightArmScreenLocation,
				m_shirtsDecal,
				0.0f,
				{0.0f, 0.0f}, //center vTorsoOffset,
				vSourceShirtArmPos,
				vSourceShirtArmSize,
				{scale, scale},
				olc::WHITE);

  game->DrawPartialRotatedDecal(vLeftArmScreenLocation,
				m_shirtsDecal,
				0.0f,
				{0.0f, 0.0f}, //center vTorsoOffset,
				vSourceShirtArmPos,
				vSourceShirtArmSize,
				{-scale, scale},
				olc::WHITE);
  

  if (m_bDrawPelvis) {
    game->DrawPartialRotatedDecal(vPelvisScreenLocation,
				  m_pantsDecal,
				  0.0f,
				  {0.0f, 0.0f}, //center vTorsoOffset,
				  vSourcePelvisPos,
				  vSourcePelvisSize,
				  {scale, scale},
				  olc::WHITE);
  } else {
    game->DrawRect(vPelvisScreenLocation.x,
		   vPelvisScreenLocation.y,
		   scale * vSourcePelvisSize.x,
		   scale * vSourcePelvisSize.y,
		   olc::Pixel(0, 200, 0));
  }

  if (m_bDrawTorso) {
    game->DrawPartialRotatedDecal(vTorsoScreenLocation,
				  m_shirtsDecal,
				  0.0f,
				  {0.0f, 0.0f}, //center vTorsoOffset,
				  vSourceTorsoPos,
				  vSourceTorsoSize,
				  {scale, scale},
				  olc::WHITE);
  } else {
    game->DrawRect(vTorsoScreenLocation.x,
		   vTorsoScreenLocation.y,
		   scale * vSourceTorsoSize.x,
		   scale * vSourceTorsoSize.y,
		   olc::Pixel(0, 200, 0));
  }

  

  game->SetPixelMode(currentPixelMode);
}


olc::vf2d BuildingGameMode::calcScreenLocation(BoneFrame skeleton[],
					      int boneIndex) const {
  float x = 0;
  float y = 0;

  while (boneIndex >= 0) {
    int parentIndex = skeleton[boneIndex].parentIndex;
    x += skeleton[boneIndex].xRootPos;
    y += skeleton[boneIndex].yRootPos;
    boneIndex = parentIndex;
  }

  return olc::vf2d(x, y);
}
