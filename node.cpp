// node.cpp

#include "node.h"

#include "constants.h"
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
  
  Node::calcExtents(m_coord->x,
		    m_coord->y,
		    m_coord->h,
		    outLeft, outBottom,
		    outRight, outTop);
}


void Node::calcExtents(int x, int y, int h,
		       int& outLeft, int& outBottom,
		       int& outRight, int& outTop)
{
  if (h == 0) {
    outLeft = x;
    outBottom = y;
    outRight = x+1;
    outTop = y+1;
    return;
  }

  // TODO handle odd and even height offset correctly
  int newH = h - 1;
  int newLeft = x * SCALE_FACTOR - ODD_HEIGHT_OFFSET;
  int newBottom = y * SCALE_FACTOR - ODD_HEIGHT_OFFSET;

  int newRight = newLeft + SCALE_FACTOR;
  int newTop = newBottom + SCALE_FACTOR;

  int newBLL, newBLB, newBLR, newBLT;
  int newTRL, newTRB, newTRR, newTRT;
  
  calcExtents(newLeft, newBottom, newH, newBLL, newBLB, newBLR, newBLT);
  calcExtents(newRight, newTop, newH, newTRL, newTRB, newTRR, newTRT);

  outLeft = newBLL;
  outBottom = newBLB;
  outRight = newTRR;
  outTop = newTRT;
}
