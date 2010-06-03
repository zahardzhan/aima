#ifndef _Wumpus_HH_
#define _Wumpus_HH_

#include "Actor.hh"
#include <String.h>

typedef enum { SIT, SPIN, RANDOM, BUMP_TURN, LOOP, GOTO_GOLD, GOTO_PIT, PICK } Movement;

extern char *MovementNames[];

class Wumpus : public Actor
{
public:

  Wumpus ( const char *nameStr, int x, int y, Orientation o, Movement m = SIT );
  virtual ~Wumpus();

  virtual void reset();
  virtual void update();
  virtual int move();
  virtual void display() const;
  virtual void printScore() const;
  virtual void updateStats();
  virtual void printStats();
  
  virtual int die();

  void write(ofstream &) const;

protected:
  
  Movement movement, origMovement;
  int turnedLast;
  Point goal;
};

inline ostream &operator<< ( ostream &o, Movement m )
{
  switch ( m )
    {
    case SIT:
    case SPIN:
    case RANDOM:
    case BUMP_TURN:
    case LOOP:
    case GOTO_GOLD:
    case GOTO_PIT:
      o << MovementNames[ m ];
      break;
      
    default:
      o << "Bad-Movement-Value";
      break;
    }

  return o;
}

inline istream &operator>> ( istream &i, Movement &m )
{
  String str;
  int n;

  i >> str;

  m = SIT;

  for ( n=0; n<7; n++ )
    if ( str == MovementNames[ n ] )
      m = ( Movement ) n;

  return i;
}

#endif
