#include "Wumpus.hh"
#include "GridEnvironment.hh"
#include "Gold.hh"
#include "Pit.hh"
#include <iostream.h>
#include "RndInt.h"

extern RandomInteger randInt;
char *MovementNames[] = { "Sit", "Spin", "Random", "Bump/Turn", "Loop", "Goto-Gold", "Goto-Pit" };

Wumpus::Wumpus( const char *nameStr, int x, int y, Orientation o, Movement m ) : Actor ( WUMPUS, x, y, o, nameStr ), goal ( 0, 0 )
{
  movement = m==PICK? ( Movement ) randInt( (int) ( PICK-1 ) ) : m;
}

Wumpus::~Wumpus()
{
}

void Wumpus::reset()
{
  Actor::reset();

  switch ( movement )
    {
    case GOTO_PIT:
    case GOTO_GOLD:
      if ( goal.is ( 0, 0 ) )
	{
	  GridObject *obj = ( GridObject* ) ( ( GridEnvironment* ) env )->findRandomObject ( movement==GOTO_GOLD?GOLD:PIT );
	  
	  if ( obj )
	    goal = obj->loc();
	  else
	    goal = location;
	}
      break;

    default:
      break;
    }
}

void Wumpus::update()
{
  switch ( movement )
    {
    case SIT:
      break;

    case SPIN:
      turnLeft();
      break;
      
    case RANDOM:
      switch ( randInt(2) )
	{
	case 0:
	  turnLeft();
	  break;
	  
	case 1:
	  turnRight();
	  break;
	  
	case 2:
	  move();
	  break;
	}
      break;
      
    case BUMP_TURN:
      if ( move() )
	{
	  if ( randInt(1) )
	    turnLeft();
	  else
	    turnRight();
	}
      break;
      
    case LOOP:
      if ( turnedLast )
	{
	  move();
	  turnedLast = 0;
	}
      else
	{
	  turnLeft();
	  turnedLast = 1;
	}
      break;
      
    case GOTO_GOLD:
    case GOTO_PIT:
      if ( location.x() != goal.x() )
	{
	  if ( location.x() < goal.x() )
	    {
	      if ( orientation == RIGHT )
		move();
	      else
		turnRight();
	    }
	  else
	    {
	      if ( orientation == LEFT )
		move();
	      else
		turnRight();
	    }
	}
      else
	if ( location.y() != goal.y() )
	  {
	    if ( location.y() < goal.y() )
	      {
		if ( orientation == UP )
		  move();
		else
		  turnRight();
	      }
	    else
	      {
		if ( orientation == DOWN )
		  move();
		else
		  turnRight();
	      }
	  }
      break;
      
    default:
      cerr << "Unknown Movement mode: " << (int) movement << endl;
      break;
    }
}

int Wumpus::move()
{
  if ( ( location+orientation ).is ( 0, 0 ) )
    return 1;
  
  return MovingObject::move();
}

int Wumpus::die()
{
  if ( state != ALIVE )
    return 0;

  state = DEAD;
  return 1;
}

void Wumpus::display() const
{
  cout << "    " << name << " is " << ( state==ALIVE?"":"dead " ) << "at " << location << ", Dir=" << orientation << ", Mode=" << movement << endl;
}

void Wumpus::printScore() const
{
}

void Wumpus::updateStats()
{
}

void Wumpus::printStats()
{
}

void Wumpus::write(ofstream &outFile) const
{
  outFile << "W " << location.x() << " " << location.y() << " " << movement;
}
