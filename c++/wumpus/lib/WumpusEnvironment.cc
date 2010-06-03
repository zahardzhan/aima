#include "WumpusEnvironment.hh"
#include "Pit.hh"
#include "Gold.hh"
#include "Wumpus.hh"
#include "Agent.hh"
#include "Arrow.hh"
#include "RndGen.hh"
#include <iostream.h>
#include <fstream.h>
#include <strstream.h>

// WUMPUS_MODE symbol:
//
// If WUMPUS_MODE is not defined, all wumpi will be stationary.
// If defined, each wumpus will move according to the mode specified:
//
// SIT        Stationary Wumpus
// SPIN       Turns Left each round
// RANDOM     Moves/Turns Randomly
// BUMP_TURN  Moves until it hits a wall
// LOOP       Moves in a small circle
// GOTO_GOLD  Moves to a gold piece and sits there
// GOTO_PIT   Moves to a pit and sits there
//
// PICK       Each Wumpus will andomly pick one of the above 7 movement modes.

const char *OUTFILE = ".world";

WumpusEnvironment::WumpusEnvironment( int s ) : GridEnvironment ( s?s:4 )
{
  int i, num, x, y;

  if ( s && ( s < 4 || s > 10 ) )
    {
      cerr << "Wumpus Environment Size must be from 4 to 10" << endl;
      exit ( 0 );
    }

  wumpusDiedThisTime = wumpusDiedLastTime = 0;
  
  if ( s )
    {
      // Random Square location generator
      RandomInteger rp ( 0, size-1, &rng );
      
      // Add Gold Pieces
      num = randInt( 3 ) + 1;
      
      for ( i=0; i<num; )
	{
	  x = rp();
	  y = rp();
	  
	  if ( !( x==0 && y==0 ) )
	    {
	      addObject ( new Gold ( x, y ) );
	      i++;
	    }
	}

      // Add Pits
      for ( x=0; x<size; x++  )
	for ( y=0; y<size; y++  )
	  if ( !( x==0 && y==0 ) && !objectOfTypeAt ( GOLD, x, y ) && !( randInt( 4 ) ) )
	    addObject ( new Pit ( x, y ) );

      // Add Wumpi
      num = randInt( 2 ) + 1;
      
      for ( i=0; i<num; )
	{
	  x = rp();
	  y = rp();
	  
	  if ( !( x==0 && y==0 ) )
	    {
	      ostrstream name;
	      
	      name << "Wumpus " << i+1;
#ifdef WUMPUS_MODE
	      addObject ( new Wumpus ( name.str(), x, y, RIGHT, WUMPUS_MODE ) );
#else
	      addObject ( new Wumpus ( name.str(), x, y, RIGHT ) );
#endif
	      i++;
	    }
	}
    }
  else
    {
      addObject ( new Wumpus ( "The Wumpus", 0, 2, RIGHT ) );
      addObject ( new Gold ( 1, 2 ) );
      addObject ( new Pit ( 3, 3 ) );
      addObject ( new Pit ( 2, 2 ) );
      addObject ( new Pit ( 2, 0 ) );
    }
  
  addObject ( new Agent ( "The Agent", 0, 0, RIGHT, 1 ) );
  writeToFile(OUTFILE);
}

WumpusEnvironment::WumpusEnvironment(const char *filename) :
  GridEnvironment(getWorldSize(filename))
{
  char ch;
  int x, y, numWumpus = 0;

  ifstream inFile( filename, ios::in );
  if (!inFile) {
    cerr << "cannot open " << filename << endl;
    exit(0);
    }

  wumpusDiedThisTime = wumpusDiedLastTime = 0;

  inFile >> x;  // read passed initial size
  while ( inFile >> ch ) {
    switch (ch) {
      case 'g':
      case 'G':
        inFile >> x >> y;
        addObject( new Gold ( x, y ) );
        break;
      case 'p':
      case 'P':
        inFile >> x >> y;
        addObject( new Pit ( x, y ) );
        break;
      case 'w':
      case 'W':
	{
	  Movement m;
	  
	  inFile >> x >> y >> m;

	  ostrstream name;
	  name << "Wumpus " << ++numWumpus;
	  addObject( new Wumpus ( name.str(), x, y, RIGHT, m ) );
        }
	break;

      default:
        cerr << "Unknown object " << ch << "in file" << filename << endl;
        exit(0);
      }
    }
  inFile.close();
  addObject ( new Agent ( "The Agent", 0, 0, RIGHT, numWumpus ) );
  writeToFile(OUTFILE);
}

WumpusEnvironment::~WumpusEnvironment()
{
}

int WumpusEnvironment::stillRunning()
{
  Pix o;
  
  for ( o = objectList.first(); o; objectList.next(o) )
    {
      Object *obj = objectList(o);
      if ( ( obj->isA ( AGENT ) && ( ( Agent* ) obj )->getState() == ALIVE ) ||
	   ( obj->isA ( ARROW ) && ( ( Arrow* ) obj )->isActive() ) )
	return 1;
    }

  return 0;
}

void WumpusEnvironment::preUpdate()
{
  wumpusDiedThisTime = 0;
}

void WumpusEnvironment::postUpdate()
{
  wumpusDiedLastTime = wumpusDiedThisTime;
}

int WumpusEnvironment::isDeadly ( const Point &point )
{
  return isDeadly ( point.x(), point.y() );
}

int WumpusEnvironment::isDeadly ( int x, int y )
{
  Wumpus *wumpus = ( Wumpus* ) objectOfTypeAt ( WUMPUS, x, y );
  
  return ( wumpus && wumpus->getState() == ALIVE ) || objectOfTypeAt ( PIT, x, y );
}

int WumpusEnvironment::isWumpusNear ( const Point &point )
{
  return isWumpusNear ( point.x(), point.y() );
}

int WumpusEnvironment::isWumpusNear ( int x, int y )
{
  int i;

  if ( isValid ( x, y ) )
    {
      if ( objectOfTypeAt ( WUMPUS, x, y ) )
	return 1;
      
      for ( i=-1; i<2; i+=2 )
	{
	  Wumpus *wumpus = ( Wumpus* ) objectOfTypeAt ( WUMPUS, x+i, y );
	  if ( wumpus && wumpus->getState() == ALIVE )
	    return 1;
	  
	  wumpus = ( Wumpus* ) objectOfTypeAt ( WUMPUS, x, y+i );
	  if ( wumpus && wumpus->getState() == ALIVE )
	    return 1;
	}
    }
  
  return 0;
}

int WumpusEnvironment::didWumpusDie() const
{
  return wumpusDiedLastTime;
}

int WumpusEnvironment::killWumpus ( const Point &point )
{
  return killWumpus ( point.x(), point.y() );
}

int WumpusEnvironment::killWumpus ( int x, int y )
{
  Wumpus *wumpus = ( Wumpus* ) objectOfTypeAt ( WUMPUS, x, y );

  if ( wumpus && wumpus->die() )
    {
      wumpusDiedThisTime = 1;
      return 1;
    }
  
  return 0;
}

void WumpusEnvironment::launchArrow ( const Point &point, Orientation o )
{
  launchArrow ( point.x(), point.y(), o );
}

void WumpusEnvironment::launchArrow ( int x, int y, Orientation o )
{
  Arrow arrow ( x, y, o );

  arrow.linkToEnv ( this );
  
  while ( arrow.isActive() )
    arrow.update();

}

void WumpusEnvironment::writeToFile(const char *filename)
{
  Pix o;
  ofstream outFile ( filename, ios::out );

  outFile << size << endl;
  for ( o = objectList.first(); o; objectList.next(o) ) {
    Object *obj = objectList(o);
    switch ( obj->isA() ) {
      case GOLD:
        ((Gold *)obj)->write(outFile);
        outFile << endl;
        break;
      case PIT:
        ((Pit *)obj)->write(outFile);
        outFile << endl;
        break;
      case WUMPUS:
        ((Wumpus *)obj)->write(outFile);
        outFile << endl;
        break;
      default:
        break;
      }
    }
  outFile.close();
}

int getWorldSize(const char *filename)
{
  int size;
  ifstream inFile ( filename, ios::in );

  if (!inFile) {
    cerr << "cannot open file " << filename << endl;
    exit(0);
    }
  inFile >> size;
  inFile.close();
  return size;
}
