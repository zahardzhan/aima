/* Support.H
 *
 * The code needs a lot of two-value pairs. One value is the support
 * for the node begin false. The other is support for the node being true.
 * The Support class contains one pair, and can perform various
 * mathematical operations on pairs.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#ifndef _SUPPORT_H_
#define _SUPPORT_H_

#include <iostream.h>

class Support {
friend Support operator+(const Support& s1, const Support& s2);  // a + b
friend Support operator*(const Support& s1, const Support& s2);  // a * b
friend Support operator/(const Support& s, double val);          // a / val
friend Support operator*(const Support& s, double val);          // a * val
friend int operator==(const Support& s1, const Support& s2);     // a == b
friend istream& operator>>(istream &i, Support &s);     // read in a support
public:

    double sup[2];  // The pair. sup[0] is support for False, sup[0] for True

    Support(double fsup, double tsup);    // Constructor
    Support();                            // Constructor for { 0, 0 }
    ~Support();                           // Destructor

    Support& operator=(Support& s);       // Assignment
    Support& operator*=(Support &s);      // a *= b
    Support& operator+=(Support &s);      // a += b

    Support normalize();    // Make the values add to 1, keeping same ratio.
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

