// node.cpp

#include "node.h"

#include "coord.h"
#include "mode_highway.h"

// TODO port node


Node::Node(int x, int y, int h, NodeMgr* nodeMgr)
{
  m_nodeMgr = nodeMgr;
  m_coord = new Coord(x, y, h);
}

Node::Node(Coord c, NodeMgr* nodeMgr)
{
  m_nodeMgr = nodeMgr;
  m_coord = new Coord(c.x, c.y, c.h);
}

void Node::draw(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  int xLeft, yBottom, xRight, yTop;
  getBaseExtents(xLeft, yBottom, xRight, yTop);

  Vec2f screenBottomLeft = mode->tileToScreenCoord(pge, Vec2f(xLeft, yBottom));
  Vec2f screenTopRight = mode->tileToScreenCoord(pge, Vec2f(xRight, yTop));

  int sLeft = int(screenBottomLeft.x);
  int sBottom = int(screenBottomLeft.y);
  int sRight = int(screenTopRight.x);
  int sTop = int(screenTopRight.y);

  if (m_coord->h == 0) {
    pge->FillRect(sLeft, sBottom, sRight-sLeft, sTop-sBottom, m_color);
    drawRoads(pge, mode);
    if (m_isCity) {
      pge->FillCircle((sRight + sLeft) / 2,
		      (sTop + sBottom) / 2,
		      (mode->getTileScale() * 3) / 8,
		      olc::Pixel(50, 50, 50));
    }      
  } else {
    pge->DrawRect(sLeft, sBottom, sRight-sLeft, sTop-sBottom, m_color);
  }
}

void Node::drawLabel(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  // TODO label
}

void Node::drawRoads(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  // TODO draw roads

}


void Node::getBaseExtents(int& outLeft, int& outBottom,
			  int& outRight, int& outTop)
{
  // TODO extents
  outLeft = 0;
  outRight = 0;
  outBottom = 0;
  outTop = 0;
  
}
