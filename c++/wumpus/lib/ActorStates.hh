#ifndef __ActorStates_HH__
#define __ActorStates_HH__

#include <iostream.h>

typedef enum { ALIVE, DEAD, VICTORIOUS } ActorState;

inline ostream& operator<< ( ostream &o, ActorState state )
{
  switch ( state )
    {
    case ALIVE:      return o << "Alive";
    case DEAD:       return o << "Dead";
    case VICTORIOUS: return o << "Victorious";
    }

  return o;
}

#endif
