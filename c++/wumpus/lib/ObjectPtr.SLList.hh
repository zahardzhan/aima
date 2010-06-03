// This may look like C code, but it is really -*- C++ -*-
// WARNING: This file is obsolete.  Use ../SLList.h, if you can.
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


#ifndef _ObjectPtrSLList_h
#ifdef __GNUG__
#pragma interface
#endif
#define _ObjectPtrSLList_h 1

#include <Pix.h>
#include "Object.hh"

#ifndef _ObjectPtrSLListNode_h
#define _ObjectPtrSLListNode_h 1

struct ObjectPtrSLListNode
{
  ObjectPtrSLListNode*         tl;
  ObjectPtr                    hd;
                         ObjectPtrSLListNode() { }
                         ObjectPtrSLListNode(const ObjectPtr  h, ObjectPtrSLListNode* t = 0);
                         ~ObjectPtrSLListNode() { }
};


inline ObjectPtrSLListNode::ObjectPtrSLListNode(const ObjectPtr  h, ObjectPtrSLListNode* t)
:tl(t), hd(h) {}

typedef ObjectPtrSLListNode* ObjectPtrSLListNodePtr;

#endif


class ObjectPtrSLList
{
protected:
  ObjectPtrSLListNode*        last;

public:
                        ObjectPtrSLList();
                        ObjectPtrSLList(const ObjectPtrSLList& a);
                        ~ObjectPtrSLList();

  ObjectPtrSLList&            operator = (const ObjectPtrSLList& a);

  int                   empty();
  int                   length();

  void                  clear();

  Pix                   prepend(ObjectPtr  item);
  Pix                   append(ObjectPtr  item);

  void                  join(ObjectPtrSLList&);

  Pix                   prepend(ObjectPtrSLListNode*);
  Pix                   append(ObjectPtrSLListNode*);

  ObjectPtr&                  operator () (Pix p);
  Pix                   first();
  void                  next(Pix& p);
  int                   owns(Pix p);
  Pix                   ins_after(Pix p, ObjectPtr  item);
  void                  del_after(Pix p);

  ObjectPtr&                  front();
  ObjectPtr&                  rear();
  ObjectPtr                   remove_front();
  int                   remove_front(ObjectPtr& x);
  void                  del_front();

  void                  error(const char* msg);
  int                   OK();
};

inline ObjectPtrSLList::~ObjectPtrSLList()
{
  clear();
}

inline ObjectPtrSLList::ObjectPtrSLList()
{
  last = 0;
}

inline int ObjectPtrSLList::empty()
{
  return last == 0;
}


inline Pix ObjectPtrSLList::first()
{
  return (last == 0)? 0 : Pix(last->tl);
}

inline void ObjectPtrSLList::next(Pix& p)
{
  p = (p == 0 || p == last)? 0 : Pix(((ObjectPtrSLListNode*)(p))->tl);
}

inline ObjectPtr& ObjectPtrSLList::operator () (Pix p)
{
  if (p == 0) error("null Pix");
  return ((ObjectPtrSLListNode*)(p))->hd;
}

inline ObjectPtr& ObjectPtrSLList::front()
{
  if (last == 0) error("front: empty list");
  return last->tl->hd;
}

inline ObjectPtr& ObjectPtrSLList::rear()
{
  if (last == 0) error("rear: empty list");
  return last->hd;
}

#endif
