# Make file for linked list project.
# Note, uses templates.

OBJS = reverse.o
CC	= g++ #variable
#compiler arguments
CCFLAGS = -Wall -Wextra -pedantic -std=c++11 -g #variable
#string substitution
DEPS = linkedStack.h linkedQueue.h 

#target executable to be created
all: reverse	

reverse:  $(OBJS)
	$(CC) $(CCFLAGS) -o reverse $(OBJS)

reverse.o: reverse.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c reverse.cpp

# -----
# clean by removing object files.

clean:
	rm $(OBJS) 