#ifndef __RandomPlayer_HH__
#define __RandomPlayer_HH__

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

class RandomPlayer : public Player
{
public:

  RandomPlayer();
  virtual ~RandomPlayer();

  virtual void reset();
  virtual const Action process ( const Percept &percept );
  virtual void done();
};

#endif
