/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: dataTest.C                                          */
/*    ASGN: Final                                               */
/*    DATE: Thu Jun 23 22:23:46 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include <DataNode.H>
#include <DataList.H>
#include <iostream.h>
#include <main.H>
int main(int ac, char ** av)
{
   DataNode::State test1_result, test2_result;
   DataNode* D1 = new DataNode("D1");
   DataNode* D2 = new DataNode("D2");
   DataNode* D3 = new DataNode("D3");
   DataNode* D4 = new DataNode("D4");
  
   D1->addJustification(G_empty);
   D2->addJustification(G_empty);
   D3->addJustification(D1);
   D3->addJustification(D2);

  
   D4->addJustification(D3);
   D4->addJustification(D4);
   test1_result = D3->state();
   D1->removeJustification(G_empty);
   test2_result = D3->state();
   if((test1_result == DataNode::IN) && (test2_result == DataNode::OUT)) 
      {
         cout << " It worked " << endl;
      }
   return 1;

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

