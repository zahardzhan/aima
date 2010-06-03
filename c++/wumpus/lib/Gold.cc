#include "Gold.hh"
#include <iostream.h>

Gold::Gold ( int x, int y ) : GridObject ( GOLD, x, y )
{
  exists = 1;
}

Gold::~Gold()
{
}

void Gold::reset()
{
  exists = 1;
}

void Gold::display() const
{
  if ( exists )
    cout << "    There is gold at " << location << endl;
}

void Gold::update()
{
}

int Gold::isGotten() const
{
  return !exists;
}

int Gold::get()
{
  if ( !exists )
    return 0;

  exists = 0;
  return 1;
}

void Gold::write(ofstream &outFile) const
{
  outFile << "G " << location.x() << " " << location.y();
}

