#include "Actor.hh"
#include <String.h>

Actor::Actor ( ObjectType objectType, int x, int y, Orientation o, const char *nameStr ) : MovingObject ( objectType, x, y, o ), name ( nameStr )
{
  state = ALIVE;
}

void Actor::reset()
{
  MovingObject::reset();
  state = ALIVE;
}
