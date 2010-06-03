#include "Percept.hh"
#include "Gold.hh"
#include "Wumpus.hh"
#include "Pit.hh"
#include "RndGen.hh"
#include <String.h>
#include <strstream.h>

Percept::Percept()
{
  init();
}

Percept::~Percept()
{
}

void Percept::perceive ( WumpusEnvironment &env, int bumped, const Point &location, Orientation o )
{
  init();
  
  setStench ( env, location );
  setBreeze ( env, location );
  setGlitter ( env, location );
  setBump ( bumped );
  setScream ( env );
  setHint ( env, location, o );
  setImage ( env, location, o );
}

void Percept::init()
{
  stench = breeze = glitter = bump = scream = 0;
  hint = "";
  image.erase();
}

void Percept::setStench ( WumpusEnvironment &env, const Point &location )
{
  stench = env.isWumpusNear ( location );
}

void Percept::setBreeze ( WumpusEnvironment &env, const Point &location )
{
  breeze = env.isObjectTypeNear ( PIT, location );
}

void Percept::setGlitter ( WumpusEnvironment &env, const Point &location )
{
  Gold *gold = ( Gold* ) env.objectOfTypeAt ( GOLD, location );
  glitter = gold && !gold->isGotten();
}

void Percept::setBump ( int Bump )
{
  bump = Bump;
}

void Percept::setScream ( WumpusEnvironment &env )
{
  scream = env.didWumpusDie();
}

//
// Language Processing
//

void Percept::setHint ( WumpusEnvironment &env, const Point &loc, Orientation o )
{
  const GridObject *object = ( GridObject* ) env.findRandomObject();
  Point pos = object->loc();

  hint = "";
  switch ( randInt ( 10 ) )
    {
    case 0:
      switch ( randInt ( 1 ) )
	{
	case 0:
	  pos.x ( randInt(1) * ( env.getSize()-1 ) );
	  pos.y ( randInt ( env.getSize()-1 ) );
	  break;
	  
	case 1:
	  pos.y ( randInt(1) * ( env.getSize()-1 ) );
	  pos.x ( randInt ( env.getSize()-1 ) );
	  break;
	}
      
      switch ( randInt ( 2 ) )
	{
	case 0:
	  hint = "there is a wall next to ";
	  hint += subjectPhrase ( pos, pos, o );
	  break;
	  
	case 1:
	  hint = "a wall is next to ";
	  hint += subjectPhrase ( pos, pos, o );
	  break;
	  
	case 2:
	  hint = subjectPhrase ( pos, pos, o );
	  hint += " is next to a wall";
	  break;
	}
      break;

    default:
      switch ( randInt(2) )
	{
	case 0:
	  hint = subjectPhrase ( object->isA(), pos, env );
	  hint += " is ";
	  hint += prepositionalPhrase ( pos, loc, o );
	  break;
	  
	case 1:
	  hint = "there is ";
	  hint += subjectPhrase ( object->isA(), pos, env );
	  hint += " ";
	  hint += prepositionalPhrase ( pos, loc, o );
	  break;
	  
	case 2:
	  hint = predicatePhrase ( object->isA(), pos, env );
	  hint.prepend ( " " );
	  hint.prepend ( subjectPhrase ( pos, loc, o ) );
	  break;
	}
    }
}

const String Percept::subjectPhrase ( ObjectType type, Point &loc, WumpusEnvironment &env )
{
  String text;
  
  switch ( type )
    {
    case WUMPUS:
      if ( randInt(1) )
	text = "a wumpus";
      else
	{
	  Orientation o;

	  do
	    o = ( Orientation ) randInt(3);
	  while ( !env.isValid ( loc+o ) );

	  loc += o;

	  text = "a stench";
	}
      break;
      
    case PIT:
      if ( randInt(1) )
	text = "a pit";
      else
	{
	  Orientation o;

	  do
	    o = ( Orientation ) randInt(3);
	  while ( !env.isValid ( loc+o ) );

	  loc += o;

	  text = "a breeze";
	}
      break;
      
    case GOLD:
      if ( randInt(1) )
	text = "gold";
      else
	text = "a glitter";
      break;

    default:
      break;
    }

  return text;
}

const String Percept::subjectPhrase ( const Point &pos, const Point &loc, Orientation o )
{
//  String text( prepositionalPhrase ( pos, loc, o ) );
  String text =  prepositionalPhrase ( pos, loc, o ) ;
  Regex r ( "\\(location\\|square\\)" );
  
  if ( text.contains ( r ) )
    text.at( 0, 2 ) = "the";
  else
    text.prepend ( randInt(1)? "the location " : "the square " );

  return text;
}

const String Percept::predicatePhrase ( ObjectType type, Point &loc, WumpusEnvironment &env )
{
  String text;
  Point orig = loc;
  String object = subjectPhrase ( type, loc, env );

  switch ( type )
    {
    case WUMPUS:
      if ( orig == loc )
	{
	  text = randInt(1)? "contains " : "has ";
	  text += object;
	}
      else
	switch ( randInt(3) )
	  {
	  case 0: text = "is smelly";  break;
	  case 1: text = "smells bad"; break;
	  case 2: text = "contains "; text += object; break;
	  case 3: text = "has "; text += object; break;
	  }
      break;
	
    case PIT:
      if ( orig == loc )
	{
	  text = randInt(1)? "contains " : "has ";
	  text += object;
	}
      else
	switch ( randInt(3) )
	  {
	  case 0: text = "is breezy";  break;
	  case 1: text = "feels breezy"; break;
	  case 2: text = "contains "; text += object; break;
	  case 3: text = "has "; text += object; break;
	  }
      break;
	
    case GOLD:
      switch ( randInt(2) )
	{
	case 0: text = "contains "; text += object; break;
	case 1: text = "has "; text += object; break;
	case 2: text = "looks glittery"; break;
	}
      break;

    default:
      text = "";
    }

  return text;
}

const String Percept::prepositionalPhrase ( const Point &pos, const Point &loc, Orientation o )
{
  String text;
  Orientation dir;
  int adjacent = 0;
  
  if ( pos == loc+LEFT )
    {
      dir = LEFT;
      adjacent = 1;
    }
  
  if ( pos == loc+RIGHT )
    {
      dir = RIGHT;
      adjacent = 1;
    }
  
  if ( pos == loc+UP )
    {
      dir = UP;
      adjacent = 1;
    }
  
  if ( pos == loc+DOWN )
    {
      dir = DOWN;
      adjacent = 1;
    }

  if ( adjacent )
    {
      int offset = ( int ) dir - ( int ) o;
      if ( offset < 0 )
	offset += 4;
      switch ( offset )
	{
	case 0: text = "ahead of you";  break;
	case 1: text = "to your left";  break;
	case 2: text = "behind you";    break;
	case 3: text = "to your right"; break;
	}
    }
  else
    {
      text = randInt(1)? "in " : "at ";
      text += randInt(1)? "location " : "square ";
      text += dec ( pos.x() );
      text += " ";
      text += dec ( pos.y() );
    }

  return text;
}

//
// Image Processing
//
void Percept::setImage ( WumpusEnvironment &env, const Point &location, Orientation o )
{
  Point p = location + o;

  if ( env.isValid ( p ) )
    {
      int wumpus = ( int ) env.objectOfTypeAt ( WUMPUS, p );
      int pit = ( int ) env.objectOfTypeAt ( PIT, p );
      int gold = ( int ) env.objectOfTypeAt ( GOLD, p );
      image.paint ( wumpus, pit, gold, 0 );
    }
  else
    image.paint ( 0, 0, 0, 1 );
}

int Percept::isStench() const
{
  return stench;
}

int Percept::isBreeze() const
{
  return breeze;
}

int Percept::isGlitter() const
{
  return glitter;
}

int Percept::isBump() const
{
  return bump;
}

int Percept::isScream() const
{
  return scream;
}

#ifdef FULL_SYSTEM
const String &Percept::getHint() const
{
  return hint;
}

const Image &Percept::getImage() const
{
  return image;
}
#endif
