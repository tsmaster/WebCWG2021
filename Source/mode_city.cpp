// mode_city.cpp

#include "mode_city.h"

#include "carswithguns.h"
#include "city.h"
#include "citymap.h"
#include "constants.h"
#include "coord.h"
#include "gameclock.h"
#include "layers.h"
#include "modemgr.h"
#include "node.h"

CityGameMode::CityGameMode()
{
  m_tileScale = START_TILE_SCALE;
  m_viewRadius = START_VIEW_RADIUS;
}

void CityGameMode::init(olc::Sprite* menuSprite,
			olc::Sprite* citySprite,
			olc::Sprite* carSprite,
			olc::Sprite* missionSprite,
			MissionMgr* missionMgr)
{
  m_centerCoord = Coord(0, 0, 0);
  m_gameClock = new GameClock();
  m_menuSprite = menuSprite;
  m_citySprite = citySprite;
  m_carSprite = carSprite;
  m_missionSprite = missionSprite;
  m_missionMgr = missionMgr;
    
  m_carPos = Vec2i(0, 0);

  m_isFindingPath = false;
  m_isFollowingPath = false;
  m_cityMap = CityMap();
}

void CityGameMode::destroy()
{
  delete(m_gameClock);
  m_gameClock = NULL;
  m_menuSprite = NULL;
  m_citySprite = NULL;
  m_cityMap.destroy();
}

bool CityGameMode::update(CarsWithGuns* game, float elapsedSeconds)
{
  if (m_isFindingPath) {
    for (int i = 0; i < 10; ++i) {
      bool isComplete = m_astar.tick();
      if (isComplete) {
	m_isFindingPath = false;
	m_isFollowingPath = true;
	m_path = m_astar.getSolution();
	m_timeRemainingBeforeMove = m_timeToMove;
	break;
      }
    }
  }

  if (m_isFollowingPath) {
    if (m_path.size() == 0) {
      m_isFollowingPath = false;
    } else {
      if (elapsedSeconds >= m_timeRemainingBeforeMove) {
      
	Vec2i nextPosn = m_path[0];
	m_path.erase(m_path.begin());
      
	//printf("moving to %d %d\n", nextPosn.x, nextPosn.y);

	int dx = nextPosn.x - m_carPos.x;
	int dy = nextPosn.y - m_carPos.y;
	if ((dx == 0) && (dy == 0)) {
	  //printf("actually not moving\n");
	} else {
	  move(dx, dy);
	}

	m_timeRemainingBeforeMove = m_timeToMove;
      } else {
	m_timeRemainingBeforeMove -= elapsedSeconds;
      }
    }
  }
  
  bool bContinue = handleUserInput(game);
  
  return bContinue;
}

void CityGameMode::move(int dx, int dy)
{
  int newHeading = m_carHeading;
  
  if (dx == 1) {
    // east
    newHeading = 0;
  } else if (dy == 1) {
    // north
    newHeading = 2;
  } else if (dx == -1) {
    // west
    newHeading = 4;
  } else {
    // south
    newHeading = 6;
  }

  Vec2i newPos = m_carPos + Vec2i(dx, dy);

  if (m_cityMap.isLocationPaved(newPos)) {
    m_carPos = newPos;
    m_carHeading = newHeading;
  }
}

bool CityGameMode::handleUserInput(CarsWithGuns* game)
{
  bool bTicked = false;

  bool bContinue = true;

  int cx = m_centerCoord.x;
  int cy = m_centerCoord.y;
    
  if (game->GetKey(olc::Key::ESCAPE).bPressed) {
    ModeChangeRequest mcr = ModeChangeRequest::modeChangeRequestFactory(GameMode::GM_HIGHWAY);
    mcr.x = m_city.getCoord().x;
    mcr.y = m_city.getCoord().y;

    printf("in city, requesting exit to pos %d %d\n", mcr.x, mcr.y);
    
    game->requestGameMode(mcr);
  }

  if (game->GetKey(olc::Key::LEFT).bPressed) {
    move(-1, 0);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::RIGHT).bPressed) {
    move(1, 0);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::DOWN).bPressed) {
    move(0, -1);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::UP).bPressed) {
    move(0, 1);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::PGUP).bPressed) {
    m_tileScale = std::min((m_tileScale * 3) / 2, 64.0f);
  }

  if (game->GetKey(olc::Key::PGDN).bPressed) {
    m_tileScale = std::max((m_tileScale * 2) / 3, 2.0f);
  }
  
  if (game->GetKey(olc::Key::NP_ADD).bPressed) {
    m_viewRadius = std::min(m_viewRadius + 0.25f, 32.0f);
  }

  if (game->GetKey(olc::Key::NP_SUB).bPressed) {
    m_viewRadius = std::min(m_viewRadius - 0.25f, 1.0f);
  }
  
  if (game->GetKey(olc::Key::K1).bPressed) {
    printf("center: %s\n", m_centerCoord.toString().c_str());
  }

  if (game->GetKey(olc::Key::R).bPressed) {
    for (Person* p : m_city.getPeople()) {
      printf("%s ", p->m_preferredName.c_str());
      for (PersonAddress fa : p->getFriendAddresses()) {
	if ((fa.wx == m_city.getCoord().x) &&
	    (fa.wy == m_city.getCoord().y)) {
	  printf("L[%d] ", fa.personIndex);
	} else {
	  printf("R[%d] ", fa.personIndex);
	}
      }      
      printf("\n");
    }
    m_bShowingResidents = (!m_bShowingResidents);
  }

  if (game->GetKey(olc::Key::M).bPressed) {
    printf("making mission from within city\n");
    game->generateMissionSequence(m_centerCoord,
				  3,
				  15, 20);
  }

  if (game->GetKey(olc::Key::COMMA).bPressed) {
    printf("advancing mission\n");
    game->progressMissionSequence();
  }    

  if (game->GetMouse(olc::Mouse::LEFT).bPressed) {
    int mx = game->GetMouseX();
    int my = game->GetMouseY();

    Vec2f tileDestFloat = screenToTileCoord(game, Vec2f(mx, my));
    //printf("nav to <%f %f>\n", tileDestFloat.x, tileDestFloat.y);

    m_destTile = Vec2i(int(floor(tileDestFloat.x)),
		       int(floor(tileDestFloat.y + 0.9f))); // TODO fix this hack

    if (m_cityMap.isLocationPaved(m_destTile)) {
      //printf("nav to int <%d %d>\n", m_destTile.x, m_destTile.y);

      std::set<Vec2i> destSet;
      destSet.insert(m_destTile);

      auto expandFunc = [=](Vec2i v){return expandPosn(v);};
      m_astar = bdg_astar::AStar();
      m_astar.requestPath(m_carPos,
			  destSet,
			  expandFunc,
			  64);
      m_isFindingPath = true;
      m_isFollowingPath = false;
    } else {
      int buildingIndex = findBuilding(m_destTile.x, m_destTile.y);
      if (buildingIndex >= 0) {
	Building bldg = m_cityMap.getBuildings()[buildingIndex];
	
	printf("nav to building %d %s\n", buildingIndex,
	       bldg.owner_name.c_str());

	std::set<Vec2i> destSet = getDestinationsForBuilding(buildingIndex);

	auto expandFunc = [=](Vec2i v){return expandPosn(v);};
	       m_astar = bdg_astar::AStar();
	       m_astar.requestPath(m_carPos,
				   destSet,
				   expandFunc,
				   64);
	       m_isFindingPath = true;
	       m_isFollowingPath = false;
      }  else {
	/*
	  printf("not valid dest <%f %f> <%d %d>\n",
	  tileDestFloat.x,
	  tileDestFloat.y,
	  m_destTile.x,
	  m_destTile.y);
	*/
	m_isFindingPath = false;
	m_isFollowingPath = false;
      }
    }
  }  

  if (bTicked) {
    m_gameClock->increment();
  }

  return bContinue;
}

void CityGameMode::draw(CarsWithGuns* game)
{
  game->Clear(olc::DARK_GRAY);

  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

  int pcx = sw / 2;
  int pcy = sh / 2;

  olc::Pixel lineColor = olc::Pixel(25, 150, 25);

  Vec2f topLeftTileCoord = screenToTileCoord(game, Vec2f(0,0));
  Vec2f bottomRightTileCoord = screenToTileCoord(game, Vec2f(sw, sh));

  float leftTileCoord = topLeftTileCoord.x;
  float topTileCoord = topLeftTileCoord.y;

  float rightTileCoord = bottomRightTileCoord.x;
  float bottomTileCoord = bottomRightTileCoord.y;

  for (int x = ceil(leftTileCoord);
       x <= floor(rightTileCoord);
       ++x) {
    Vec2f projVec = tileToScreenCoord(game, Vec2f(x, 0));
    int sx = int(projVec.x);
    game->DrawLine(sx, 0, sx, sh, lineColor);
  }

  for (int y = ceil(bottomTileCoord);
       y <= floor(topTileCoord);
       ++y) {
    Vec2f projVec = tileToScreenCoord(game, Vec2f(0, y));
    int sy = int(projVec.y);
    game->DrawLine(0, sy, sw, sy, lineColor);
  }

  m_cityMap.draw(game);

  if (m_isFollowingPath) {
    for (Vec2i pathpos : m_path) {
      drawPathPos(game, pathpos);
    }
  }

  if (m_isFindingPath) {
    drawCursor(game, 0);
  } else if (m_isFollowingPath) {
    drawCursor(game, 1);
  }
  
  drawCar(game);

  for (Mission* m : m_missionMgr->getMissions()) {
    assert(m != NULL);
    for (MissionStage* ms : m->getStages()) {
      assert(ms != NULL);
      switch (ms->m_state) {
      case MissionStageState::Hidden:
      case MissionStageState::Completed:
	// do nothing
	break;
      case MissionStageState::Available:
	{
	  // draw ? at start location
	  if ((ms->m_startPerson.wx == m_city.getCoord().x) &&
	      (ms->m_startPerson.wy == m_city.getCoord().y)) {
	    drawMissionQuestion(game, ms->m_startPerson.personIndex);
	  }
	}
	break;
      case MissionStageState::InProgress:
	// draw ... at start location
	if ((ms->m_startPerson.wx == m_city.getCoord().x) &&
	    (ms->m_startPerson.wy == m_city.getCoord().y)) {
	  drawMissionDots(game, ms->m_startPerson.personIndex);
	}

	// draw ! at dest location
	if ((ms->m_destPerson.wx == m_city.getCoord().x) &&
	    (ms->m_destPerson.wy == m_city.getCoord().y)) {
	  drawMissionExclamation(game, ms->m_destPerson.personIndex);
	}
	break;
      }
    }
  }  

  m_popupLocationPanel.draw(4, 4, game, m_menuSprite);

  if (m_bShowingResidents) {
    m_residentsPanel.draw(32, 32, game, m_menuSprite);
  }
}

void CityGameMode::drawCar(CarsWithGuns* game)
{
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  int scx = 320;
  int scy = 240;
  
  Vec2i wc = m_carPos;

  Vec2i tc = Vec2i(16 * (m_carHeading & 0x3),
		   16 * (m_carHeading / 4));

  olc::vi2d vScreenLocation = { scx + 16 * wc.x, scy - 16 * wc.y };
  olc::vi2d vTileLocation = {tc.x, tc.y};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_carSprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);
}

void CityGameMode::drawCursor(CarsWithGuns* game, int cursorStyle)
{
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  int scx = 320;
  int scy = 240;
  
  Vec2i wc = m_destTile;

  Vec2i tc;
  if (cursorStyle == 0) {
    tc = Vec2i(10, 16);
  } else {
    tc = Vec2i(2, 15);
  }

  olc::vi2d vScreenLocation = { scx + 16 * wc.x, scy - 16 * wc.y };
  olc::vi2d vTileLocation = {tc.x * 16, tc.y * 16};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_citySprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);
}

void CityGameMode::drawPathPos(CarsWithGuns* game, Vec2i pathPos)
{
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  int scx = 320;
  int scy = 240;
  
  Vec2i wc = pathPos;

  Vec2i tc = Vec2i(10, 17);

  olc::vi2d vScreenLocation = { scx + 16 * wc.x, scy - 16 * wc.y };
  olc::vi2d vTileLocation = {tc.x * 16, tc.y * 16};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_citySprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);
}



Vec2f CityGameMode::screenToTileCoord(CarsWithGuns* game, Vec2f screenCoord)
{
  return m_cityMap.screenToTileCoord(game, screenCoord);
}

Vec2f CityGameMode::tileToScreenCoord(CarsWithGuns* game, Vec2f tileCoord)
{
  return m_cityMap.tileToScreenCoord(game, tileCoord);
}

void CityGameMode::setCity(City c)
{
  m_city = c;
  rebuildDisplay();

  m_cityMap.populate(c.getCoord().x, c.getCoord().y,
		     c.getPopulation(),
		     c.hasExit(0), c.hasExit(1), c.hasExit(2), c.hasExit(3),
		     m_citySprite,
		     &m_city);

  m_carPos = m_cityMap.getCityCenterLocn();
  m_carHeading = 0;

  std::vector<ButtonDesc> buttons;
  std::string resmsg = std::string("Residents:\n\n");
  for (Person* p : m_city.getPeople()) {
    resmsg += p->m_preferredName;
    resmsg += std::string("\n");
  }
  resmsg = resmsg.substr(0, resmsg.size() - 1);
  m_residentsPanel.build(resmsg, buttons);  
}

void CityGameMode::rebuildDisplay()
{
  std::string name = m_city.getName();
  int population = m_city.getPopulation();
  printf("city name: %s pop %d\n", name.c_str(), population);

  // todo better formatting
  std::string msg = name + std::string("\npop: ") +std::to_string(population);
  msg = msg + std::string("\nexits: ");

  if (m_city.hasExit(0)) {
    msg = msg + std::string("E ");
  }
  if (m_city.hasExit(1)) {
    msg = msg + std::string("N ");
  }
  if (m_city.hasExit(2)) {
    msg = msg + std::string("W ");
  }
  if (m_city.hasExit(3)) {
    msg = msg + std::string("S ");
  }
  
  std::vector<ButtonDesc> buttons;
  m_popupLocationPanel.build(msg, buttons);
}

std::vector<bdg_astar::Link> CityGameMode::expandPosn(Vec2i posn)
{
  std::vector<bdg_astar::Link> outLinks;

  std::vector<Vec2i> deltas = {
    Vec2i(-1, 0),
    Vec2i(1, 0),
    Vec2i(0, -1),
    Vec2i(0, 1)};

  for (Vec2i delta: deltas) {
    Vec2i nPos = posn + delta;
    if (m_cityMap.isLocationPaved(nPos)) {
      outLinks.push_back(bdg_astar::Link(nPos, 1.0f));
    }
  }    
  
  return outLinks;
}

int CityGameMode::findBuilding(int wx, int wy)
{
  std::vector<Building> buildings = m_cityMap.getBuildings();
  
  for (int i = 0; i < buildings.size(); ++i) {
    Building bldg = buildings[i];

    if ((wx >= bldg.x) &&
	(wy >= bldg.y) &&
	(wx < bldg.x + bldg.width) &&
	(wy < bldg.y + bldg.height)) {
      return i;
    }
  }
  return -1;
}

std::set<Vec2i> CityGameMode::getDestinationsForBuilding(int buildingIndex)
{
  std::set<Vec2i> outSet;
  Building b = m_cityMap.getBuildings()[buildingIndex];

  for (int x = b.x; x < b.x + b.width; ++x){
    Vec2i nPos(x, b.y - 1);
    if (m_cityMap.isLocationPaved(nPos)) {
      outSet.insert(nPos);
    }
    nPos = Vec2i(x, b.y + b.height);
    if (m_cityMap.isLocationPaved(nPos)) {
      outSet.insert(nPos);
    }
  }

  for (int y = b.y; y < b.y + b.height; ++y){
    Vec2i nPos(b.x - 1, y);
    if (m_cityMap.isLocationPaved(nPos)) {
      outSet.insert(nPos);
    }
    nPos = Vec2i(b.x + b.width, y);
    if (m_cityMap.isLocationPaved(nPos)) {
      outSet.insert(nPos);
    }
  }

  return outSet;
}

void CityGameMode::drawMissionQuestion(CarsWithGuns* game, int personIndex)
{
  Person* person = m_city.getPeople()[personIndex];
  int bldgIndex = person->getBuildingIndex();
  assert (bldgIndex >= 0);

  std::vector<Building> cityBuildings = m_cityMap.getBuildings();

  assert(bldgIndex < cityBuildings.size());
	 
  Building bldg = cityBuildings[bldgIndex];

  Vec2f bldgVec = Vec2f(bldg.x, bldg.y);			  
  Vec2f lowerLeftScreenCoord = tileToScreenCoord(game, bldgVec);
  Vec2f upperRightScreenCoord = tileToScreenCoord(game, bldgVec + Vec2f(1.0f, 1.0f));

  Vec2i midScreenCoord = Vec2i(int((lowerLeftScreenCoord.x + upperRightScreenCoord.x)/2.0f),
			       int((lowerLeftScreenCoord.y + upperRightScreenCoord.y)/2));
  
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  Vec2i tc = Vec2i(0, 0);

  olc::vi2d vScreenLocation = {
    midScreenCoord.x - 8,
    midScreenCoord.y - 8};
  olc::vi2d vTileLocation = {tc.x, tc.y};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_missionSprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);
  
}

void CityGameMode::drawMissionDots(CarsWithGuns* game, int personIndex)
{
  Person* person = m_city.getPeople()[personIndex];
  int bldgIndex = person->getBuildingIndex();
  assert (bldgIndex >= 0);

  std::vector<Building> cityBuildings = m_cityMap.getBuildings();

  assert(bldgIndex < cityBuildings.size());
	 
  Building bldg = cityBuildings[bldgIndex];

  Vec2f bldgVec = Vec2f(bldg.x, bldg.y);			  
  Vec2f lowerLeftScreenCoord = tileToScreenCoord(game, bldgVec);
  Vec2f upperRightScreenCoord = tileToScreenCoord(game, bldgVec + Vec2f(1.0f, 1.0f));

  Vec2i midScreenCoord = Vec2i(int((lowerLeftScreenCoord.x + upperRightScreenCoord.x)/2.0f),
			       int((lowerLeftScreenCoord.y + upperRightScreenCoord.y)/2));
  
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  Vec2i tc = Vec2i(32, 0);

  olc::vi2d vScreenLocation = {
    midScreenCoord.x - 8,
    midScreenCoord.y - 8};
  olc::vi2d vTileLocation = {tc.x, tc.y};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_missionSprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);  
}

void CityGameMode::drawMissionExclamation(CarsWithGuns* game, int personIndex)
{
  Person* person = m_city.getPeople()[personIndex];
  int bldgIndex = person->getBuildingIndex();
  assert (bldgIndex >= 0);

  std::vector<Building> cityBuildings = m_cityMap.getBuildings();

  assert(bldgIndex < cityBuildings.size());
	 
  Building bldg = cityBuildings[bldgIndex];

  Vec2f bldgVec = Vec2f(bldg.x, bldg.y);			  
  Vec2f lowerLeftScreenCoord = tileToScreenCoord(game, bldgVec);
  Vec2f upperRightScreenCoord = tileToScreenCoord(game, bldgVec + Vec2f(1.0f, 1.0f));

  Vec2i midScreenCoord = Vec2i(int((lowerLeftScreenCoord.x + upperRightScreenCoord.x)/2.0f),
			       int((lowerLeftScreenCoord.y + upperRightScreenCoord.y)/2));
  
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  Vec2i tc = Vec2i(16, 0);

  olc::vi2d vScreenLocation = {
    midScreenCoord.x - 8,
    midScreenCoord.y - 8};
  olc::vi2d vTileLocation = {tc.x, tc.y};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_missionSprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);  
}
