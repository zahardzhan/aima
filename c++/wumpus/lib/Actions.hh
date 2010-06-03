#ifndef __Actions_HH__
#define __Actions_HH__

#include <iostream.h>

typedef enum { TURN_RIGHT, TURN_LEFT, GOFORWARD, GRAB, SHOOT, CLIMB } Action;

inline ostream& operator<< ( ostream &o, Action action )
{
  switch ( action )
    {
    case TURN_RIGHT: return o << "Turn_Right";
    case TURN_LEFT:  return o << "Turn_Left";
    case GOFORWARD:  return o << "Go_Forward";
    case GRAB:       return o << "Grab";
    case SHOOT:      return o << "Shoot";
    case CLIMB:      return o << "Climb";
    }

  return o;
}

typedef const Action cAction;

#endif
