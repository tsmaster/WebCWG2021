#ifndef CARD_H
#define CARD_H

#include <string>

#include "olcPixelGameEngine.h"
#include "entt.hpp"

const int CARD_WIDTH = 24;
const int CARD_HEIGHT = 34;

enum Suit
{
 SUIT_BIRD, // ??
 SUIT_COIN,
 SUIT_CUBE,
 SUIT_HAND, // ??
 SUIT_SHIELD,
 SUIT_SWORD,

 SUIT_LAST,
};

enum ClassicSuit
{
 CL_SUIT_NONE,
 CL_SUIT_CLUB,
 CL_SUIT_DIAMOND,
 CL_SUIT_HEART,
 CL_SUIT_SPADE,

 CL_SUIT_LAST
};

enum Rank
{
 RANK_ACE,
 RANK_TWO,
 RANK_THREE,
 RANK_FOUR,
 RANK_FIVE,
 RANK_SEVEN,
 RANK_TEN,
 RANK_TWENTY,
 RANK_ROGUE,
 RANK_PRINCESS,
 RANK_KNIGHT,
 RANK_QUEEN,
 RANK_KING,

 RANK_LAST
};

enum ClassicRank
{
 CL_RANK_NONE,
 CL_RANK_ACE,
 CL_RANK_TWO,
 CL_RANK_THREE,
 CL_RANK_FOUR,
 CL_RANK_FIVE,
 CL_RANK_SIX,
 CL_RANK_SEVEN,
 CL_RANK_EIGHT,
 CL_RANK_NINE,
 CL_RANK_TEN,
 CL_RANK_JACK,
 CL_RANK_QUEEN,
 CL_RANK_KING,

 CL_RANK_LAST
};
 

class Card
{
 public:
  Suit suit;
  Rank rank;

  bool faceUp;
  int x;
  int y;

  Card(Suit s, Rank r);

  void draw(olc::PixelGameEngine* drawer);

  bool hit(int x, int y);
};

struct ClassicCardTemplateComponent
{
  ClassicSuit suit;
  ClassicRank rank;
  int value;
  std::string name;
  
  olc::Sprite* sprSmFront;
  olc::Decal* decSmFront;
  olc::Sprite* sprMdFront;
  olc::Decal* decMdFront;
  olc::Sprite* sprLgFront;
  olc::Decal* decLgFront;
};

struct ClassicCardInstanceComponent
{
  float x;
  float y;
  float scale;
  float rotation;
  bool bFaceUp;

  bool bHasCardBelow;
  entt::entity eCardBelow;
  bool bHasCardAbove;
  entt::entity eCardAbove;

  bool bIsInHand;
  int handHeight; // 0 = first card, -1 = not in hand

  int deckIndex;
};

struct ClassicCardAnimationComponent
{
  float start_time;
  float end_time;

  float start_x;
  float start_y;
  float start_rot;

  float end_x;
  float end_y;
  float end_rot;

  bool bActive;

  // TODO animation curve enum linear, fast out/slow in, etc
};

#endif //CARD_H
