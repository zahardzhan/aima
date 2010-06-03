#ifndef _MovingObject_HH_
#define _MovingObject_HH_

#include "GridObject.hh"
#include "Orientations.hh"

class MovingObject : public GridObject
{
public:

  MovingObject ( ObjectType objectType, int x, int y, Orientation o );
  virtual ~MovingObject() {};

  virtual void reset();
  virtual void setOrientation ( Orientation o );
  virtual void turnLeft();
  virtual void turnRight();
  virtual int move();
  
protected:

  Orientation orientation;
  Orientation origOrientation;
};

#endif
