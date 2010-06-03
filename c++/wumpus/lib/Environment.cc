#include "Environment.hh"
#include <iostream.h>

//
//
//
Environment::Environment()
{
  numSteps = 0;
}

//
//
//
Environment::~Environment()
{
  while ( !objectList.empty() )
    delete objectList.remove_front();
}

//
//
//
void Environment::addObject ( Object *obj )
{
  objectList.append ( obj );
  obj->linkToEnv ( this );
}

//
//
//
void Environment::trials ( int numTrials, int maxSteps )
{
  int i;

  for ( i=0; i<numTrials; i++ )
    {
      cout << endl << endl << "Trial " << i << ":" << endl << endl;
      run ( maxSteps );
      updateStats();
    }

  displayStats();
}

//
//
//
void Environment::run ( int maxSteps )
{
  numSteps = 0;

  reset();

  cout << "Initial:" << endl;
  display();
  
  for ( numSteps=0; stillRunning() && numSteps<maxSteps; numSteps++ )
    step();

  done();
  
  cout << "Final:" << endl;
  display();

  displayScores();
}

//
//
//
void Environment::reset()
{
  Pix o;

  for ( o=objectList.first(); o; objectList.next(o) )
    objectList(o)->reset();
}

//
//
//
void Environment::done()
{
  Pix o;

  for ( o=objectList.first(); o; objectList.next(o) )
    objectList(o)->done();
}

//
//
//
void Environment::updateStats()
{
  Pix o;

  for ( o=objectList.first(); o; objectList.next(o) )
    objectList(o)->updateStats();
}

//
//
//
void Environment::step()
{
  cout << "Step " << numSteps << ":" << endl;
  
  preUpdate();
  
  Pix o;
  
  for ( o = objectList.first(); o; objectList.next(o) )
    objectList(o)->update();

  postUpdate();
}

//
//
//
void Environment::displayScores()
{
  Pix o;
  
  cout << "Scores:" << endl;

  for ( o = objectList.first(); o; objectList.next(o) )
    objectList(o)->printScore();
}

//
//
//
void Environment::displayStats()
{
  Pix o;
  
  for ( o = objectList.first(); o; objectList.next(o) )
    objectList(o)->printStats();
}
