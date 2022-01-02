// Behavior Tree Implementation

#include "barrel.h"

BarrelAI::BarrelAI() {
  m_root = SelectorNode();
  SequenceNode node_sequence_have_barrel;
  BarrelSensorNode node_sensor_have_barrel;
  node_sequence_have_barrel.add(node_sensor_have_barrel);
  SelectorNode node_selector_deliver_barrel;
  SequenceNode node_sequence_local_delivery;
  SortLosNode node_sort_los_to_goals;
  node_sequence_local_delivery.add(node_sort_los_to_goals);
  NavNode node_nav_to_goal;
  node_sequence_local_delivery.add(node_nav_to_goal);
  node_selector_deliver_barrel.add(node_sequence_local_delivery);
  SequenceNode node_sequence_long_distance_delivery;
  AStarNode node_a_star_to_goal;
  node_sequence_long_distance_delivery.add(node_a_star_to_goal);
  FollowAStarPathNode node_follow_a_star_to_goal;
  node_sequence_long_distance_delivery.add(node_follow_a_star_to_goal);
  node_selector_deliver_barrel.add(node_sequence_long_distance_delivery);
  node_sequence_have_barrel.add(node_selector_deliver_barrel);
  m_root.add(node_sequence_have_barrel);
  SequenceNode node_sequence_get_barrel;
  SelectorNode node_selector;
  SequenceNode node_sequence_get_local;
  SortLosNode node_sort_los_to_barrels;
  node_sequence_get_local.add(node_sort_los_to_barrels);
  NavNode node_nav_to_barrel;
  node_sequence_get_local.add(node_nav_to_barrel);
  node_selector.add(node_sequence_get_local);
  SequenceNode node_sequence_get_remote;
  AStarNode node_a_star_to_barrels;
  node_sequence_get_remote.add(node_a_star_to_barrels);
  FollowAStarPathNode node_follow_a_star_to_barrel;
  node_sequence_get_remote.add(node_follow_a_star_to_barrel);
  node_selector.add(node_sequence_get_remote);
  node_sequence_get_barrel.add(node_selector);
  m_root.add(node_sequence_get_barrel);
  SequenceNode node_sequence_patrol;
  AStarNode node_a_star_to_patrol_points;
  node_sequence_patrol.add(node_a_star_to_patrol_points);
  FollowAStarPathNode node_follow_a_star_to_patrol_point;
  node_sequence_patrol.add(node_follow_a_star_to_patrol_point);
  m_root.add(node_sequence_patrol);
}



BtResult BarrelAI::tick(float dt) {
  return m_root.tick(dt);
}

