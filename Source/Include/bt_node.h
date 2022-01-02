#ifndef BT_NODE_H
#define BT_NODE_H

#include <memory>
#include <string>
#include <vector>

#include "btutil.h"

class CarsWithGuns;
class Bdg_Car;
class ArenaGameMode;


class BtNode
{
 public:
  BtNode();

  /*virtual*/ void add(std::unique_ptr<BtNode> child);

  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt);

  virtual std::string getName() { return std::string("Generic BtNode"); }
  
 protected:
  std::vector<std::unique_ptr<BtNode>> m_children;
};

class SelectorNode: public BtNode
{
 public:
  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) override;

  virtual std::string getName() { return std::string("Selector"); }
  
 private:
  bool m_bIsRunning;
  int m_currentlyRunningChild;
  
};

class SequenceNode: public BtNode
{
 public:
  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) override;

  virtual std::string getName() { return std::string("Sequence"); }
  
 private:
  bool m_bIsRunning;
  int m_currentlyRunningChild;
};

class InverterNode: public BtNode
{
 public:
  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) override;

  //virtual void add(std::unique_ptr<BtNode> child) override;

  virtual std::string getName() { return std::string("Inverter"); }
  
  
};

class BarrelSensorNode: public BtNode
{
 public:
  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) override;

  virtual std::string getName() { return std::string("Barrel Sensor"); }
};

class SortLosNode: public BtNode
{
 public:
  SortLosNode(BarrelModeFeature target);
  
  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) override;

  virtual std::string getName() { return std::string("SortLosNode"); }
  
 private:
  BarrelModeFeature m_target;
};

class NavNode: public BtNode
{
 public:
  virtual BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt) override;

  virtual std::string getName() { return std::string("NavNode"); }
  
};

#endif // BT_NODE_H
