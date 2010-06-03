#ifndef _Agent_HH_
#define _Agent_HH_

#include "Actor.hh"
#include "Actions.hh"
#include "Percept.hh"

class Agent : public Actor
{
public:

  Agent( const char *nameStr, int x, int y, Orientation o, int numArrows );
  virtual ~Agent();
  
  virtual void reset();
  virtual void update();
  virtual void done();
  
  virtual Percept &look();
  virtual Action think ( const Percept &percept );
  virtual void act ( Action action );

  virtual int numGold() const { return goldCount; };
  virtual int numArrows() const { return arrowCount; };
  
  virtual void display() const;
  virtual void printScore() const;
  virtual void updateStats();
  virtual void printStats();

protected:

  int goldCount;
  int arrowCount;
  int maxArrowCount;
  int bumpedLastTime;
};

#endif
