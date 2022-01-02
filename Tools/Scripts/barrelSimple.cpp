// Behavior Tree Implementation

#include "barrelSimple.h"

BarrelSimpleAI::BarrelSimpleAI() {
  m_root = SelectorNode();
  SequenceNode node_sequence_have_barrel;
  BarrelSensorNode node_sensor_have_barrel;
  node_sequence_have_barrel.add(node_sensor_have_barrel);
  SequenceNode node_sequence_local_delivery;
  SortLosNode node_sort_los_to_goals;
  node_sequence_local_delivery.add(node_sort_los_to_goals);
  NavNode node_nav_to_goal;
  node_sequence_local_delivery.add(node_nav_to_goal);
  node_sequence_have_barrel.add(node_sequence_local_delivery);
  m_root.add(node_sequence_have_barrel);
  SequenceNode node_sequence_get_barrel;
  SequenceNode node_sequence_get_local;
  SortLosNode node_sort_los_to_barrels;
  node_sequence_get_local.add(node_sort_los_to_barrels);
  NavNode node_nav_to_barrel;
  node_sequence_get_local.add(node_nav_to_barrel);
  node_sequence_get_barrel.add(node_sequence_get_local);
  m_root.add(node_sequence_get_barrel);
}



BtResult BarrelSimpleAI::tick(float dt) {
  return m_root.tick(dt);
}

