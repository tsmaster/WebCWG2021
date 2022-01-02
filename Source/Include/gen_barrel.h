// Behavior Tree Declaration

#include "btutil.h"

class BarrelAI {
  public:
    BarrelAI();
    BtResult tick(float dt);
  private:
    SelectorNode m_root;
};

