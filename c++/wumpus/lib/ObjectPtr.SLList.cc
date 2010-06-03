// This may look like C code, but it is really -*- C++ -*-
// WARNING: This file is obsolete.  Use ../SLList.cc, if you can.
/* 
Copyright (C) 1988 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifdef __GNUG__
#pragma implementation
#endif
#include <limits.h>
#include <stream.h>
#include <builtin.h>
#include "ObjectPtr.SLList.hh"

void ObjectPtrSLList::error(const char* msg)
{
  (*lib_error_handler)("SLList", msg);
}

int ObjectPtrSLList::length()
{
  int l = 0;
  ObjectPtrSLListNode* t = last;
  if (t != 0) do { ++l; t = t->tl; } while (t != last);
  return l;
}

ObjectPtrSLList::ObjectPtrSLList(const ObjectPtrSLList& a)
{
  if (a.last == 0)
    last = 0;
  else
  {
    ObjectPtrSLListNode* p = a.last->tl;
    ObjectPtrSLListNode* h = new ObjectPtrSLListNode(p->hd);
    last = h;
    for (;;)
    {
      if (p == a.last)
      {
        last->tl = h;
        return;
      }
      p = p->tl;
      ObjectPtrSLListNode* n = new ObjectPtrSLListNode(p->hd);
      last->tl = n;
      last = n;
    }
  }
}

ObjectPtrSLList& ObjectPtrSLList::operator = (const ObjectPtrSLList& a)
{
  if (last != a.last)
  {
    clear();
    if (a.last != 0)
    {
      ObjectPtrSLListNode* p = a.last->tl;
      ObjectPtrSLListNode* h = new ObjectPtrSLListNode(p->hd);
      last = h;
      for (;;)
      {
        if (p == a.last)
        {
          last->tl = h;
          break;
        }
        p = p->tl;
        ObjectPtrSLListNode* n = new ObjectPtrSLListNode(p->hd);
        last->tl = n;
        last = n;
      }
    }
  }
  return *this;
}

void ObjectPtrSLList::clear()
{
  if (last == 0)
    return;

  ObjectPtrSLListNode* p = last->tl;
  last->tl = 0;
  last = 0;

  while (p != 0)
  {
    ObjectPtrSLListNode* nxt = p->tl;
    delete(p);
    p = nxt;
  }
}


Pix ObjectPtrSLList::prepend(ObjectPtr  item)
{
  ObjectPtrSLListNode* t = new ObjectPtrSLListNode(item);
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
  }
  return Pix(t);
}


Pix ObjectPtrSLList::prepend(ObjectPtrSLListNode* t)
{
  if (t == 0) return 0;
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
  }
  return Pix(t);
}


Pix ObjectPtrSLList::append(ObjectPtr  item)
{
  ObjectPtrSLListNode* t = new ObjectPtrSLListNode(item);
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
    last = t;
  }
  return Pix(t);
}

Pix ObjectPtrSLList::append(ObjectPtrSLListNode* t)
{
  if (t == 0) return 0;
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
    last = t;
  }
  return Pix(t);
}

void ObjectPtrSLList::join(ObjectPtrSLList& b)
{
  ObjectPtrSLListNode* t = b.last;
  b.last = 0;
  if (last == 0)
    last = t;
  else if (t != 0)
  {
    ObjectPtrSLListNode* f = last->tl;
    last->tl = t->tl;
    t->tl = f;
    last = t;
  }
}

Pix ObjectPtrSLList::ins_after(Pix p, ObjectPtr  item)
{
  ObjectPtrSLListNode* u = (ObjectPtrSLListNode*)p;
  ObjectPtrSLListNode* t = new ObjectPtrSLListNode(item);
  if (last == 0)
    t->tl = last = t;
  else if (u == 0) // ins_after 0 means prepend
  {
    t->tl = last->tl;
    last->tl = t;
  }
  else
  {
    t->tl = u->tl;
    u->tl = t;
    if (u == last) 
      last = t;
  }
  return Pix(t);
}


void ObjectPtrSLList::del_after(Pix p)
{
  ObjectPtrSLListNode* u = (ObjectPtrSLListNode*)p;
  if (last == 0 || u == last) error("cannot del_after last");
  if (u == 0) u = last; // del_after 0 means delete first
  ObjectPtrSLListNode* t = u->tl;
  if (u == t)
    last = 0;
  else
  {
    u->tl = t->tl;
    if (last == t)
      last = u;
  }
  delete t;
}

int ObjectPtrSLList::owns(Pix p)
{
  ObjectPtrSLListNode* t = last;
  if (t != 0 && p != 0)
  {
    do
    {
      if (Pix(t) == p) return 1;
      t = t->tl;
    } while (t != last);
  }
  return 0;
}

ObjectPtr ObjectPtrSLList::remove_front()
{
  if (last == 0) error("remove_front of empty list");
  ObjectPtrSLListNode* t = last->tl;
  ObjectPtr res = t->hd;
  if (t == last)
    last = 0;
  else
    last->tl = t->tl;
  delete t;
  return res;
}

int ObjectPtrSLList::remove_front(ObjectPtr& x)
{
  if (last == 0)
    return 0;
  else
  {
    ObjectPtrSLListNode* t = last->tl;
    x = t->hd;
    if (t == last)
      last = 0;
    else
      last->tl = t->tl;
    delete t;
    return 1;
  }
}


void ObjectPtrSLList::del_front()
{
  if (last == 0) error("del_front of empty list");
  ObjectPtrSLListNode* t = last->tl;
  if (t == last)
    last = 0;
  else
    last->tl = t->tl;
  delete t;
}

int ObjectPtrSLList::OK()
{
  int v = 1;
  if (last != 0)
  {
    ObjectPtrSLListNode* t = last;
    long count = LONG_MAX;      // Lots of chances to find last!
    do
    {
      count--;
      t = t->tl;
    } while (count > 0 && t != last);
    v &= count > 0;
  }
  if (!v) error("invariant failure");
  return v;
}
