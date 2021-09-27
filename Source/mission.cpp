#include "mission.h"



std::vector<MissionStage*> Mission::getStages()
{
  std::vector<MissionStage*> outVec;

  for (int i=0; i < m_missionStages.size(); ++i) {
    outVec.push_back(&(m_missionStages[i]));
  }
  return outVec;
}

void MissionMgr::reset()
{
  m_missions.clear();
}

std::vector<Mission *> MissionMgr::getMissions()
{
  std::vector<Mission *> outVec;

  for (int i = 0; i < m_missions.size(); ++i) {
    outVec.push_back(&(m_missions[i]));
  }

  return outVec;
}
