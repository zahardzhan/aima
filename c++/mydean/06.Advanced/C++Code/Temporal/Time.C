/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Time.C                                              */
/*    ASGN: Final                                               */
/*    DATE: Sat Jun 11 18:50:57 1994                            */
/****************************************************************/

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */



#include "Time.H"



Time::Time()
{
   time_ = 0;
}



Time::Time(const Time& time)
{
   time_ = time.time_;
}



Time::~Time()
{
}


Time& Time::operator=(const Time& time)
{
   time_ = time.time_;
   return *this;
}

 
Time::Time(int time){
   time_ = time;
}

int Time::operator<(Time& time){
  if(time_ == -1)               // if infinity then return false
     {
        return 0;
     }
  else  if(time.time_ == -1)    // if time infinity, (object not)
     {                          // then return true
        return 1;
     }
  else if (time_ > time.time_ ) // no problems with infinity so make comparison
     {
        return 0;
     }
  else 
     {
        return 1;
     }
}



int Time::operator>(Time& time)
{
   return  time < *this;
}


int Time::operator==(Time& time)
{
   if(time_ == time.time_ )
      return 1;
   return 0;
}



Time Time::operator+(Time& time)
{
   if((time.time_ == -1) || (time_ == -1)) // test for infinity 
      {
         return -1;             // one of them was infinite so return infinity
      } 
   else  
      {
         return time.time_ + time_;
      }
}


Time& Time::operator+=(Time& time) 
{
   *this = *this+time;
   return *this;
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

