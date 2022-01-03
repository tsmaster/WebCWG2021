// Behavior Tree Implementation


#include <memory>

#include "bt_node.h"
#include "btutil.h"
#include "gen_barrel.h"

class CarsWithGuns;
class Bdg_Car;
class ArenaGameMode;

BarrelAI::BarrelAI() {
  m_root = std::unique_ptr<SelectorNode>(new SelectorNode);
  auto node_sequence_have_barrel = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sensor_have_barrel = std::unique_ptr<BarrelSensorNode>(new BarrelSensorNode);
  node_sequence_have_barrel->add(std::move(node_sensor_have_barrel));
  auto node_selector_deliver_barrel = std::unique_ptr<SelectorNode>(new SelectorNode);
  auto node_sequence_local_delivery = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sort_los_to_goals = std::unique_ptr<SortLosNode>(new SortLosNode(BarrelModeFeature::BMF_Goal));
  node_sequence_local_delivery->add(std::move(node_sort_los_to_goals));
  auto node_nav_to_goal = std::unique_ptr<NavNode>(new NavNode);
  node_sequence_local_delivery->add(std::move(node_nav_to_goal));
  node_selector_deliver_barrel->add(std::move(node_sequence_local_delivery));
  auto node_sequence_long_distance_delivery = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_a_star_to_goal = std::unique_ptr<AStarNode>(new AStarNode);
  node_sequence_long_distance_delivery->add(std::move(node_a_star_to_goal));
  auto node_follow_a_star_to_goal = std::unique_ptr<FollowAStarPathNode>(new FollowAStarPathNode);
  node_sequence_long_distance_delivery->add(std::move(node_follow_a_star_to_goal));
  node_selector_deliver_barrel->add(std::move(node_sequence_long_distance_delivery));
  node_sequence_have_barrel->add(std::move(node_selector_deliver_barrel));
  m_root->add(std::move(node_sequence_have_barrel));
  auto node_sequence_get_barrel = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_selector = std::unique_ptr<SelectorNode>(new SelectorNode);
  auto node_sequence_get_local = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sort_los_to_barrels = std::unique_ptr<SortLosNode>(new SortLosNode(BarrelModeFeature::BMF_Barrel));
  node_sequence_get_local->add(std::move(node_sort_los_to_barrels));
  auto node_nav_to_barrel = std::unique_ptr<NavNode>(new NavNode);
  node_sequence_get_local->add(std::move(node_nav_to_barrel));
  node_selector->add(std::move(node_sequence_get_local));
  auto node_sequence_get_remote = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_a_star_to_barrels = std::unique_ptr<AStarNode>(new AStarNode);
  node_sequence_get_remote->add(std::move(node_a_star_to_barrels));
  auto node_follow_a_star_to_barrel = std::unique_ptr<FollowAStarPathNode>(new FollowAStarPathNode);
  node_sequence_get_remote->add(std::move(node_follow_a_star_to_barrel));
  node_selector->add(std::move(node_sequence_get_remote));
  node_sequence_get_barrel->add(std::move(node_selector));
  m_root->add(std::move(node_sequence_get_barrel));
  auto node_sequence_patrol = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_a_star_to_patrol_points = std::unique_ptr<AStarNode>(new AStarNode);
  node_sequence_patrol->add(std::move(node_a_star_to_patrol_points));
  auto node_follow_a_star_to_patrol_point = std::unique_ptr<FollowAStarPathNode>(new FollowAStarPathNode);
  node_sequence_patrol->add(std::move(node_follow_a_star_to_patrol_point));
  m_root->add(std::move(node_sequence_patrol));
}



BtResult BarrelAI::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) {
  return m_root->tick(game, mode, car, dt);
}

