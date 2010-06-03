/* Perceptron.C
 *
 * This class encapsulates the entire perceptron program.
 */

/*
 * Copyright 1994, Brown University, Providence, RI
 * See end of file for full copyright information
 */

#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include "Perceptron.H"
#include "Function.H"

// A function that takes 2 inputs.
int or_func(int inputs[])
{
   if(inputs[0] || inputs[1])
      return 1;
   else
      return 0;
}

// A function that takes 2 inputs.
int and_func(int inputs[])
{
   if(inputs[0] && inputs[1])
      return 1;
   else
      return 0;
}

// A function that takes 2 inputs.
int xor_func(int inputs[])
{
   if(inputs[0] ^ inputs[1])
      return 1;
   else
      return 0;
}

// Print information about how to use this program
void usage()
{
   cerr << "Usage:  perceptron [-or] [-and] [-xor]" << endl;
   cerr << "        -or  learn the 2 bit or  algorithm" << endl;
   cerr << "        -and learn the 2 bit and algorithm" << endl;
   cerr << "        -xor learn the 2 bit xor algorithm" << endl;
   exit(1);
}

// The main() function is the first function called in this program.
// Parse the command line arguments to find out which function the user
// wants to learn. Of course, you are welcome to add more functions
// yourself, with inputs of more than just 2 bits. However, you'll
// have to compile them in. There is no example file to read.
int main(int argc, char *argv[])
{
   // Comment this out for debugging. Initialize random number generator.
#ifndef DEBUG
   srand((unsigned int) time(0));
#endif

   if(argc != 2)
      usage();

   Perceptron perceptron;
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

   int weights[MAX_INPUTS];

   // Initialize all weights to zero
   for(int x = 0; x < function->get_num_inputs(); x++)
      weights[x] = 0;

   perceptron.test(function, weights);    // Try to learn the function

   delete function;

   return 0;
}

// Try to learn the function, given the initial weights, by iterating.
// After each iteration, test to see if we have successfully learned the
// function.
void Perceptron::test(Function *_function, int *_weights)
{
   function = _function;
   weights = _weights;
   num_inputs = function->get_num_inputs();

   inputs = new int[num_inputs];

   int result;
   int x;

   // Try to adjust the network until successful, or until too many adjustments
   for(int adjustments = 0; !success() && adjustments < MAX_ADJUSTMENTS;
       adjustments++) {

      // Choose a training example by generating inputs randomly
      cout << "Training example:";
      for(x = 0; x < num_inputs; x++) {    // Try a random input
         inputs[x] = rand() % 2;
         cout << " " << inputs[x];
      }
      cout << endl;

      result = ltu(inputs);  // Put training example into the network. Correct?

      // Now, adjust the weights
      if(result != function->execute(inputs)) {
         if(result == 0)
            for(x = 0; x < num_inputs; x++)
               weights[x] += inputs[x];
         else
            for(x = 0; x < num_inputs; x++)
               weights[x] -= inputs[x];
      }

      cout << "Adjusted weights:";
      for(x = 0; x < num_inputs; x++)     // Print out the weights
         cout << " " << weights[x];
      cout << endl;
   }

   delete [] inputs;

   if(adjustments < MAX_ADJUSTMENTS)
      cout << "Number of adjustments: " << adjustments << endl;
   else
      cout << "Could not learn function in "
           << MAX_ADJUSTMENTS << " adjustments." << endl;
}

// test the network against the function for all combinations of
//  inputs. For a 2-bit input function, this is no big deal, but of
//  course you couldn't do this for a 50-bit function. It would take too
//  long to generate all the inputs. So you'd probably just take a
//  random sample. This program doesn't do random sampling.
int Perceptron::success()
{
   for(int x = 0; x < num_inputs; x++)
      inputs[x] = 0;

   // This loop generates all combinations of inputs.
   // The logic threshold unit is tested for each input combination.
   x = 0;
   while(x >= 0) {
      if(ltu(inputs) != function->execute(inputs)) // test network
         return 0;
      for(x = num_inputs - 1; x >= 0; x--) {       // generate next input combo
         inputs[x] = !inputs[x];
         if(inputs[x] == 1)
            break;
      }
   }

   return 1;
}

// Here is a straight-through logic threshold unit with a fixed
// threshold of one for any length of input and weight vectors.
// Return the output given the current weights and current input
int Perceptron::ltu(int input[])
{
   int sum = 0;
   for(int x = 0; x < num_inputs; x++)
      sum += inputs[x] * weights[x];

   if(sum > 1)
      return 1;
   else
      return 0;
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

