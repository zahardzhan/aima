#ifndef _Pit_HH_
#define _Pit_HH_

#include "GridObject.hh"

class Pit : public GridObject
{
public:

  Pit ( int x, int y );
  virtual ~Pit();

  virtual void reset() {};
  virtual void update() {};
  virtual void display() const;
  virtual void printScore() const {};
  virtual void updateStats() {};
  virtual void printStats() {};

  void write(ofstream &);
};

#endif
