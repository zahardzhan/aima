// This may look like C code, but it is really -*- C++ -*-
// WARNING: This file is obsolete.  Use ../DLList.h, if you can.
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


#ifndef _ActionDLList_h
#ifdef __GNUG__
#pragma interface
#endif
#define _ActionDLList_h 1

#include <Pix.h>
#include "Actions.hh"

#ifndef _ActionDLListNode_h
#define _ActionDLListNode_h 1

struct ActionDLListNode
{
  ActionDLListNode*         bk;
  ActionDLListNode*         fd;
  const Action                    hd;
                         ActionDLListNode();
                         ActionDLListNode(const Action  h, 
                                       ActionDLListNode* p = 0,
                                       ActionDLListNode* n = 0);
                         ~ActionDLListNode();
};

inline ActionDLListNode::ActionDLListNode() {}

inline ActionDLListNode::ActionDLListNode(const Action  h, ActionDLListNode* p,
                                    ActionDLListNode* n)
  :bk(p), fd(n), hd(h) {}

inline ActionDLListNode::~ActionDLListNode() {}

typedef ActionDLListNode* ActionDLListNodePtr;

#endif

class ActionDLList
{
  friend class          ActionDLListTrav;

  ActionDLListNode*        h;

public:
                        ActionDLList();
                        ActionDLList(const ActionDLList& a);
                        ~ActionDLList();

  ActionDLList&            operator = (const ActionDLList& a);

  int                   empty();
  int                   length();

  void                  clear();

  Pix                   prepend(const Action  item);
  Pix                   append(const Action  item);
  void                  join(ActionDLList&);

  const Action&                  front();
  const Action                   remove_front();
  void                  del_front();

  const Action&                  rear();
  const Action                   remove_rear();
  void                  del_rear();

  const Action&                  operator () (Pix p);
  Pix                   first();
  Pix                   last();
  void                  next(Pix& p);
  void                  prev(Pix& p);
  int                   owns(Pix p);
  Pix                   ins_after(Pix p, const Action  item);
  Pix                   ins_before(Pix p, const Action  item);
  void                  del(Pix& p, int dir = 1);
  void                  del_after(Pix& p);

  void                  error(const char* msg);
  int                   OK();
};


inline ActionDLList::~ActionDLList()
{
  clear();
}

inline ActionDLList::ActionDLList()
{
  h = 0;
}

inline int ActionDLList::empty()
{
  return h == 0;
}


inline void ActionDLList::next(Pix& p)
{
  p = (p == 0 || p == h->bk)? 0 : Pix(((ActionDLListNode*)p)->fd);
}

inline void ActionDLList::prev(Pix& p)
{
  p = (p == 0 || p == h)? 0 : Pix(((ActionDLListNode*)p)->bk);
}

inline Pix ActionDLList::first()
{
  return Pix(h);
}

inline Pix ActionDLList::last()
{
  return (h == 0)? 0 : Pix(h->bk);
}

inline const Action& ActionDLList::operator () (Pix p)
{
  if (p == 0) error("null Pix");
  return ((ActionDLListNode*)p)->hd;
}

inline const Action& ActionDLList::front()
{
  if (h == 0) error("front: empty list");
  return h->hd;
}

inline const Action& ActionDLList::rear()
{
  if (h == 0) error("rear: empty list");
  return h->bk->hd;
}

#endif
