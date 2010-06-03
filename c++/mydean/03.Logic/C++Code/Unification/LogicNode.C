/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: LogicAtoms.C                                        */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun  9 21:45:03 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "LogicNode.H"
#include <Queue.H>
#include <string.h>

/****************************************************************/
/*                                                              */
/* Function Name: LogicNode                                     */
/* Parameters:                                                  */
/*  char symbol : the symbol for the variable                   */
/* Returns: <none>                                              */
/* Effects: creates a variable. A variable as mentioned         */
/* previously is defined to having only a single char as a      */
/* symbol                                                       */
/*                                                              */
/****************************************************************/



LogicNode::LogicNode(char symbol)
{
   symbol_ = symbol;
   type_ = LogicNode::VARIABLE;
   queue_ = new Queue<LogicNode, LogicComparator>(new LogicComparator);
   current_child_ = new LogicNode; //(LogicNode::MARK); LBH 2/96
   current_child_->mark() = LogicNode::MARK;
}


/****************************************************************/
/*                                                              */
/* Function Name:LogicNode                                      */
/* Parameters:                                                  */
/*  char* symbol : the string representing the symbol for the   */
/*                 node                                         */
/*  int start : where the symbol starts in the string           */
/*  int end : where it ends                                     */
/* Returns: <none>                                              */
/* Effects: This constructor is used to create a logic node     */
/* that is a constant                                           */
/*                                                              */
/****************************************************************/


LogicNode::LogicNode(char* symbol, int start, int end){
   char buffer[50];
    for (int i = 0; i < 50; i++)
      buffer[i] = '\0';
   strncpy(buffer, symbol, end-start+1);
   symbol_ = buffer;
   
   type_ = LogicNode::CONSTANT;
   current_child_ = new LogicNode;
   current_child_->mark() = LogicNode::MARK;
   queue_ = new Queue<LogicNode, LogicComparator>(new LogicComparator);   
}


/****************************************************************/
/*                                                              */
/* Function Name:LogicNode                                      */
/* Parameters:                                                  */
/*  NodeType group                                              */
/*                                                              */
/* Returns: <none>                                              */
/* Effects: Creates a logic node that is of type group          */
/*                                                              */
/****************************************************************/


LogicNode::LogicNode(NodeType group)
{
   type_ = LogicNode::GROUP;
   current_child_ = new LogicNode;
   current_child_->mark() = LogicNode::MARK; 
   queue_ = new Queue<LogicNode, LogicComparator>(new LogicComparator);   
}



LogicNode::~LogicNode()
{
   delete queue_;
   delete current_child_;
   return;
}

LogicNode& LogicNode::operator=(LogicNode& logic_node)
{
   symbol_ = logic_node.symbol_;
   type_ = logic_node.type_;
   current_child_ = logic_node.current_child_;
   mark_ = logic_node.mark_;
   queue_ = logic_node.queue_;
   return *this;
}


void LogicNode::insert(LogicNode* child)
{
   queue_->insert(child);
}


void LogicNode::setSymbol(char* string, int length)
{
   XDString temp(string, length);
   symbol_ = temp;
}

/****************************************************************/
/*                                                              */
/* Function Name: nextChild                                     */
/* Parameters: <none>                                           */
/* Returns:                                                     */
/*  1 success                                                   */
/*  0 none                                                      */
/* Effects: gets the next child off the queue making sure       */
/* that the child is not marked. If all the children have       */
/* been visited this function returns 0 else it returns 1       */
/*                                                              */
/****************************************************************/

int LogicNode::nextChild()
{
   current_child_->mark() = LogicNode::MARK;
   queue_->insert(current_child_);
   queue_->remove(current_child_);
   if(current_child_->mark() == LogicNode::MARK)
      {
         return 0;
      } 
   else
      {
         return 1;
      }
   
}


/****************************************************************/
/*                                                              */
/* Function Name: search                                        */
/* Parameters:                                                  */
/*  LogicNode* node : the node to search for                    */
/* Returns:                                                     */
/*  1 found                                                     */
/*  0 did not find                                              */
/* Effects:                                                     */
/*  Searches the queue for the appropriate object               */
/****************************************************************/


int LogicNode::search(LogicNode* node)
{
   LogicNode* temp = new LogicNode(*node);
   int ret_val= queue_->search(node);
   *node = *temp;
   
   return ret_val;
}

LogicNode* LogicNode::child()
{
   return current_child_;
}


LogicNode::NodeType LogicNode::type()
{
   return type_;
}


LogicComparator::~LogicComparator(){;}


int LogicComparator::compare(LogicNode* node, LogicNode* node2)
{
 return 0;
}


/****************************************************************/
/*                                                              */
/* Function Name: equal                                         */
/* Parameters:                                                  */
/*  LogicNode* node : the node in the data structure            */
/*  LogicNode* node2 : the node being compared to               */
/* Returns:                                                     */
/*  1 if true                                                   */
/*  0 if false                                                  */
/* Effects:                                                     */
/*  Tests for equality by comparing the top level symbols       */
/* and testing all the children of the node if they exist       */
/****************************************************************/



int LogicComparator::equal(LogicNode* node, LogicNode* node2)
{
   if (node->type() != LogicNode::GROUP) // is node a group?
      {
         if (node->type() == node2->type()) // no compare the types
            {
               if(node->symbol() == node2->symbol()) // same types and symbols?
                  {
                     return 1; // yes return 1
                  } 
               else 
                  {
                     return 0; // not equal
                  }
            }
         else // not the same type
            { 
               return 0;        
            }
       }
   else // node is a groups so search all of its sub nodes and of node2
      {
         return node->search(node2);
      }
}

void LogicComparator::display(LogicNode* node)
{
   cout << node->symbol() << endl;
   if(node->mark() == LogicNode::MARK) cout << "marked" << endl;
}

void LogicNode::unMarkChildren() {  // LBH 2/96
  LogicNode *current = current_child_;
  do {
    current_child_->mark() = LogicNode::UNMARKED;
    queue_->insert(current_child_);
    queue_->remove(current_child_);
  } while (current_child_ != current);
}

void LogicNode::display() {  // LBH 2/96
  switch (type_) {
    case LogicNode::CONSTANT: cout << " " << symbol_; break;
    case LogicNode::VARIABLE: cout << " ?" << symbol_; break;
    case LogicNode::GROUP:
      cout << "(";
      while (nextChild()) child()->display();
      unMarkChildren();
      cout << ")";
      break;
    default: break;
    }
  cout << " ";
}


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

