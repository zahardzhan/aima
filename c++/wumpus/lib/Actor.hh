#ifndef _Actor_HH_
#define _Actor_HH_

#include "MovingObject.hh"
#include "ActorStates.hh"
#include <String.h>

class Actor : public MovingObject
{
public:

  Actor ( ObjectType objectType, int x, int y, Orientation o, const char *nameStr );
  virtual ~Actor() {};

  virtual void reset();
  virtual ActorState getState() const { return state; };
  
protected:

  String name;
  ActorState state;
};

#endif
