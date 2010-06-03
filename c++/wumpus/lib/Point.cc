#include "Point.hh"

Point::Point ( int x, int y )
{
  X = x;
  Y = y;
}

Point::~Point()
{}

int Point::x() const
{
  return X;
}

void Point::x ( int x )
{
  X = x;
}

int Point::y() const
{
  return Y;
}

void Point::y ( int y )
{
  Y = y;
}

void Point::set ( int x, int y )
{
  X = x;
  Y = y;
}

int Point::operator== ( const Point &p ) const
{
  return ( p.X == X && p.Y == Y );
}

Point &Point::operator+ ( Orientation o ) const
{
  static Point p;

  p = *this;

  switch ( o )
    {
    case LEFT:  p.X--; break;
    case RIGHT: p.X++; break;
    case UP:    p.Y++; break;
    case DOWN:  p.Y--; break;
    }

  return p;
}

Point &Point::operator+= ( Orientation o )
{
  switch ( o )
    {
    case LEFT:  X--; break;
    case RIGHT: X++; break;
    case UP:    Y++; break;
    case DOWN:  Y--; break;
    }

  return *this;
}

int Point::is ( int x, int y ) const
{
  return ( X==x && Y==y );
}
