#ifndef _Gold_HH_
#define _Gold_HH_

#include "GridObject.hh"

class Gold : public GridObject
{
public:

  Gold( int x, int y );
  virtual ~Gold();

  virtual void reset();
  virtual void update();
  virtual void display() const;
  virtual void printScore() const {};
  virtual void updateStats() {};
  virtual void printStats() {};

  virtual int isGotten() const;
  virtual int get();

  void write(ofstream &) const;

protected:

  int exists;
};

#endif
