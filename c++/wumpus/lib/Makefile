#
# The symbol DEFINES is used to supply defines for compiler options.
# The 2 compiler options currently available are:
#
# FULL_SYSTEM    - Allows access to the Percept's hint and image members.
# WUMPUS_MODE    - Specifies the movement mode for Wumpi (see WumpusEnvironment.cc)
#
# Example:  gmake DEFINES="-DFULL_SYSTEM -DWUMPUS_MODE=PICK"
#
DEFINES = -DFULL_SYSTEM -DWUMPUS_MODE=PICK

CXX		=	g++
CXXFLAGS	=	-g -Wall $(DEFINES)
LDFLAGS		=	

SRCS		:=	$(wildcard *.cc)
OBJS		=	$(SRCS:.cc=.o)
LIBOBJS		=	$(patsubst %,libwumpus.a(%),$(OBJS))
DEPS		=	$(SRCS:.cc=.d)

libwumpus.a:		$(OBJS)
			ar rv libwumpus.a $(OBJS)
			ranlib $@

clean:
			rm -f *.o *.a

