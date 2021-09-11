// mode_highway.h

// Reference ../PyCWG2021/fractal.py

#ifndef MODE_HIGHWAY_H
#define MODE_HIGHWAY_H

class HighwayGameMode
{
 public:
  HighwayGameMode();

  void init();

  void destroy();

  void update(float elapsedSeconds);

  void draw();
  
};

#endif // MODE_HIGHWAY_H
