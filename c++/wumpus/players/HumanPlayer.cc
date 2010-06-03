#include "HumanPlayer.hh"
#include <iostream.h>
#include <stdlib.h>
#include <time.h>

//
// Global static variable of your player's class
//
static HumanPlayer player;

//
// Your Player's class constructor
//
HumanPlayer::HumanPlayer()
{
}

//
// Your Player's class destructor
//
HumanPlayer::~HumanPlayer()
{
}

//
// Your Player's reset method
//
// You must call "Player::reset();" as the first step of this
// method!!
//
void HumanPlayer::reset()
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

const Action HumanPlayer::process ( const Percept &percept )
{
  Pix p, a;
  char c;

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

  cout << "Action (l,r,f,g,s,c): ";
  cin >> c;

  switch ( c )
    {
    case 'l': return TURN_LEFT;
    case 'r': return TURN_RIGHT;
    case 'f': return GOFORWARD;
    case 'g': return GRAB;
    case 's': return SHOOT;
    case 'c': return CLIMB;
    }

  return TURN_LEFT;
}

void HumanPlayer::done()
{
  cout << "    In the Final Analysis:" << endl;
  cout << "    My state is " << getState() << "." << endl;
  cout << "    I have " << numGold() << " gold pieces." << endl;
  cout << "    I have  " << numArrows() << " arrows." << endl;
  cout << "    My score is " << getScore() << "." << endl;  
}
