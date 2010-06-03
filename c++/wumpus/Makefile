#
# This is a sample makefile for use with the Wumpus simulation.
#
# You do not need to modify this makefile when adding new source
# files.  It will update itself automatically.
#
# The "TARGET" variable is the name of the executable program
# that will be created.
#
TARGET		=	wumpsim

LIB_DIR		=	lib

CXX		=	g++
CXXFLAGS	=	-g -Wall $(DEFINES)
CPPFLAGS	=	-I$(LIB_DIR)
LDFLAGS		=	-L$(LIB_DIR) -lwumpus -lm

SRCS		:=	$(wildcard *.cc)
OBJS		=	$(SRCS:.cc=.o)

$(TARGET):		$(OBJS)
			$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
			rm -f *.o $(TARGET)

