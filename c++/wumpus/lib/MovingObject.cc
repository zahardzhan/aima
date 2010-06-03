#include "MovingObject.hh"

MovingObject::MovingObject ( ObjectType objectType, int x, int y, Orientation o ) : GridObject ( objectType, x, y )
{
  origOrientation = orientation = o;
}

void MovingObject::reset()
{
  GridObject::reset();
  orientation = origOrientation;
}

void MovingObject::setOrientation ( Orientation o )
{
  orientation = o;
}

void MovingObject::turnLeft()
{
  int x = ( int ) orientation;
  x++;
  x %= 4;
  orientation = ( Orientation ) x;
}

void MovingObject::turnRight()
{
  int x = ( int ) orientation;
  x+=3;
  x %= 4;
  orientation = ( Orientation ) x;
}

int MovingObject::move()
{
  return setXY ( location+orientation );
}
