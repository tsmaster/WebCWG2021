#ifndef BTUTIL_H
#define BTUTIL_H


enum class BtResult {
  Success,
  Failure,
  Running
};


class BtNode
{
 public:
  BtNode();

  void add(BtNode& child);

  BtResult tick(float dt);
};

class SelectorNode: public BtNode
{
};

class SequenceNode: public BtNode
{
};

class BarrelSensorNode: public BtNode
{
};

class SortLosNode: public BtNode
{
};

class NavNode: public BtNode
{
};


#endif // BTUTIL_H
