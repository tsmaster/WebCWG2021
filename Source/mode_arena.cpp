#include "mode_arena.h"

#include "arena_ai_controller.h"
#include "bdg_car.h"
#include "bdg_math.h"
#include "bdg_random.h"
#include "carswithguns.h"


void ArenaGameMode::init(olc::Sprite* car_00_Sprite,
			 olc::Sprite* car_01_Sprite,
			 olc::Sprite* car_02_Sprite,
			 olc::Sprite* car_03_Sprite,
			 olc::Sprite* car_04_Sprite,
			 olc::Sprite* car_05_Sprite,
			 olc::Sprite* car_06_Sprite,
			 olc::Sprite* car_07_Sprite,
			 olc::Sprite* arena_floor_Sprite,
			 olc::Sprite* barrel_Sprite)
{
  m_spriteVec.push_back(car_00_Sprite);
  m_spriteVec.push_back(car_01_Sprite);
  m_spriteVec.push_back(car_02_Sprite);
  m_spriteVec.push_back(car_03_Sprite);
  m_spriteVec.push_back(car_04_Sprite);
  m_spriteVec.push_back(car_05_Sprite);
  m_spriteVec.push_back(car_06_Sprite);
  m_spriteVec.push_back(car_07_Sprite);
  m_arenaFloorSprite = arena_floor_Sprite;

  m_decalVec.push_back(new olc::Decal(car_00_Sprite));
  m_decalVec.push_back(new olc::Decal(car_01_Sprite));
  m_decalVec.push_back(new olc::Decal(car_02_Sprite));
  m_decalVec.push_back(new olc::Decal(car_03_Sprite));
  m_decalVec.push_back(new olc::Decal(car_04_Sprite));
  m_decalVec.push_back(new olc::Decal(car_05_Sprite));
  m_decalVec.push_back(new olc::Decal(car_06_Sprite));
  m_decalVec.push_back(new olc::Decal(car_07_Sprite));

  m_arenaFloorDecal = new olc::Decal(arena_floor_Sprite);

  m_barrelSprite = barrel_Sprite;
  m_barrelDecal = new olc::Decal(barrel_Sprite);

  m_cars.push_back(new Bdg_Car({0.0f, 0.0f}, degToRad(90), m_decalVec[0], "Player"));
  //m_cars.push_back(new Bdg_Car({-290.0f, -300.0f}, degToRad(180), m_decalVec[1]));

  m_cars.push_back(new Bdg_Car({0.0f, -50.0f}, 0.0f, m_decalVec[1], "Black"));
  m_cars.push_back(new Bdg_Car({50.0f, 0.0f}, 0.0f, m_decalVec[2], "Two White"));
  m_cars.push_back(new Bdg_Car({0.0f, 50.0f}, 0.0f, m_decalVec[3], "Three Yellow Green"));
  m_cars.push_back(new Bdg_Car({-50.0f, 0.0f}, 0.0f, m_decalVec[4], "Four Blue Green"));
  m_cars.push_back(new Bdg_Car({-120.0f, -240.0f}, 0.0f, m_decalVec[5], "Five"));
  m_cars.push_back(new Bdg_Car({-350.0f, -0.0f}, 0.0f, m_decalVec[6], "Six"));
  m_cars.push_back(new Bdg_Car({-240.0f, -120.0f}, 0.0f, m_decalVec[7], "Seven"));

  for (float fx = -400.0f; fx < 400.0f; fx += 100.0f) {
    for (float fy = -400.0f; fy < 400.0f; fy += 100.0f) {
      m_floors.push_back(WorldQuad::MakeFromAABB(Vec2f(fx, fy + 100.0f),
						 Vec2f(fx + 100.0f, fy),
						 m_arenaFloorDecal, olc::WHITE, 0));
    }
  }

  for (int i = 0; i < 8; ++i) {
    m_aiController[i].setMode(this);
    m_aiController[i].setCar(m_cars[i]);

    if (i != 0) {
      m_cars[i]->setController(&(m_aiController[i]));
    }
  }

  /*
  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(0.0f, 0.0f),
					    Vec2f(50.0f, 50.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));*/
  
  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(100.0f,50.0f),
					    Vec2f(200.0f,-50.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(-200.0f,50.0f),
					    Vec2f(-100.0f,-50.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(-50.0f,100.0f),
					    Vec2f(50.0f,200.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(50.0f,-100.0f),
					    Vec2f(-50.0f,-200.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(-500.0f,500.0f),
					    Vec2f(-400.0f,-500.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(500.0f,500.0f),
					    Vec2f(400.0f,-500.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(-200.0f,-400.0f),
					    Vec2f(200.0f,-500.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad::MakeFromAABB(Vec2f(-200.0f,400.0f),
					    Vec2f(200.0f,500.0f),
					    m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad(Vec2f(-500.0f, -100.0f),
			      Vec2f(-100.0f, -500.0f),
			      Vec2f(-100.0f, -600.0f),
			      Vec2f(-500.0f, -600.0f),
			      m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad(Vec2f(500.0f, -100.0f),
			      Vec2f(100.0f, -500.0f),
			      Vec2f(100.0f, -600.0f),
			      Vec2f(500.0f, -600.0f),
			      m_arenaFloorDecal, olc::BLACK, 1));
  
  m_walls.push_back(WorldQuad(Vec2f(-500.0f, 100.0f),
			      Vec2f(-100.0f, 500.0f),
			      Vec2f(-100.0f, 600.0f),
			      Vec2f(-500.0f, 600.0f),
			      m_arenaFloorDecal, olc::BLACK, 1));

  m_walls.push_back(WorldQuad(Vec2f(500.0f, 100.0f),
			      Vec2f(100.0f, 500.0f),
			      Vec2f(100.0f, 600.0f),
			      Vec2f(500.0f, 600.0f),
			      m_arenaFloorDecal, olc::BLACK, 1));


  olc::Pixel goalColor = olc::Pixel(128, 128, 128, 128);
  //olc::Pixel goalColor = olc::DARK_GRAY;
  
  m_goals.push_back(WorldQuad::MakeFromAABB(Vec2f(-100, -10),
					    Vec2f(-80, 10),
					    m_arenaFloorDecal, goalColor, 2));
    
  m_goals.push_back(WorldQuad::MakeFromAABB(Vec2f(80, -10),
					    Vec2f(100, 10),
					    m_arenaFloorDecal, goalColor, 2));

  m_goals.push_back(WorldQuad::MakeFromAABB(Vec2f(-10, -100),
					    Vec2f(10, -80),
					    m_arenaFloorDecal, goalColor, 2));
    
  m_goals.push_back(WorldQuad::MakeFromAABB(Vec2f(-10, 80),
					    Vec2f(10, 100),
					    m_arenaFloorDecal, goalColor, 2));
    
  printf("about to make waypoints\n");
  makeWaypoints(-400.0f, 400.0f,
		-400.0f, 400.0f, 50.0f);

  // init camera
  //m_camera.setScale(2.5f);
  //m_camera.setScale(25.0f);
  m_camera.setScale(10.0f);
  m_camera.setRotation(0.0f);

  // TODO move this elsewhere
  olc::GamePad::init();

  printf("gamepad initted\n");

  auto gamepads = olc::GamePad::getGamepads();

  printf("gamepads size %ld\n", gamepads.size());

  for (int gpi = 0; gpi < gamepads.size(); ++gpi) {
    std::string gp_name = gamepads[gpi]->getName();
    printf("[%02d] %s\n", gpi, gp_name.c_str());
  }

  for (int i = 0; i < 10; ++i) {
    addRandomBarrel();
  }
}

void ArenaGameMode::makeWaypoints(float xMin, float xMax,
				  float yMin, float yMax,
				  float cellsize) {
  for (int xi = 0; xi * cellsize + xMin <= xMax; ++ xi) {
    float cellLeft = xi * cellsize + xMin;
    float cellRight = cellLeft + cellsize;
    for (int yi = 0; yi * cellsize + yMin <= yMax; ++ yi) {
      float cellBottom = yi * cellsize + yMin;
      float cellTop = cellBottom + cellsize;

      float rx = rand_frange(cellLeft, cellRight);
      float ry = rand_frange(cellBottom, cellTop);

      //float rx = cellLeft;
      //float ry = cellBottom;

      //printf("making waypoint %f %f\n", rx, ry);

      Vec2f newPoint(rx, ry);

      bool inWall = false;
      for (const WorldQuad& w : m_walls) {
	if (w.pointInside(newPoint)) {
	  inWall = true;
	  break;
	}
      }

      if (inWall) {
	//printf("in wall\n");
      } else {
	m_waypoints.push_back(Vec2f(rx, ry));
      }
    }
  }

  for (int i = 0; i < m_waypoints.size(); ++i) {
    Vec2f& wpi = m_waypoints[i];
    for (int j = i+1; j < m_waypoints.size(); ++j) {
      Vec2f& wpj = m_waypoints[j];

      float dist = (wpj-wpi).len();
      if (dist < 2.5 * cellsize) {
	//printf("waypoints %d, %d dist %f\n", i, j, dist);
	//printf("wp %d <%f %f>\n", i, wpi.x, wpi.y);
	//printf("wp %d <%f %f>\n", j, wpj.x, wpj.y);

	bool isObstructed = false;
	Vec2f direction = wpj-wpi;
	Vec2f outIntersection(0.0f,0.0f);
	for (int wallIndex = 0; wallIndex < m_walls.size(); ++wallIndex) {
	  //for (WorldQuad& wall : m_walls) {
	  WorldQuad& wall = m_walls[wallIndex];
	  //printf("=====\n");
	  //printf("testing wall #%d\n", wallIndex);
	  //wall.print();
	  
	  if (wall.raycast(wpi, direction, outIntersection)){
	    isObstructed = true;
	    //printf("obstructed by wall # %d\n", wallIndex);
	    //wall.print();
	    break;
	  }
	}
	if (isObstructed) {
	  //printf("obstructed\n");
	} else {
	  //printf("connected\n");
	  m_waypointLinks.push_back(std::pair(i,j));
	}
      }
    }
  }
}

bool ArenaGameMode::update(CarsWithGuns* game, float elapsedSeconds)
{
  handleUserInput(game, elapsedSeconds);

  m_physicsJuice += elapsedSeconds;

  while (m_physicsJuice > m_physicsFrameTime) {
    for (Bdg_Car* car : m_cars) {
      CarController* cc = car->getController();
      if (cc != NULL) {
	cc->tick(m_physicsFrameTime);
      }	
    }
    
    for (Bdg_Car* car : m_cars) {
      car->updatePhysics(m_physicsFrameTime, m_walls, this);
    }

    for (ArenaBarrel* barrel : m_barrels) {
      barrel->tickPhysics(m_physicsFrameTime);
    }

    m_physicsJuice -= m_physicsFrameTime;
  }

  for (int carIndex = 0; carIndex < m_cars.size(); ++carIndex) {
    Bdg_Car* car = m_cars[carIndex];
    if (car->canDropBarrel()) {
      for (WorldQuad& w : m_goals) {
	if (w.pointInside(car->getPosition())) {
	  car->dropBarrel();
	  score(carIndex, 1);
	}
      }
    }
  }

  return true;
}

void ArenaGameMode::setPlayerCar(int carNum)
{
  // remove old car control
  m_cars[m_playerControlledCarIndex]->setController(NULL);

  // set new car control
  m_playerControlledCarIndex = carNum;
  m_cars[m_playerControlledCarIndex]->setController(&m_gamepadController);  
}

void ArenaGameMode::handleUserInput(CarsWithGuns* game, float elapsedSeconds)
{
  if (m_gamepad == NULL || !m_gamepad->stillConnected) {
    //m_gamepad = olc::GamePad::selectWithButton(olc::GPButtons::SELECT);

    m_gamepad = olc::GamePad::selectWithButton(olc::GPButtons::FACE_D);

    if (m_gamepad != NULL) {
      printf("Binding gamepad\n");
      m_gamepadController.setGamepad(m_gamepad);
      setPlayerCar(0);
    }
    return;
  }

  if (game->GetKey(olc::Key::K1).bPressed) {
    setPlayerCar(0);
  }
  else if (game->GetKey(olc::Key::K2).bPressed) {
    setPlayerCar(1);
  }
  else if (game->GetKey(olc::Key::K3).bPressed) {
    setPlayerCar(2);
  }
  else if (game->GetKey(olc::Key::K4).bPressed) {
    setPlayerCar(3);
  }
  else if (game->GetKey(olc::Key::K5).bPressed) {
    setPlayerCar(4);
  }
  else if (game->GetKey(olc::Key::K6).bPressed) {
    setPlayerCar(5);
  }
  else if (game->GetKey(olc::Key::K7).bPressed) {
    setPlayerCar(6);
  }
  else if (game->GetKey(olc::Key::K8).bPressed) {
    setPlayerCar(7);
  }

  Bdg_Car* car = m_cars[m_playerControlledCarIndex];

  if (m_gamepad) {
    /*
    if (m_gamepad->getButton(olc::GPButtons::FACE_L).bPressed) {
      printf("stop!\n");
      car->stop();
    }
    
    float inSteer = m_gamepad->getAxis(olc::GPAxes::LX);
    float inThrottle = m_gamepad->getAxis(olc::GPAxes::TR);
    float inBrake = m_gamepad->getAxis(olc::GPAxes::TL);

    car->setSteer(inSteer);
    car->setThrottle(inThrottle);
    car->setBrake(inBrake);

    if ((inSteer != 0) ||
	(inThrottle != 0) ||
	(inBrake != 0)) {
    }
    */

    // toggle debug waypoint display

    if (m_gamepad->getButton(olc::GPButtons::FACE_U).bPressed) {
      m_bDrawGrid = !m_bDrawGrid;
    }
    

    // update camera zoom, rot
    float inZoom = m_gamepad->getAxis(olc::GPAxes::RY);
    float z = fmap(inZoom, -1.0f, 1.0f, -0.1f, 0.1f);
    float zps = z * elapsedSeconds + 1.0f;
    m_camera.setScale(m_camera.getScale() * zps);
  } else {
    /*
    car->setSteer(0.0f);
    car->setThrottle(0.0f);
    car->setBrake(0.0f);
    */
  }
}

void ArenaGameMode::draw(CarsWithGuns* game)
{
  game->Clear(olc::GREEN);

  // TODO move this to init
  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

  m_camera.setScreenSize(Vec2f(sw, sh));

  Bdg_Car* playerCar = m_cars[m_playerControlledCarIndex];
  m_camera.setPosition(playerCar->getPosition());

  float floorScale = m_camera.getScale();
  const float floorWidth = 800.0f * floorScale;
  const float floorHeight = 800.0f * floorScale;

  // draw floor(s)
  for (WorldQuad& w : m_floors) {
    w.draw(game, m_camera);
  }

  // draw goals
  for (WorldQuad& w : m_goals) {
    w.draw(game, m_camera);
  }

  // draw barrels
  for (ArenaBarrel* b : m_barrels) {
    b->draw(game, m_camera);
  }

  // draw cars
  for (Bdg_Car* c : m_cars) {
    c->draw(game, m_camera);
  }

  // draw walls
  for (WorldQuad& w : m_walls) {
    w.draw(game, m_camera);
  }

  if (m_bDrawGrid) {
    std::vector<Vec2f> screenWaypoints;
    for (Vec2f& wp : m_waypoints) {
      Vec2f screenPosn = m_camera.worldPosToScreenPos(wp);
      screenWaypoints.push_back(screenPosn);
    }
  
    for (std::pair<int, int> link: m_waypointLinks) {
      int i = link.first;
      int j = link.second;
      Vec2f& vi = screenWaypoints[i];
      Vec2f& vj = screenWaypoints[j];
      
      game->DrawLineDecal({vi.x, vi.y},
  			{vj.x, vj.y},
  			olc::GREEN);
  			
    }
  
    for (Vec2f& wp : m_waypoints) {
      Vec2f screenPosn = m_camera.worldPosToScreenPos(wp);
  
      olc::vf2d ul = {screenPosn.x - 2,
        screenPosn.y - 2};
      olc::vf2d sz = {4, 4};
      game->GradientFillRectDecal(ul, sz,
  				olc::GREEN,
  				olc::GREEN,
  				olc::GREEN,
  				olc::GREEN);
    }
  }
  // draw dashboard display
  game->FillRectDecal({sw - 100.0f, sh - 100.0f}, {100.0f, 100.0f}, olc::BLACK);

  char speedBuffer[40];
  sprintf(speedBuffer, "SPD: %0.1f", m_cars[m_playerControlledCarIndex]->getSpeed());
  std::string speedString(speedBuffer);
  game->DrawStringDecal({sw- 80.0f, sh - 80.0f}, speedString, olc::GREEN);

  char xBuffer[40];
  sprintf(xBuffer, "X: %0.1f", m_cars[m_playerControlledCarIndex]->getPosition().x);
  std::string xString(xBuffer);
  game->DrawStringDecal({sw- 80.0f, sh - 60.0f}, xString, olc::GREEN);

  char yBuffer[40];
  sprintf(yBuffer, "Y: %0.1f", m_cars[m_playerControlledCarIndex]->getPosition().y);
  std::string yString(yBuffer);
  game->DrawStringDecal({sw- 80.0f, sh - 40.0f}, yString, olc::GREEN);

  char aBuffer[40];
  sprintf(aBuffer, "A: %0.1f", m_cars[m_playerControlledCarIndex]->getHeading());
  std::string aString(aBuffer);
  game->DrawStringDecal({sw- 80.0f, sh - 20.0f}, aString, olc::GREEN);
}

void ArenaGameMode::addRandomBarrel()
{
  float x = rand_frange(-100.0f, 100.0f);
  float y = rand_frange(-100.0f, 100.0f);

  printf("placing barrel at %f %f\n", x, y);

  m_barrels.push_back(new ArenaBarrel(Vec2f(x,y), m_barrelDecal));
}

void ArenaGameMode::score(int carIndex, int points)
{
  if (m_scores.find(carIndex) == m_scores.end()) {
    m_scores[carIndex] = points;
  } else {
    m_scores[carIndex] += points;
  }

  for (int i = 0; i < m_cars.size(); ++i) {
    int score = 0;
    if (m_scores.find(i) != m_scores.end()) {
      score = m_scores[i];
    }

    printf("Car [%d] %s : %d\n", i, m_cars[i]->getName().c_str(), score);
  }
}
