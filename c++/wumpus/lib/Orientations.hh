#ifndef __Orientation_HH__
#define __Orientation_HH__

#include <iostream.h>

typedef enum { RIGHT, UP, LEFT, DOWN } Orientation;

inline ostream& operator<< ( ostream &o, Orientation or )
{
  switch ( or )
    {
    case UP:    return o << "Up";
    case DOWN:  return o << "Down"; 
    case LEFT:  return o << "Left";
    case RIGHT: return o << "Right";
    }

  return o;
}

#endif
