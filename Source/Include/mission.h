#ifndef mission_h
#define mission_h

#include <string>

#include "person.h"

enum class MissionStageState
{
  NotStarted,
  Active,
  Completed  
};


// eventually want a variety of missions. To begin with, a simple carry quest.

class MissionStage
{
 public:
  MissionStage() {};
  
  MissionStageState m_state;

  std::string m_startMsg;
  std::string m_helpMsg;
  std::string m_completeMsg;

  // temp
  PersonAddress m_startPerson = PersonAddress(-1, -1, -1);
  PersonAddress m_destPerson = PersonAddress(-1, -1, -1);
  // we might also insert an item into the inventory
  // we don't yet have an inventory

  // payoff will probably be zero until the end?
  int m_stagePayoff;

 protected:
  void complete();
  
};

// container for MissionStages
class Mission
{
 public:
  std::vector<MissionStage> m_missionStages;
};

// container for missions
class MissionMgr
{
 public:
  std::vector<Mission> m_missions;

  void addMission(Mission& mission) { m_missions.push_back(mission); }
  void reset();
};

#endif //mission_h
