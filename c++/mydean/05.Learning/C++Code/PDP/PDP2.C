/* PDP2.C
 *
 * This file hold some functions we need to simulate a network. It is
 * linked together with PDP.C to form the executable "pdp2".
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <math.h>
#include "PDP.H"

//                      w_0
//		   x_0 ----- hout1
//		       \   /   \
//		    w_1 \ / w_4 \
//		         X       o ---- out
//		    w_2 / \ w_5 /
//		       /   \   /
//		   x_1 ----- hout2
//		        w_3
//

int PDP::num_weights = 6;   // How many weights this network has
int PDP::num_inputs = 2;    // How many inputs this network has

double sigmoid(double x)
{
   return 1 / (1 + exp(1 - x));
}

double net(int inputs[], double weights[])
{
   return sigmoid((weights[4]
                   * sigmoid(weights[0] * inputs[0]
                             + weights[2] * inputs[1]))
                   + weights[5]
                     * sigmoid(weights[1] * inputs[0]
                               + weights[3] * inputs[1]));
}

void delta(int inputs[], int output, double weights[], double deltas[])
{
   double out = net(inputs, weights);
   double error = output - out;
   double hout1 = sigmoid(weights[0] * inputs[0] + weights[2] * inputs[1]);
   double hout2 = sigmoid(weights[1] * inputs[0] + weights[3] * inputs[1]);

   deltas[0] = inputs[0] * hout1 * (1 - hout1) * weights[4]
                         * out * (1 - out) * error;

   deltas[1] = inputs[0] * hout2 * (1 - hout2) * weights[5]
                         * out * (1 - out) * error;

   deltas[2] = inputs[1] * hout1 * (1 - hout1) * weights[4]
                         * out * (1 - out) * error;

   deltas[3] = inputs[1] * hout2 * (1 - hout2) * weights[5]
                         * out * (1 - out) * error;

   deltas[4] = hout1 * out * (1 - out) * error;

   deltas[5] = hout2 * out * (1 - out) * error;
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

