#include "Arrow.hh"
#include "WumpusEnvironment.hh"
#include "Wumpus.hh"

Arrow::Arrow ( int x, int y, Orientation o ) : MovingObject ( ARROW, x, y, o )
{
  active = 1;
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
  WumpusEnvironment *we = ( WumpusEnvironment* ) env;
  
  if ( !active )
    return;
  
  if ( move() )
    {
      cout << "    Arrow hit the wall" << endl;
      active = 0;
      return;
    }

  if ( we->killWumpus ( location ) )
    {
      cout << "    Arrow Struck a Wumpus at " << location << endl;
      active = 0;
      return;
    }
  else
    cout << "    Arrow moved to " << location << endl;
}

int Arrow::isActive() const
{
  return active;
}
