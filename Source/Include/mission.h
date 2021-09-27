#ifndef mission_h
#define mission_h

#include <string>

#include "person.h"

enum class MissionStageState
{
  Hidden,       // not displayed to player
  Available,    // shown as (?) to prompt player to start the mission
  InProgress,   // shown with (...) on start and (!) on dest if mission simply needs to "Report in"
  Completed     // not displayed, complete.
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
  void addStage(MissionStage stage) { m_missionStages.push_back(stage); }
  std::vector<MissionStage *> getStages();
 private:
  std::vector<MissionStage> m_missionStages;
};

// container for missions
class MissionMgr
{
 public:
  void addMission(Mission mission) { m_missions.push_back(mission); }
  std::vector<Mission *> getMissions();
  void reset();
 private:
  std::vector<Mission> m_missions;  
};

#endif //mission_h
