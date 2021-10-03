#ifndef mode_building_h
#define mode_building_h

#include "olcPixelGameEngine.h"


class CarsWithGuns;
class City;

struct SpriteCoords
{
public:
  int x;
  int y;
  int width;
  int height;
};

struct BoneFrame
{
public:
  int parentIndex;
  float xRootPos;
  float yRootPos;
};

class BuildingGameMode
{
 public:
  void init(olc::Sprite* menuSprite,
	    olc::Sprite* faceSprite,
	    olc::Sprite* hairSprite,
	    olc::Sprite* pantsSprite,
	    olc::Sprite* shirtsSprite,
	    olc::Sprite* shoesSprite,
	    olc::Sprite* skinSprite);

  void setCity(City* city) { m_city = city; }

  void setBuildingIndex(int idx) { m_buildingIndex = idx; }

  bool update(CarsWithGuns* game, float elapsedSeconds);

  void draw(CarsWithGuns* game);

 protected:
  void handleUserInput(CarsWithGuns* game);
  
  void drawPerson(CarsWithGuns* game, int x, int y);

  olc::vf2d calcScreenLocation(BoneFrame skeleton[],
			       int boneIndex) const;

 private:
  City* m_city;
  int m_buildingIndex;

  bool m_bDrawTorso = true;
  bool m_bDrawPelvis = true;

  olc::Sprite* m_menuSprite;
  olc::Sprite* m_faceSprite;
  olc::Sprite* m_hairSprite;
  olc::Sprite* m_pantsSprite;
  olc::Sprite* m_shirtsSprite;
  olc::Sprite* m_shoesSprite;
  olc::Sprite* m_skinSprite;

  olc::Decal* m_faceDecal;
  olc::Decal* m_hairDecal;
  olc::Decal* m_pantsDecal;
  olc::Decal* m_shirtsDecal;
  olc::Decal* m_shoesDecal;
  olc::Decal* m_skinDecal;

  unsigned int m_seed = 0;
};



#endif //mode_building_h
