#ifndef _Object_HH_
#define _Object_HH_

#include "ObjectTypes.hh"
#include <SmplStat.h>
#include <iostream.h>
#include <fstream.h>

class Environment;

class Object
{
public:

  Object ( ObjectType objectType=NULL_OBJECT );
  virtual ~Object() {};

  virtual void reset();
  virtual void update() = 0;
  virtual void done();
  virtual void display() const = 0;
  virtual int getScore() const { return score; };
  virtual void printScore() const = 0;
  virtual void updateStats() = 0;
  virtual void printStats() = 0;
  virtual void write(ofstream &) const {};
  
  virtual void linkToEnv ( Environment *envPtr );
  int isA ( ObjectType objectType ) const;
  ObjectType isA() const;
  
protected:

  ObjectType type;
  int score;
  Environment *env;
  SampleStatistic stats;
};

typedef Object *ObjectPtr;

#endif
