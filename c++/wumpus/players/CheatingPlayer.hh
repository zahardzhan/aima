#ifndef __CheatingPlayer_HH__
#define __CheatingPlayer_HH__

//
// This is the definition of your Player class.  It is a subclass
// of class "Player".
//
// The 5 method you must have are:
//
// A constructor
// A destructor
// void reset()                       - Resets the Player at the beginning of
//                                      each trial.
// Action process ( Percept &percept) - Takes a percept and returns an action.
// void done()                        - Called with Game is over.
//

#include "Player.hh"

class CheatingPlayer : public Player
{
public:

  CheatingPlayer();
  virtual ~CheatingPlayer();

  virtual void reset();
  virtual const Action process ( const Percept &percept );
  virtual void done();
};

#endif
