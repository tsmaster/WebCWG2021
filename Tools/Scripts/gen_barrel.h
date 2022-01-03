#ifndef GEN_BARRELAI
#define GEN_BARRELAI

// Behavior Tree Declaration

#include <memory>

#include "bt_node.h"
#include "btutil.h"

class CarsWithGuns;
class Bdg_Car;

class BarrelAI {
  public:
    BarrelAI();
    BtResult tick(CarsWithGuns* game, ArenaGameMode* mode, Bdg_Car* car, float dt);
  private:
    std::unique_ptr<SelectorNode> m_root;
};

#endif // GEN_BARRELAI
