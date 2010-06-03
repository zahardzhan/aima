#ifndef __ObjectTypes_HH__
#define __ObjectTypes_HH__

#include <iostream.h>

typedef enum { NULL_OBJECT, PIT, GOLD, ARROW, WUMPUS, AGENT } ObjectType;

inline ostream& operator<< ( ostream &o, ObjectType type )
{
  switch ( type )
    {
    case NULL_OBJECT: return o << "Null";
    case PIT:         return o << "Pit";
    case GOLD:        return o << "Gold";
    case ARROW:       return o << "Arrow";
    case WUMPUS:      return o << "Wumpus";
    case AGENT:       return o << "Agent";
    }

  return o;
}

#endif
