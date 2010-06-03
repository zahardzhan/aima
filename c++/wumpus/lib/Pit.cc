#include "Pit.hh"
#include <iostream.h>

Pit::Pit( int x, int y ) : GridObject ( PIT, x, y )
{
}

Pit::~Pit()
{
}

void Pit::display() const
{
  cout << "    A Pit is at " << location << endl;
}

void Pit::write(ofstream &outFile)
{
  outFile << "P " << location.x() << " " << location.y();
}

