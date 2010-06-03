#ifndef _Percept_HH_
#define _Percept_HH_

//
// Access to the Percept's hint and image members will only
// be allowed if the symbol FULL_SYSTEM is defined.
//

#include "WumpusEnvironment.hh"
#include "Point.hh"
#include "Image.hh"
#include <iostream.h>
#include <String.h>

class Percept
{
  friend inline ostream&operator<< ( ostream &o, const Percept &percept );

public:

  Percept();
  virtual ~Percept();

  virtual void perceive( WumpusEnvironment &env, int bumped, const Point &location, Orientation o );
  
  virtual int isStench() const;
  virtual int isBreeze() const;
  virtual int isGlitter() const;
  virtual int isBump() const;
  virtual int isScream() const;
#ifdef FULL_SYSTEM
  virtual const String &getHint() const;
  virtual const Image &getImage() const;
#endif
  
protected:

  virtual void init();
  virtual void setStench ( WumpusEnvironment &env, const Point &location );
  virtual void setBreeze ( WumpusEnvironment &env, const Point &location );
  virtual void setGlitter ( WumpusEnvironment &env, const Point &location );
  virtual void setBump ( int bumped );
  virtual void setScream ( WumpusEnvironment &env );

  virtual void setHint ( WumpusEnvironment &env, const Point &loc, Orientation o );
  virtual const String subjectPhrase ( ObjectType type, Point &loc, WumpusEnvironment &env );
  virtual const String subjectPhrase ( const Point &pos, const Point &loc, Orientation o );
  virtual const String predicatePhrase ( ObjectType type, Point &loc, WumpusEnvironment &env );
  virtual const String prepositionalPhrase ( const Point &pos, const Point &loc, Orientation o );

  virtual void setImage ( WumpusEnvironment &env, const Point &location, Orientation o );

  int stench;
  int breeze;
  int glitter;
  int bump;
  int scream;
  String hint;
  Image image;
};

inline ostream&operator<< ( ostream &o, const Percept &percept )
{
  o << "[";

  if ( percept.stench )
    o << " Stench";;
  
  if ( percept.breeze )
    o << " Breeze";;
  
  if ( percept.glitter )
    o << " Glitter";;
  
  if ( percept.bump )
    o << " Bump";;
  
  if ( percept.scream )
    o << " Scream";;

#ifdef FULL_SYSTEM
  if ( percept.hint.length() )
    o << " \"" << percept.hint << "\"";
#endif
  
  return o << " ]";
}

typedef const Percept cPercept;

#endif
