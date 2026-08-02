SHELL := /bin/bash
# Added -I/usr/local/include so headers are found
CC = g++ -g -std=c++23 -I/usr/local/include
CXX = g++

# Define temporary directory
TMPDIR = /dev/shm

# Added -I/usr/local/include for the implicit pattern rules
CXXFLAGS = -g -std=c++23 -I/usr/local/include -DSPDLOG_FMT_EXTERNAL -pthread

# THE FIX: Point to the compiled library directory in /usr/local
LDFLAGS  = -L/usr/local/lib
LDLIBS   = -lCatch2Main -lCatch2 -lfmt -lspdlog

MAKE=make
node_o := $(wildcard ../*.o)

#objects = test_node_1.o test_node_2.o 
#objects = (wildcard: *.cc)
headers  := (wildcard: *.hh)

all:  test_node_1.out test_node_2.out  

#main.out : main.o $(node_o)
#       $^ -o $@ -lreadline

# Added $(LDFLAGS) before objects, ensuring libraries link cleanly at the end
test_node_1.out : test_node_1.o $(node_o)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

test_node_2.out : test_node_2.o $(node_o)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.out : %.o $(node_o)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f out *.o *.gch *.out

