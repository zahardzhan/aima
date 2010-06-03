/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: LogicAtoms.H                                        */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun  8 23:04:40 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef LOGICATOMS_HEADER
#define LOGICATOMS_HEADER

#include <Compare.H>
#include <XDString.H>
#include <Queue.H>

/****************************************************************/
/* CLASS NAME : LogicNode                                       */
/*   this class is the node that is in the parse tree generated */
/* by the the function parser. The LogicNode has a number       */
/* of attributes : it can be a group node, a constant or        */
/* a variable. The LogicNode can be thought of as a single      */
/* symbol abstratction for all the symbols that can be          */
/* manipulated. It can have the property of being a :           */
/* group : a list in lisp                                       */
/* constant : a symbol in lisp                                  */
/* variable : (? x) similar to the construct in the text        */
/*                                                              */
/* There are three different constructors, one for each kind    */
/* of type the node can be.                                     */
/*                                                              */
/*                                                              */
/****************************************************************/


class LogicNode 
{

   LogicNode* current_child_;  
   XDString symbol_;            // symbol representing node
public:
   enum NodeType {CONSTANT, VARIABLE, GROUP, MARK, UNMARKED};
   LogicNode() 
      {
      }
   LogicNode(char symbol); // creates a variable
   LogicNode(char* string, int start, int end); // creates a symbol
   LogicNode(NodeType group); // used to create groups.
   ~LogicNode();
   LogicNode& operator=(LogicNode&);
   // sets the child of the node to be the next child in the queue
   // and if all the children have been visited returns 0
   int nextChild();
   // inserts a child node
   void insert(LogicNode* node);
   // searches in the children of the node to find if node is a child
   int search(LogicNode* node);
   // marks a node as visited
   NodeType& mark()
      {
         return mark_;
      } 
   // returns the current child node
   LogicNode* child();
   // Unmarks the children of this node, if GROUP (LBH 2/96)
   void unMarkChildren();
   // ACCESSORS

   NodeType type();
   void setSymbol(char* string,  int);
  
   friend class LogicComparator;
   XDString symbol()
      {
         return symbol_;
      }
   void display();  // LBH 2/96
private:
   NodeType type_;
   NodeType mark_;              
   Queue<LogicNode,LogicComparator>* queue_; // child nodes
};


#endif

/*
 * Copyright 1994, Brown University, Providence, RI
 *
 * Permission to use and modify this software and its documentation for
 * any purpose other than its incorporation into a commercial product is
 * hereby granted without fee.  Permission to copy and distribute this
 * software and its documentation only for non-commercial use is also
 * granted without fee, provided, however, that the above copyright notice
 * appear in all copies, that both that copyright notice and this permission
 * notice appear in supporting documentation, that the name of Brown
 * University not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior permission,
 * and that the person doing the distribution notify Brown University of
 * such distributions outside of his or her organization. Brown University
 * makes no representations about the suitability of this software for
 * any purpose.  It is provided "as is" without express or implied warranty.
 * Brown University requests notification of any modifications to this
 * software or its documentation.
 *
 * Send the following redistribution information:
 *
 *	Name:
 *	Organization:
 *	Address (postal and/or electronic):
 *
 * To:
 *	Software Librarian
 *	Computer Science Department, Box 1910
 *	Brown University
 *	Providence, RI 02912
 *
 *		or
 *
 *	brusd@cs.brown.edu
 *
 * We will acknowledge all electronic notifications.
 */

