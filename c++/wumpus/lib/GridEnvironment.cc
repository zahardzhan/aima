#include "GridEnvironment.hh"
#include "GridObject.hh"
#include "RndGen.hh"
#include <iostream.h>

GridEnvironment::GridEnvironment( int s ) : Environment()
{
  size = s;
}

GridEnvironment::~GridEnvironment()
{
}

int GridEnvironment::getSize() const
{
  return size;
}

int GridEnvironment::isValid ( int x, int y ) const
{
  return ( x >= 0 && x < size && y >= 0 && y < size );
}

int GridEnvironment::isValid ( const Point &point ) const
{
  return isValid ( point.x(), point.y() );
}

Object *GridEnvironment::objectOfTypeAt ( ObjectType type, int x, int y )
{
  Pix o;

  if ( isValid ( x, y ) )
    for ( o = objectList.first(); o; objectList.next(o) )
      {
	GridObject *obj = ( GridObject* ) objectList(o);
	if ( obj->isAt ( x, y ) && obj->isA ( type ) )
	  return obj;
      }
  
  return 0;
}

Object *GridEnvironment::objectOfTypeAt ( ObjectType type, const Point &point )
{
  return objectOfTypeAt ( type, point.x(), point.y() );
}

int GridEnvironment::isObjectTypeNear ( ObjectType type, int x, int y )
{
  int i;

  if ( isValid ( x, y ) )
    for ( i=-1; i<2; i+=2 )
      if ( objectOfTypeAt ( type, x+i, y ) || objectOfTypeAt ( type, x, y+i ) )
	return 1;
  
  return 0;
}

int GridEnvironment::isObjectTypeNear ( ObjectType type, const Point &point )
{
  return isObjectTypeNear ( type, point.x(), point.y() );
}

const Object *GridEnvironment::findRandomObject ( ObjectType type )
{
  GridObject *object;
  Pix o;
  int i, index;

  do
    {
      index = randInt ( objectList.length()-1 );
      
      for ( i=0, o = objectList.first();
	    i<index && o;
	    i++, objectList.next(o) )
	;
      object = ( GridObject* ) objectList(o);
    }
  while ( object->isA( AGENT ) || ( type != NULL_OBJECT && !object->isA ( type ) ) );

  return object;
}

void GridEnvironment::display()
{
  GridObject *object;
  Pix o;
  
  for ( o = objectList.first(); o; objectList.next(o) )
    {
      object = ( GridObject* ) objectList(o);
      object->display();
    }
}
