#ifndef _Environment_HH_
#define _Environment_HH_

#include "Object.hh"
#include "ObjectPtr.SLList.hh"

class Environment
{
public:
    
  Environment();
  virtual ~Environment();
  
  virtual void addObject ( Object* );
  
  virtual int stillRunning() = 0;
  
  virtual void reset();
  virtual void done();
  
  virtual void trials ( int numTrials, int maxSteps );
  virtual void run ( int maxSteps );
  virtual void preUpdate() {};
  virtual void postUpdate() {};
  virtual void updateStats();
  virtual void step();

  virtual void display() = 0;
  virtual void displayScores();
  virtual void displayStats();
  
protected:

  ObjectPtrSLList objectList;
  int numSteps;

private:
  
};

#endif
