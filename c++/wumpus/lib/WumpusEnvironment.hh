#ifndef _WumpusEnvironment_HH_
#define _WumpusEnvironment_HH_

#include "GridEnvironment.hh"
#include "Orientations.hh"

class WumpusEnvironment : public GridEnvironment
{
public:

  WumpusEnvironment ( int size=0 );
  WumpusEnvironment ( const char * );
  virtual ~WumpusEnvironment();

  virtual int stillRunning();
  virtual void preUpdate();
  virtual void postUpdate();
  
  virtual int isDeadly ( int x, int y );
  virtual int isDeadly ( const Point &point );

  virtual int isWumpusNear ( int x, int y );
  virtual int isWumpusNear ( const Point &point );
  
  virtual int killWumpus ( int x, int y );
  virtual int killWumpus ( const Point &point );

  virtual void launchArrow ( int x, int y, Orientation o );
  virtual void launchArrow ( const Point &point, Orientation o );

  virtual int didWumpusDie() const;
  
protected:

  int wumpusDiedThisTime;
  int wumpusDiedLastTime;

  void writeToFile ( const char *);
};

int getWorldSize(const char *filename);

#endif
