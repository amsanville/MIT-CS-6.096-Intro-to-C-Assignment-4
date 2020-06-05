OBJS = mainA4.o myStack.o myGraph.o
CC = g++
CFLAGS = -Wall -g
#LIBS =
EXEC = output

output: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

mainA3.o: mainA4.cpp myStack.h myGraph.h
	g++ -c mainA4.cpp

myStack.o: myStack.cpp myStack.h
	g++ -c myStack.cpp

myGraph.o: myGraph.cpp myGraph.h
	g++ -c myGraph.cpp
	
clean: 
	rm -f $(EXEC) *.o

# target: dependencies
#	command(s)