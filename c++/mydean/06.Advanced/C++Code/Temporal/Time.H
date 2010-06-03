/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Time.H                                              */
/*    ASGN: Final                                               */
/*    DATE: Sat Jun 11 18:49:18 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */


#ifndef TIME_HEADER
#define TIME_HEADER
#include <iostream.h>

/****************************************************************/
/* CLASS NAME : Time                                            */
/*    Rather than use integers for time, we have to use         */
/* an object that represents time, because of the problem of    */
/* infinity. Infinity, is not a symbol that is represented      */
/* by an integer. For the purposes of this program the integer  */
/* -1 represents infinity. To handle infinity, the + operator   */
/* and the <,>,== operators have been overloaded for this       */
/* data type.                                                   */
/*                                                              */
/****************************************************************/


class Time 
{
   int time_;
public:
   Time();                      // default constructor
   Time(const Time& time);      // copy constructor
   Time& operator=(const Time& time); // assignment operator
   Time(int time);                    //   
   ~Time();
   // outputs time 
friend ostream& operator<<(ostream& os, Time& time) 
   {
      os << time.time_;
      return os;
   };
   // overloaded operators for time
   // they are written so as to handle the special case of infinity
   Time& operator+=(Time& time);
   Time operator+(Time& time);
   int operator<(Time& time);
   int operator>(Time& time);
   int operator==(Time& time);
   
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

