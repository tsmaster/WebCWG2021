// Behavior Tree Declaration

#include "btutil.h"

class BarrelSimpleAI {
  public:
    BarrelSimpleAI();
    BtResult tick(float dt);
  private:
    SelectorNode m_root;
};

