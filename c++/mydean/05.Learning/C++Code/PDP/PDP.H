/* PDP.H
 *
 * This class encapsulates the pdp training algorithm.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

const int MAX_ADJUSTMENTS = 100000; // Don't cycle more than this many times
const int MAX_INPUTS = 1000;      // If you have a function with more than
                                  // 1000 inputs, you're in big trouble already
const int MAX_WEIGHTS = 1000;
const int FAILURE = -1;

class Function;
class PDP {
   int inputs[MAX_INPUTS];
   double (* net)(int inputs[], double weights[]);
   void (* delta)(int inputs[], int output,
                   double weights[], double deltas[]);

   int success(Function *target, double weights[]);
   double mse(Function *target, double weights[]);
   void gradient(Function* target, double weights[], double rate);

public:
   static int num_weights;
   static int num_inputs;
   PDP(double (* _net)(int inputs[], double weights[]),
       void (* _delta)(int inputs[], int output,
                       double weights[], double deltas[]));
   ~PDP();

   int trial(Function* target, int stat, double rate);
   void average(Function* target, int attempts, double rate);
};

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

