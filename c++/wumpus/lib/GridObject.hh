#ifndef _GridObject_HH_
#define _GridObject_HH_

#include "Object.hh"
#include "Point.hh"

class GridObject : public Object
{
public:

  GridObject ( ObjectType objectType, int x, int y );
  virtual ~GridObject() {};

  virtual void reset();
  virtual int setXY ( int x, int y );
  virtual int setXY ( const Point &point );
  
  virtual int isAt ( int x, int y ) const;
  virtual int isAt ( const Point &point ) const;

  virtual const Point &loc() const { return location; };
  
protected:

  Point location;
  Point origLocation;
};

#endif
