#include "CheatingPlayer.hh"
#include <iostream.h>

//
// Global static variable of your player's class
//
static CheatingPlayer player;

//
// Your Player's class constructor
//
CheatingPlayer::CheatingPlayer()
{
}

//
// Your Player's class destructor
//
CheatingPlayer::~CheatingPlayer()
{
}

//
// Your Player's reset method
//
// You must call "Player::reset();" as the first step of this
// method!!
//
void CheatingPlayer::reset()
{
  Player::reset();
}

//
// Your Player's process method
//
// This is the method that will be called with each percept.
// The Player superclass provides you with lists of all previous
// percepts you have seen and all previous actions you have taken.
// When this method is invoked, the percept passed in already will
// have been added to the Percept List.
//
// See the Simulation Handout for instructions on accessing the
// Percept and Action lists.
//

static Action actions[] = { TURN_LEFT, SHOOT, GOFORWARD, GOFORWARD, TURN_RIGHT, GOFORWARD, GRAB, TURN_RIGHT, GOFORWARD, GOFORWARD, TURN_RIGHT, GOFORWARD, CLIMB };

const Action CheatingPlayer::process ( const Percept &percept )
{
  Pix p, a;

  for ( p = perceptList.first(),
	  a = actionList.first();
	p;
	perceptList.next(p),
	  actionList.next(a) )
    {
      cout << "    " << perceptList(p);
      if ( a )
	cout << " -> " << actionList(a);
      cout << endl;
    }
  
  cout << "    My state is " << getState() << "." << endl;
  cout << "    I have " << numGold() << " gold pieces." << endl;
  cout << "    I have  " << numArrows() << " arrows." << endl;
  cout << "    My score is " << getScore() << "." << endl;

  return actions[ actionList.length() ];
}

void CheatingPlayer::done()
{
  cout << "    In the Final Analysis:" << endl;
  cout << "    My state is " << getState() << "." << endl;
  cout << "    I have " << numGold() << " gold pieces." << endl;
  cout << "    I have  " << numArrows() << " arrows." << endl;
  cout << "    My score is " << getScore() << "." << endl;  
}
