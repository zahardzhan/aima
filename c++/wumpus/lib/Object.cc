#include "Object.hh"

Object::Object ( ObjectType objectType )
{
  type = objectType;
  score = 0;
  env = 0;
}

void Object::reset()
{
  score = 0;
}

void Object::done()
{
}

void Object::linkToEnv ( Environment *envPtr )
{
  env = envPtr;
}

ObjectType Object::isA() const
{
  return type;
}

int Object::isA ( ObjectType objectType ) const
{
  return type == objectType;
}
