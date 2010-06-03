#include "GridObject.hh"
#include "GridEnvironment.hh"

GridObject::GridObject ( ObjectType objectType, int x, int y ) : Object ( objectType ), location ( x, y ), origLocation ( x, y )
{
}

void GridObject::reset()
{
  Object::reset();
  location = origLocation;
}

int GridObject::setXY ( const Point &point )
{
  return setXY ( point.x(), point.y() );
}

int GridObject::setXY ( int x, int y )
{
  GridEnvironment *ge = ( GridEnvironment* ) env;

  if ( !ge->isValid ( x, y ) )
    return 1;

  location.set ( x, y );
  return 0;
}

int GridObject::isAt ( const Point &point ) const
{
  return isAt ( point.x(), point.y() );
}

int GridObject::isAt ( int x, int y ) const
{
  return location.is ( x, y );
}
