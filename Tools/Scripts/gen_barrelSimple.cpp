// Behavior Tree Implementation


#include <memory>

#include "bt_node.h"
#include "btutil.h"
#include "gen_barrelSimple.h"

class CarsWithGuns;
class Bdg_Car;
class ArenaGameMode;

BarrelSimpleAI::BarrelSimpleAI() {
  m_root = std::unique_ptr<SelectorNode>(new SelectorNode);
  auto node_sequence_have_barrel = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sensor_have_barrel = std::unique_ptr<BarrelSensorNode>(new BarrelSensorNode);
  node_sequence_have_barrel->add(std::move(node_sensor_have_barrel));
  auto node_sequence_local_delivery = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sort_los_to_goals = std::unique_ptr<SortLosNode>(new SortLosNode(BarrelModeFeature::BMF_Goal));
  node_sequence_local_delivery->add(std::move(node_sort_los_to_goals));
  auto node_nav_to_goal = std::unique_ptr<NavNode>(new NavNode);
  node_sequence_local_delivery->add(std::move(node_nav_to_goal));
  node_sequence_have_barrel->add(std::move(node_sequence_local_delivery));
  m_root->add(std::move(node_sequence_have_barrel));
  auto node_sequence_get_barrel = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sequence_get_local = std::unique_ptr<SequenceNode>(new SequenceNode);
  auto node_sort_los_to_barrels = std::unique_ptr<SortLosNode>(new SortLosNode(BarrelModeFeature::BMF_Barrel));
  node_sequence_get_local->add(std::move(node_sort_los_to_barrels));
  auto node_nav_to_barrel = std::unique_ptr<NavNode>(new NavNode);
  node_sequence_get_local->add(std::move(node_nav_to_barrel));
  node_sequence_get_barrel->add(std::move(node_sequence_get_local));
  m_root->add(std::move(node_sequence_get_barrel));
}



BtResult BarrelSimpleAI::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) {
  return m_root->tick(game, mode, car, dt);
}

