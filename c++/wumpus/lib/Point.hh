#ifndef __Point_HH__
#define __Point_HH__

#include "Orientations.hh"
#include <iostream.h>

class Point
{
  friend inline ostream& operator<< ( ostream &o, const Point &p );
  
public:

  Point ( int x=0, int y=0 );
  virtual ~Point();

  virtual int x() const;
  virtual int y() const;
  virtual int is ( int x, int y ) const;

  virtual int operator== ( const Point &p ) const;
  virtual Point &operator+ ( Orientation o ) const;
  virtual Point &operator+= ( Orientation o );
  
  virtual void x ( int x );
  virtual void y ( int y );
  virtual void set ( int x, int y );
  
protected:

  int X;
  int Y;
};

inline ostream& operator<< ( ostream &o, const Point &p )
{
  return o << "(" << p.X << "," << p.Y << ")";
}

#endif
