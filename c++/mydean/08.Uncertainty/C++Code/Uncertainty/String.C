/* String.C
 *
 * This is a general string class. We include it for a platform-independent
 * string comparison function.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include "String.H"

// Compares two strings. If they are equal, return zero.
int strcmp(const char *a, const char *b)
{
   while(*b) {
      if(*a > *b)
         return 1;
      else if(*a < *b)
         return -1;
      a++;
      b++;
   }
   
   if(*a)
      return 1;
   else
      return 0;
}

// Copy one string to another, but NOT more than n characters.
// Assume that "a" points to allocated memory which can be written into.
void strncpy(char *a, const char *b, int n)
{
   for(int i=0; *b && i<n; i++)
      *a++ = *b++;
   *a = '\0';
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

