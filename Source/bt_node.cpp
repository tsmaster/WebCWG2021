#include "bt_node.h"

#include <cassert>
#include <cstdio>

#include "bdg_car.h"

BtNode::BtNode()
{
}

void BtNode::add(std::unique_ptr<BtNode> child)
{
  printf("pushing %s\n", child->getName().c_str());
  m_children.push_back(std::move(child));
}

BtResult BtNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  // should never run
  assert(false);
  return BtResult::BT_Running;
}

BtResult SelectorNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  //printf("in selectorNode tick\n");
  int startingIndex;
  
  if (m_bIsRunning) {
    startingIndex = m_currentlyRunningChild;
  } else {
    startingIndex = 0;
  }
    
  for (int i = startingIndex; i < m_children.size(); ++i) {
    //printf("about to tick %d %s\n", i, m_children[i]->getName().c_str());
    BtResult childResult = m_children[i]->tick(game, mode, car, dt);
    //printf("result: %d\n", int(childResult));
    
    if (childResult == BtResult::BT_Running) {
      m_bIsRunning = true;
      m_currentlyRunningChild = i;
      return childResult;
    }
    
    if (childResult == BtResult::BT_Success) {
      m_bIsRunning = false;
      return childResult;
    }
    
    // else, continue iteration
  }
  m_bIsRunning = false;
  m_currentlyRunningChild = -1;
  return BtResult::BT_Failure;
}




BtResult SequenceNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  //printf("--in sequence node tick\n");
  int startingIndex;
  
  if (m_bIsRunning) {
    startingIndex = m_currentlyRunningChild;
  } else {
    startingIndex = 0;
  }
    
  for (int i = startingIndex; i < m_children.size(); ++i) {
    //printf("--about to tick child %d %s\n", i, m_children[i]->getName().c_str());
    BtResult childResult = m_children[i]->tick(game, mode, car, dt);
    //printf("--got childResuld %d\n", int(childResult));
    
    if (childResult == BtResult::BT_Running) {
      m_bIsRunning = true;
      m_currentlyRunningChild = i;
      return childResult;
    }
    
    if (childResult == BtResult::BT_Failure) {
      m_bIsRunning = false;
      return childResult;
    }
    
    // else, continue iteration
  }
  m_bIsRunning = false;
  m_currentlyRunningChild = -1;
  return BtResult::BT_Success;
}

/*
void InverterNode::add(std::unique_ptr<BtNode> child)
{
  assert(m_children.size() == 0);
  BtNode::add(child);
  }*/

BtResult InverterNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  assert(m_children.size() == 1);

  BtResult childResult = m_children[0]->tick(game, mode, car, dt);

  switch(childResult) {
  case BtResult::BT_Running: return BtResult::BT_Running;
  case BtResult::BT_Success: return BtResult::BT_Failure;
  case BtResult::BT_Failure: return BtResult::BT_Success;
  default:
    assert(false);
  }
}


// BarrelSensorNode

BtResult BarrelSensorNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  if (car->hasBarrel()) {
    //printf("has barrel\n");
    return BtResult::BT_Success;
  } else {
    //printf("no barrel\n");
    return BtResult::BT_Failure;
  }
}

// SortLosNode

SortLosNode::SortLosNode(BarrelModeFeature target)
{
  m_target = target;
}

BtResult SortLosNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  Vec2f carPos = car->getPosition();
  
  switch (m_target) {
  case BarrelModeFeature::BMF_Barrel:
    {
      float bestDist = -1.0f;
      ArenaBarrel* bestBarrel = NULL;
    
      for (ArenaBarrel* barrel : mode->getBarrels()) {
	Bdg_Car* barrelOwner = barrel->getOwningCar();
	if (barrelOwner == car) {
	  continue;
	}

	if (!barrel->getIsAlive()) {
	  continue;
	}

	// TODO verify LOS
	
	Vec2f barrelPos = barrel->getPosition();

	Vec2f delta = barrelPos - carPos;
	
	float deltaLen = delta.len();
	
	if ((bestBarrel == NULL) ||
	    (deltaLen < bestDist)) {
	  bestBarrel = barrel;
	  bestDist = deltaLen;
	}
      }

      if (bestBarrel != NULL) {
	Vec2f bestPos = bestBarrel->getPosition();
	//printf("BT selected barrel posn %f %f\n", bestPos.x, bestPos.y);
	car->setTargetPos(bestBarrel->getPosition());
	return BtResult::BT_Success;
      }
      return BtResult::BT_Failure;
    }
  case BarrelModeFeature::BMF_Goal:
    {
      float bestDist = -1.0f;
      Vec2f bestDest(0.0f, 0.0f);
      
      for (WorldQuad& goal : mode->getGoals()) {
	// TODO verify LOS

	Vec2f nearPoint = goal.centerPoint();

	Vec2f delta = nearPoint - carPos;
	
	float deltaLen = delta.len();
	
	if ((bestDist < 0.0f) ||
	    (deltaLen < bestDist)) {
	  bestDest = nearPoint;
	  bestDist = deltaLen;
	}
      }

      if (bestDist >= 0.0f) {
	//printf("BT selected goal posn %f %f\n", bestDest.x, bestDest.y);
	car->setTargetPos(bestDest);
	return BtResult::BT_Success;
      }
      return BtResult::BT_Failure;
    }
  case BarrelModeFeature::BMF_EnemyCar:
    // TODO calc LOS to cars
    break;

  default:
    return BtResult::BT_Failure;
  }
  return BtResult::BT_Failure;
}


// NavNode

BtResult NavNode::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt)
{
  auto aicc = dynamic_cast<ArenaAiContextCarController*>(car->getController());

  assert(aicc != NULL);

  Vec2f carTarget = car->getTargetPos();
  
  //printf("navigating to %f %f\n", carTarget.x, carTarget.y);
  aicc->steerToPos(car->getTargetPos());
  
  return BtResult::BT_Success;
}

