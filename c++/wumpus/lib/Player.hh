#ifndef __Player_HH__
#define __Player_HH__

#include "Percept.hh"
#include "Actions.hh"
#include "Agent.hh"
#include "Percept.DLList.hh"
#include "Action.DLList.hh"

class Player
{
  friend Agent;
  
public:

  Player();
  virtual ~Player();

  //
  // For use by subclasses
  //
  virtual void reset();
  virtual const Action process ( const Percept &percept ) = 0;
  virtual void done();

  virtual ActorState getState() const;
  virtual int numGold() const;
  virtual int numArrows() const;
  virtual int getScore() const;
  
  //
  // Interfacing with Simulation
  //
  virtual void linkToAgent ( Agent *agentPtr );
  virtual const Action think ( const Percept &percept );
  virtual void preProcess ( const Percept &percept );
  virtual void postProcess ( const Action action );
  
protected:

  PerceptDLList perceptList;
  ActionDLList actionList;

private:
  Agent *agent;

  static Player *player;
};


#endif
