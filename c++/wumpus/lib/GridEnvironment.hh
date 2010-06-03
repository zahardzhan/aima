#ifndef _GridEnvironment_HH_
#define _GridEnvironment_HH_

#include "Environment.hh"
#include "Point.hh"

#define MAX_GRID_SIZE   10

class GridEnvironment : public Environment
{
public:

  GridEnvironment ( int s );
  virtual ~GridEnvironment();
  
  int getSize() const;

  int isValid ( int x, int y ) const;
  int isValid ( const Point &point ) const;
  
  Object *objectOfTypeAt ( ObjectType type, int x, int y );
  Object *objectOfTypeAt ( ObjectType type, const Point &point );

  int isObjectTypeNear ( ObjectType type, int x, int y );
  int isObjectTypeNear ( ObjectType type, const Point &point );

  const Object *findRandomObject ( ObjectType type = NULL_OBJECT );
  
  virtual void display();
  
protected:

  int size;
};

#endif
