#ifndef gameclock_h
#define gameclock_h

class GameClock
{
 public:
  GameClock();

  void increment();

  unsigned int getTime() const;

 private:
  unsigned int m_counter = 0;
};

#endif //gameclock_h
