/* PDP.C
 *
 * This class encapsulates the pdp training algorithm.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <math.h>
#include <stdlib.h>
#include <iostream.h>
#include "PDP.H"
#include "Function.H"

double net(int inputs[], double weights[]);
void delta(int inputs[], int output, double weights[], double deltas[]);

// A function that takes 2 inputs.
int or_func(int *inputs)
{
   if(inputs[0] || inputs[1])
      return 1;
   else
      return 0;
}
 
// A function that takes 2 inputs.
int and_func(int *inputs)
{
   if(inputs[0] && inputs[1])
      return 1;
   else
      return 0;
}
 
// A function that takes 2 inputs.
int xor_func(int *inputs)
{
   if(inputs[0] ^ inputs[1])
      return 1;
   else
      return 0;
}

void usage()
{
   cerr << "Usage:  pdp [-or] [-and] [-xor] num_attempts learning_rate"
        << endl;
   cerr << "        -or  use the 2 bit or  algorithm" << endl;
   cerr << "        -and use the 2 bit and algorithm" << endl;
   cerr << "        -xor use the 2 bit xor algorithm" << endl;
   cerr << "        num_attempts is the number of training attempts" << endl;
   cerr << "        learning_rate is the learning rate, try 1 or 2" << endl;
   exit(1);
}

int main(int argc, char *argv[])
{
   // Comment this out for debugging. Initialize random number generator.
#ifndef DEBUG
   srand((unsigned int) time(0));
#endif

   if(argc != 4)
      usage();

   PDP pdp(net, delta);

   Function *function;

   // Figure out which of the predefined functions to use. You can add your own
   if(argv[1][0] == '-')
      switch(argv[1][1]) {
      case 'o':
         function = new Function(2, or_func);
         break;
      case 'a':
         function = new Function(2, and_func);
         break;
      case 'x':
         function = new Function(2, xor_func);
         break;
      default:
         usage();
      }
   else
      usage();

   int num_attempts = atoi(argv[2]);
   int learning_rate = atoi(argv[3]);

   // Calcuale average time to learn the below functions, over the given
   // number of attempts and the given learning rate.
   pdp.average(function, num_attempts, learning_rate);

   delete function;

   return 0;
}

PDP::PDP(double (* _net)(int inputs[], double weights[]),
         void (* _delta)(int inputs[], int output,
                         double weights[], double deltas[]))
{
   net = _net;
   delta = _delta;
}

PDP::~PDP()
{
}

int PDP::success(Function *target, double weights[])
{
   for(int x = 0; x < num_inputs; x++)
      inputs[x] = 0;

   x = 0;
   while(x >= 0) {
      if(fabs(target->execute(inputs) - (*net)(inputs, weights)) >= 0.4)
         return 0;
      for(x = num_inputs - 1; x >= 0; x--) {
         inputs[x] = !inputs[x];
         if(inputs[x] == 1)
            break;
      }
   }

   return 1;   
}

double PDP::mse(Function *target, double weights[])
{
   double sum = 0;

   for(int x = 0; x < num_inputs; x++)
      inputs[x] = 0;

   double result;

   x = 0;
   while(x >= 0) {
      result = target->execute(inputs) - (*net)(inputs, weights);
      sum += result * result;

      for(x = num_inputs - 1; x >= 0; x--) {
         inputs[x] = !inputs[x];
         if(inputs[x] == 1)
            break;
      }
   }

   return sum;
}

void PDP::gradient(Function* target, double weights[], double rate)
{
   double deltas[MAX_INPUTS];

   int x = 0;
   while(x >= 0) {
      delta(inputs, target->execute(inputs), weights, deltas);

      for(x = 0; x < num_weights; x++)
         weights[x] += deltas[x] * rate;

      for(x = num_inputs - 1; x >= 0; x--) {
         inputs[x] = !inputs[x];
         if(inputs[x] == 1)
            break;
      }
   }   
}

// Try to train the net to learn the given function. It returns the number
// of adjustments needed to learn the function, or FAILURE if it was never
// learned. The variable "stats" tells whether or not to print information
// while training.
int PDP::trial(Function* target, int stat, double rate)
{
   if(target->get_num_inputs() != num_inputs) {
      cerr << "number of inputs for network and function do not match" << endl;
      exit(1);
   }

   int freq = 10;    // How often do we want results printed?

   double weights[MAX_WEIGHTS];
   for(int x = 0; x < num_weights; x++)
      weights[x] = (rand() % 10000) / 5000.0;  // From 0 to 2

   for(int n = 0; n < MAX_ADJUSTMENTS && !success(target, weights); n++) {
      if(!stat && (n % freq == 0))
         cout << "Adjustments: " << n
              << " Error: " << mse(target, weights) << endl;

      gradient(target, weights, rate);
   }

   if(!stat) {
      if(n < MAX_ADJUSTMENTS) {
         cout << "Weights:";
         for(x = 0; x < num_weights; x++)
            cout << " " << weights[x];
         cout << endl;
      } else
         cout << "Function not learned in " << MAX_ADJUSTMENTS
              << " adjustments" << endl;
   }

   if(n < MAX_ADJUSTMENTS)
      return n;
   else
      return FAILURE;
}

void PDP::average(Function* target, int attempts, double rate)
{
   int successes = 0;
   int adjustments;
   double total = 0;

   for(int i = 0; i < attempts; i++) {
      adjustments = trial(target, 1, rate);
      if(adjustments != FAILURE) {
         successes++;
         total += adjustments;
      }
   }

   if(successes > 0)
      cout << "The average is " << total / successes << " for "
           << successes << " successes out of " << attempts
           << " attempts." << endl;
   else
      cout << "No successes out of " << attempts << " attempts." << endl;
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

