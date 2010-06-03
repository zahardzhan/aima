/* Support.C
 *
 * The code sends around a lot of two-double bundles, one for false
 * and one for true. The Support class surrounds this bundle cleanly.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <math.h>
#include "Support.H"

// Constructor. Use given values for initialization.
Support::Support(double fsup, double tsup)
{
   sup[0] = fsup;
   sup[1] = tsup;
}

// Constructor. Assume initial values are zero.
Support::Support()
{
   sup[0] = 0;
   sup[1] = 0;
}

// Destructor
Support::~Support()
{
}

// Make the values add to 1, keeping the same ratio. This is called
// normalization.
Support Support::normalize()
{
   return Support(sup[0] / (sup[0] + sup[1]), sup[1] / (sup[0] + sup[1]));
}

// Support a, b;    a = b;
Support& Support::operator=(Support& s)
{
   sup[0] = s.sup[0];
   sup[1] = s.sup[1];

   return *this;
}

// Support a, b;    a *= b;
Support& Support::operator*=(Support &s)
{
   sup[0] = sup[0] * s.sup[0];
   sup[1] = sup[1] * s.sup[1];

   return *this;
}

// Support a, b;    a += b;
Support& Support::operator+=(Support &s)
{
   sup[0] = sup[0] + s.sup[0];
   sup[1] = sup[1] + s.sup[1];

   return *this;
}

// Support a, b, c;    c = a + b;
Support operator+(const Support& s1, const Support& s2)
{
   return Support(s1.sup[0] + s2.sup[0], s1.sup[1] + s2.sup[1]);
}

// Support a, b, c;    c = a * b;
Support operator*(const Support& s1, const Support& s2)
{
   return Support(s1.sup[0] * s2.sup[0], s1.sup[1] * s2.sup[1]);
}

// Support a,b; double val;    b = a / v;
Support operator/(const Support& s, double val)
{
   return Support(s.sup[0] / val, s.sup[1] / val);
}

// Support a,b; double val;    b = a * v;
Support operator*(const Support& s, double val)
{
   return Support(s.sup[0] * val, s.sup[1] * val);
}

// Comparison between doubleing point numbers is difficult because of
// numerical precision errors. If they're close, they're equal.
int operator==(const Support& s1, const Support& s2)
{
   return    fabs(s1.sup[0] - s2.sup[0]) < 0.001
          && fabs(s1.sup[1] - s2.sup[1]) < 0.001;
}

// Read in a Support object
istream& operator>>(istream &i, Support &s)
{
   i >> s.sup[0] >> s.sup[1];

   return i;
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

