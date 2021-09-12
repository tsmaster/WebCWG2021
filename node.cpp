// node.cpp

#include "node.h"

#include "city.h"
#include "constants.h"
#include "coord.h"
#include "mode_highway.h"


Node::Node(int x, int y, int h, NodeMgr* nodeMgr)
{
  m_nodeMgr = nodeMgr;
  m_coord = new Coord(x, y, h);
  m_color = olc::Pixel(0, 0, 200);
  m_isCity = false;
  m_city = NULL;
  m_populatedLayer = TileLayer::EMPTY;
}

void Node::destroy()
{
  delete m_coord;
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

  //printf("sl: %d sb: %d sr: %d st: %d\n", sLeft, sBottom, sRight, sTop);

  if (m_coord->h == 0) {
    pge->FillRect(sLeft, sTop, sRight-sLeft, sBottom-sTop, m_color);
    drawRoads(pge, mode);
    if (m_isCity) {
      pge->FillCircle((sRight + sLeft) / 2,
		      (sTop + sBottom) / 2,
		      (mode->getTileScale() * 3) / 8,
		      olc::Pixel(50, 50, 50));
    }      
  } else {
    //printf("drawing node at %s\n", m_coord->toString().c_str());
    //printf("l: %d, b: %d r: %d t: %d\n", xLeft, yBottom, xRight, yTop);
    
    pge->DrawRect(sLeft, sTop, sRight-sLeft, sBottom-sTop, m_color);
  }
}

void Node::drawLabel(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  if (m_isCity) {
    int xLeft, yBottom, xRight, yTop;
    getBaseExtents(xLeft, yBottom, xRight, yTop);

    Vec2f screenBottomLeft = mode->tileToScreenCoord(pge, Vec2f(xLeft, yBottom));

    olc::Pixel color = olc::Pixel(0, 0, 150);
    std::string cityName = std::string("C");
    if (m_city != NULL) {
      cityName = m_city->getName();
    }
    pge->DrawString(int(screenBottomLeft.x), int(screenBottomLeft.y),
		    cityName, color);
  }
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

/// outLeft is left
/// outRight is outside
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

  //printf("calcing extents for x %d y %d h %d\n", x, y, h);
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
  outRight = newTRL;
  outTop = newTRB;

  //printf("outLeft: %d outRight: %d\n", outLeft, outRight);
}


void Node::populate(TileLayer newLayer)
{
  if (m_populatedLayer >= newLayer) {
    return;
  }

  m_populatedLayer = newLayer;

  /*
    printf("populating x %d y %d h %d l %d\n",
	 m_coord->x,
	 m_coord->y,
	 m_coord->h,
	 int(newLayer));
  */

  if (isOrigin()) {
    if (m_coord->h == 0) {
      constrainFromNothing();
    } else {
      Coord childCoord = Coord(m_coord->x,
			       m_coord->y,
			       m_coord->h - 1);
      
      Node* childNode = m_nodeMgr->getNode(childCoord, newLayer);
      constrainFromChild(*childNode);
    }
  } else {
    Coord parentCoord = getParentCoord();
    Node* parentNode = m_nodeMgr->getNode(parentCoord, newLayer);
    constrainFromParent(*parentNode);
  }

  // roads
  if (newLayer >= TileLayer::H1_CROSS_TILE_ROADS) {
    if (m_coord->h == 1) {
      // TODO neighborNode
      //paveCrossTileRoad(neighborNode);
    } else if (m_coord->h == 0) {
      Coord parentCoord = getParentCoord();
      Node* parentNode = m_nodeMgr->getNode(parentCoord, newLayer);
    }
  }
}

bool Node::isOrigin() const
{
  return ((m_coord->x == 0) &&
	  (m_coord->y == 0));
}

void Node::constrainFromNothing()
{
  // TODO constrain from nothing
}

void Node::constrainFromChild(Node& childNode)
{
  // TODO constrain from child
}

void Node::constrainFromParent(Node& parentNode)
{
  // TODO constrain from parent
}

Coord Node::getParentCoord()
{
  // TODO handle odd height offset
  int px = (m_coord->x + ODD_HEIGHT_OFFSET) / SCALE_FACTOR;
  int py = (m_coord->y + ODD_HEIGHT_OFFSET) / SCALE_FACTOR;
  return Coord(px, py, m_coord->h + 1);
}
