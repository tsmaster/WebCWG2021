// Behavior Tree Implementation

// TODO add memory
#include <memory>


// TODO add bt_node
#include "bt_node.h"
// TODO add btutil.h
#include "btutil.h"
// TODO add "gen_" when generating
#include "gen_barrelSimple.h"

// TODO declare CWG, Car, ArenaGameMode
class CarsWithGuns;
class Bdg_Car;
class ArenaGameMode;

// TODO SortLosNode arguments (Goal, Barrel)
// TODO rewrite to use unique_ptr

BarrelSimpleAI::BarrelSimpleAI() {
  //m_root = SelectorNode();
  m_root = std::unique_ptr<SelectorNode>(new SelectorNode);
  //  SequenceNode node_sequence_have_barrel;
  auto node_sequence_have_barrel = std::unique_ptr<SequenceNode>(new SequenceNode);
  //  BarrelSensorNode node_sensor_have_barrel;
  auto node_sensor_have_barrel = std::unique_ptr<BarrelSensorNode>(new BarrelSensorNode);
  //  node_sequence_have_barrel.add(node_sensor_have_barrel);
  node_sequence_have_barrel->add(std::move(node_sensor_have_barrel));
  //  SequenceNode node_sequence_local_delivery;
  auto node_sequence_local_delivery = std::unique_ptr<SequenceNode>(new SequenceNode);
  //  SortLosNode node_sort_los_to_goals(BarrelModeFeature::BMF_Goal);
  auto node_sort_los_to_goals = std::unique_ptr<SortLosNode>(new SortLosNode(BarrelModeFeature::BMF_Goal));
  //  node_sequence_local_delivery.add(node_sort_los_to_goals);
  node_sequence_local_delivery->add(std::move(node_sort_los_to_goals));
  //  NavNode node_nav_to_goal;
  auto node_nav_to_goal = std::unique_ptr<NavNode>(new NavNode);
  //  node_sequence_local_delivery.add(node_nav_to_goal);
  node_sequence_local_delivery->add(std::move(node_nav_to_goal));
  //  node_sequence_have_barrel.add(node_sequence_local_delivery);
  node_sequence_have_barrel->add(std::move(node_sequence_local_delivery));
  //  m_root.add(node_sequence_have_barrel);
  m_root->add(std::move(node_sequence_have_barrel));
  //  SequenceNode node_sequence_get_barrel;
  auto node_sequence_get_barrel = std::unique_ptr<SequenceNode>(new SequenceNode);
  //  SequenceNode node_sequence_get_local;
  auto node_sequence_get_local = std::unique_ptr<SequenceNode>(new SequenceNode);
  //  SortLosNode node_sort_los_to_barrels(BarrelModeFeature::BMF_Barrel);
  auto node_sort_los_to_barrels = std::unique_ptr<SortLosNode>(new SortLosNode(BarrelModeFeature::BMF_Barrel));
  //  node_sequence_get_local.add(node_sort_los_to_barrels);
  node_sequence_get_local->add(std::move(node_sort_los_to_barrels));
  //  NavNode node_nav_to_barrel;
  auto node_nav_to_barrel = std::unique_ptr<NavNode>(new NavNode);
  //  node_sequence_get_local.add(node_nav_to_barrel);
  node_sequence_get_local->add(std::move(node_nav_to_barrel));
  //  node_sequence_get_barrel.add(node_sequence_get_local);
  node_sequence_get_barrel->add(std::move(node_sequence_get_local));
  //  m_root.add(node_sequence_get_barrel);
  m_root->add(std::move(node_sequence_get_barrel));
}


// TODO add Cwg ptr
// TODO add car ptr
// TODO add mode ptr
BtResult BarrelSimpleAI::tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) {
  // TODO fix signature
  return m_root->tick(game, mode, car, dt);
}

