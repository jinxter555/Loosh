SHELL := /bin/bash
CC=g++ -g -std=c++23 -Wall -I ~/.local/include/
# Define temporary directory
TMPDIR = /dev/shm
MAKE=make

#objects = node.o  node_str.o node_out.o node_clone.o scope_logger.o  my_helpers.o lang.o
objects =  node.o  node_str.o node_out.o node_clone.o scope_logger.o  \
	my_helpers.o  node_error.o  node_math.o \
	node_map.o node_sequence.o meta.o \
	trace_guard.o tree.o atom.o lang.o \
	lisp.o  lisp_keywords.o lisp_reader.o  lisp_lookups.o \
	lisp_build_util.o  lisp_eval_math.o \
  prompt.o  interactive.o  commandline.o\
	process_branch.o  frame.o scope.o environment.o  lex.yy.o token.o

# node_map.o node_sequence.o node_object.o  environment.o \


#objects = (wildcard: *.cc)
headers  := (wildcard: *.hh)

#all: test_cc_d $(objects) 
all: $(objects) lex.yy.cc  test_cc_d 


$(objects): %.o: %.cc 
	$(CC) -c $^ -o $@

test_cc_d:
	$(MAKE) -C test_cc 

lex.yy.cc: lexer_inline.l lexer_generic.l
	reflex lexer_inline.l

clean:
	rm -f out *.o *.gch *.out
	cd test_cc; make clean
