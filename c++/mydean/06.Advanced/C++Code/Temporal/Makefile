# Copyright 1994, Brown University, Providence, RI
#
# See end of file for full copyright information
# This file is a makefile, a way of automating the installation process
# of this program. To use this makefile, change the CC and SUPPORT variables
# if needed, and type "make" at the command line.

# Choose the appropriate C++ compiler. Do not use g++, which won't work.
CC = g++

# The SUPPORT variable gives the location of all the include files for the
# container classes needed to compile this package.
SUPPORT = ../../../C++Support

######################################################################
#   Do NOT change anything after this line
######################################################################

# List of include directories to look for file included with #include<..>
# The -I. means the current directory.
INC = -I$(SUPPORT) -I.

# Flags to pass to the C++ compiler such as the "-g" debugging flag
CFLAGS = -g

# The object files that we want to compile to build the program.
OBJS = Effects.o CausalRuleDatabase.o Project.o Time.o \
	FactDatabase.o TemporalUpdate.o	

SUPPORT_OBJS = $(SUPPORT)/KRUtility.o $(SUPPORT)/XDString.o

# The source files should end in .C for C++, or .c for normal C.
# This line automatically generates them from the object files.
SRCS = $(OBJS:%.o=%.C)

# The name of the program I want to make
PROG = temporal

all : $(PROG)

# This rule tells how to compile C++ source files.
.C.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INC) -c $<

# The $(INC) here is for compling C++ code with templates.
$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(SUPPORT_OBJS) $(OBJS) $(INC)

clean :
	rm -f $(OBJS) $(PROG)

#
# Copyright 1994, Brown University, Providence, RI
#
# Permission to use and modify this software and its documentation for
# any purpose other than its incorporation into a commercial product is
# hereby granted without fee.  Permission to copy and distribute this
# software and its documentation only for non-commercial use is also
# granted without fee, provided, however, that the above copyright notice
# appear in all copies, that both that copyright notice and this permission
# notice appear in supporting documentation, that the name of Brown
# University not be used in advertising or publicity pertaining to
# distribution of the software without specific, written prior permission,
# and that the person doing the distribution notify Brown University of
# such distributions outside of his or her organization. Brown University
# makes no representations about the suitability of this software for
# any purpose.  It is provided "as is" without express or implied warranty.
# Brown University requests notification of any modifications to this
# software or its documentation.
#
# Send the following redistribution information:
#
#	Name:
#	Organization:
#	Address (postal and/or electronic):
#
# To:
#	Software Librarian
#	Computer Science Department, Box 1910
#	Brown University
#	Providence, RI 02912
#
#		or
#
#	brusd@cs.brown.edu
#
# We will acknowledge all electronic notifications.
