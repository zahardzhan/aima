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


#ifndef _PerceptDLList_h
#ifdef __GNUG__
#pragma interface
#endif
#define _PerceptDLList_h 1

#include <Pix.h>
#include "Percept.hh"

#ifndef _PerceptDLListNode_h
#define _PerceptDLListNode_h 1

struct PerceptDLListNode
{
  PerceptDLListNode*         bk;
  PerceptDLListNode*         fd;
  const Percept                    hd;
                         PerceptDLListNode();
                         PerceptDLListNode(const Percept  h, 
                                       PerceptDLListNode* p = 0,
                                       PerceptDLListNode* n = 0);
                         ~PerceptDLListNode();
};

inline PerceptDLListNode::PerceptDLListNode() {}

inline PerceptDLListNode::PerceptDLListNode(const Percept  h, PerceptDLListNode* p,
                                    PerceptDLListNode* n)
  :bk(p), fd(n), hd(h) {}

inline PerceptDLListNode::~PerceptDLListNode() {}

typedef PerceptDLListNode* PerceptDLListNodePtr;

#endif

class PerceptDLList
{
  friend class          PerceptDLListTrav;

  PerceptDLListNode*        h;

public:
                        PerceptDLList();
                        PerceptDLList(const PerceptDLList& a);
                        ~PerceptDLList();

  PerceptDLList&            operator = (const PerceptDLList& a);

  int                   empty();
  int                   length();

  void                  clear();

  Pix                   prepend(const Percept  item);
  Pix                   append(const Percept  item);
  void                  join(PerceptDLList&);

  const Percept&                  front();
  const Percept                   remove_front();
  void                  del_front();

  const Percept&                  rear();
  const Percept                   remove_rear();
  void                  del_rear();

  const Percept&                  operator () (Pix p);
  Pix                   first();
  Pix                   last();
  void                  next(Pix& p);
  void                  prev(Pix& p);
  int                   owns(Pix p);
  Pix                   ins_after(Pix p, const Percept  item);
  Pix                   ins_before(Pix p, const Percept  item);
  void                  del(Pix& p, int dir = 1);
  void                  del_after(Pix& p);

  void                  error(const char* msg);
  int                   OK();
};


inline PerceptDLList::~PerceptDLList()
{
  clear();
}

inline PerceptDLList::PerceptDLList()
{
  h = 0;
}

inline int PerceptDLList::empty()
{
  return h == 0;
}


inline void PerceptDLList::next(Pix& p)
{
  p = (p == 0 || p == h->bk)? 0 : Pix(((PerceptDLListNode*)p)->fd);
}

inline void PerceptDLList::prev(Pix& p)
{
  p = (p == 0 || p == h)? 0 : Pix(((PerceptDLListNode*)p)->bk);
}

inline Pix PerceptDLList::first()
{
  return Pix(h);
}

inline Pix PerceptDLList::last()
{
  return (h == 0)? 0 : Pix(h->bk);
}

inline const Percept& PerceptDLList::operator () (Pix p)
{
  if (p == 0) error("null Pix");
  return ((PerceptDLListNode*)p)->hd;
}

inline const Percept& PerceptDLList::front()
{
  if (h == 0) error("front: empty list");
  return h->hd;
}

inline const Percept& PerceptDLList::rear()
{
  if (h == 0) error("rear: empty list");
  return h->bk->hd;
}

#endif
