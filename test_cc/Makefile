SHELL := /bin/bash
CC = g++ -g -std=c++23
CXX = g++
# Define temporary directory
TMPDIR = /dev/shm
CXXFLAGS = -g -std=c++23
LDFLAGS  = 
LDLIBS   = -lCatch2Main -lCatch2

MAKE=make
node_o := $(wildcard ../*.o)

objects = test_node_1.o 
#objects = (wildcard: *.cc)
headers  := (wildcard: *.hh)

all:  test_node_1.out  test_node_2.out  

#main.out : main.o $(node_o)
#	$^ -o $@ -lreadline

#test_node_1.out : test_node_1.o $(node_o)
#	$(CC) $^ -o $@


#test_node_2.out : test_node_2.o $(node_o)
#	$(CC) $^ -o $@  $(LDLIBS)


%.out : %.o $(node_o)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f out *.o *.gch *.out
