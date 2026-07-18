SHELL := /bin/bash
CC=g++ -g -std=c++23
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make
node_o := $(wildcard ../*.o)

objects = test_node_1.o 
#objects = (wildcard: *.cc)
headers  := (wildcard: *.hh)

all:  test_node_1.out  # test_tree_1.out test_map_1.out test_lisp_1.out  test_lisp_2.out  
#all:  test_del_1.out  test_interactive_1.out  test_lisp_4.out  test_lisp_3.out  test_node_1.out   test_tree_1.out test_map_1.out test_lisp_1.out  test_lisp_2.out  

main.out : main.o $(node_o)
	$(CC) $^ -o $@ -lreadline

test_interactive_1.out : test_interactive_1.o $(node_o)
	$(CC) $^ -o $@

test_map_1.out : test_map_1.o $(node_o)
	$(CC) $^ -o $@

test_node_1.out : test_node_1.o $(node_o)
	$(CC) $^ -o $@

test_del_1.out : test_del_1.o $(node_o)
	$(CC) $^ -o $@ -lreadline

test_tree_1.out : test_tree_1.o $(node_o)
	$(CC) $^ -o $@

test_lang_1.out : test_lang_1.o $(node_o)
	$(CC) $^ -o $@

test_lisp_1.out : test_lisp_1.o $(node_o)
	$(CC) $^ -o $@

test_lisp_2.out : test_lisp_2.o $(node_o)
	$(CC) $^ -o $@

test_lisp_3.out : test_lisp_3.o $(node_o)
	$(CC) $^ -o $@

test_lisp_4.out : test_lisp_4.o $(node_o)
	$(CC) $^ -o $@


clean:
	rm -f out *.o *.gch *.out
