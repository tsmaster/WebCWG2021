#ifndef GEN_BARREL_SIMPLE
#define GEN_BARREL_SIMPLE

// TODO wrap with GEN_BARREL_SIMPLE

// Behavior Tree Declaration

// TODO include <memory>
#include <memory>

#include "bt_node.h"
#include "btutil.h"

// TODO add CWG, car declarations
class CarsWithGuns;
class Bdg_Car;

class BarrelSimpleAI {
  public:
    BarrelSimpleAI();
  
  // TODO fix signature
  BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt);
  private:
  std::unique_ptr<SelectorNode> m_root;
};

#endif // GEN_BARREL_SIMPLE
