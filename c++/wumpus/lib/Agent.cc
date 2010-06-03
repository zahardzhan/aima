#include <iostream.h>
#include <iomanip.h>
#include "Agent.hh"
#include "Player.hh"
#include "WumpusEnvironment.hh"
#include "Gold.hh"

const int scoreForMove = -1;
const int scorePerGold = 1000;
const int scoreForDeath = -1000;

Agent::Agent( const char *nameStr, int x, int y, Orientation o, int numArrows ) : Actor ( AGENT, x, y, o, nameStr )
{
  goldCount = 0;
  maxArrowCount = arrowCount = numArrows;
  bumpedLastTime = 0;
  Player::player->linkToAgent ( this );
}

Agent::~Agent()
{
}

void Agent::display() const
{
  cout << "    " << name << ":";

  cout << " State=" << state;
  
  cout << " Location=" << location << " Orientation=" << orientation;

  if ( goldCount )
    cout << " Gold=" << goldCount;

  if ( arrowCount )
    cout << " Arrows=" << arrowCount;

  cout << endl;
}

void Agent::reset()
{
  Actor::reset();
  Player::player->reset();
  goldCount = 0;
  arrowCount = maxArrowCount;
  bumpedLastTime = 0;
}

void Agent::update()
{
  if ( state == ALIVE )
    {
      Percept percept = look();
      Action action = think( percept );
      act( action );
    }
}

void Agent::done()
{
  Player::player->done();
}

Percept &Agent::look()
{
  static Percept percept;
  
  int b = bumpedLastTime;
  bumpedLastTime = 0;
  
  percept.perceive ( ( WumpusEnvironment& ) *env, b, location, orientation );
  return percept;
}

Action Agent::think ( const Percept &percept )
{
  return Player::player->think ( percept );
}

void Agent::act ( Action action )
{
  WumpusEnvironment *we = ( WumpusEnvironment* ) env;
  Gold *gold = ( Gold* ) we->objectOfTypeAt ( GOLD, location );    
  
  switch ( action )
    {
    case TURN_LEFT:
      switch ( orientation )
	{
	case UP:    orientation = LEFT; break;
	case DOWN:  orientation = RIGHT; break;
	case LEFT:  orientation = DOWN; break;
	case RIGHT: orientation = UP; break;
	}
      cout << "    " << name << " is now facing " << orientation << endl;
      score += scoreForMove;
      break;
      
    case TURN_RIGHT:
      switch ( orientation )
	{
	case UP:    orientation = RIGHT; break;
	case DOWN:  orientation = LEFT; break;
	case LEFT:  orientation = UP; break;
	case RIGHT: orientation = DOWN; break;
	}
      cout << "    " << name << " is now facing " << orientation << endl;
      score += scoreForMove;
      break;
      
    case GOFORWARD:
      if ( move() )
	{
	  bumpedLastTime = 1;
	  cout << "    " << name << " hit the wall!" << endl;
	}
      else
	cout << "    " << name << " moved to " << location << endl;
      
      score += scoreForMove;

      if ( we->isDeadly ( location ) )
	{
	  cout << "    " << name << " then promptly Died!!!!!" << endl;
	  state = DEAD;
	  score += scoreForDeath;
	}

      break;
      
    case GRAB:
      if ( gold && gold->get() )
	{
	  goldCount++;
	  cout << "    " << name << " picked up some gold" << endl;
	}
      else
	cout << "    " << name << " tried to get non-existent gold" << endl;
      score += scoreForMove;
      break;
      
    case SHOOT:
      if ( arrowCount )
	{
	  cout << "    " << name << " shot arrow " << orientation << " from " << location << endl;
	  arrowCount--;
	  we->launchArrow ( location, orientation );
	}
      else
	cout << "    " << name << " is out of arrows!" << endl;
      score += scoreForMove;
      break;
      
    case CLIMB:
      score += scoreForMove;
      if ( location.is ( 0, 0 ) )
	{
	  state = VICTORIOUS;
	  cout << "    " << name << " climbed out of cave." << endl;
	  score += scorePerGold * goldCount;
	}
      else
	cout <<  "    " << name << " can't climb out from " << location << endl;
      break;
    }
}

void Agent::printScore() const
{
  cout << "   " << name;

  switch ( state )
    {
    case ALIVE:       cout << " scored "; break;
    case DEAD:        cout << " died with score of "; break;
    case VICTORIOUS:  cout << " won with score of "; break;
    }

  cout << score << endl;
}

void Agent::updateStats()
{
  stats += ( double ) score;
}

void Agent::printStats()
{
  cout.setf ( ios::left, ios::adjustfield );
  
  cout << endl << "Performance Analysis for " << name << endl;
  cout << "    " << setw(21) << "Number of Trials: " << stats.samples() << endl;
  cout << "    " << setw(21) << "Best Score: " << stats.max() << endl;
  cout << "    " << setw(21) << "Worst Score: " << stats.min() << endl;
  cout << "    " << setw(21) << "Mean: " << stats.mean() << endl;
  cout << "    " << setw(21) << "Standard Deviation: " << stats.stdDev() << endl;
}
