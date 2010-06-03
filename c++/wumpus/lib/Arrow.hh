#ifndef _Arrow_HH_
#define _Arrow_HH_

#include "MovingObject.hh"

class Arrow : public MovingObject
{
public:

  Arrow( int x, int y, Orientation o );
  virtual ~Arrow();

  virtual void reset() {};
  virtual void update();
  virtual void display() const {};
  virtual void printScore() const {};
  virtual void updateStats() {};
  virtual void printStats() {};

  virtual int isActive() const;
  
protected:

  int active;
};

#endif
