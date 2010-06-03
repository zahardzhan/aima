/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: testParser.C                                        */
/*    ASGN: Final                                               */
/*    DATE: Sun Jun 12 18:44:16 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#include <iostream.h>
#include "Parser.H"
#include "LogicNode.H"
#include "Bind.H"

int main()
{
   char e1[]= "(loves larry ?y)";
   char e2[]= "(loves ?x diane)";
   char e3[]= "(?z larry diane kelvin)";
   BindCompare* comp = new BindCompare;
   Queue<Binding, BindCompare>* bindings = new Queue<Binding, BindCompare>(comp);

   LogicNode *node1, *node2, *node3;
   int i = 0, j = 0, k = 0;
   node1 = parse(e1,i);
   node2 = parse(e2,j);
   node3 = parse(e3,k);
   cout << "Before1: "; node1->display();
   cout << " "; node2->display(); cout << endl;
   unify(node1,node2,bindings); 
   bindings->display();
   cout << "After1:  "; node1->display();
   cout << " "; node2->display(); cout << endl;
   cout << "Before2: "; node2->display();
   cout << " "; node3->display(); cout << endl;
   unify(node2,node3,bindings); 
   bindings->display();
   cout << "After2:  "; node2->display();
   cout << " "; node3->display(); cout << endl;
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

