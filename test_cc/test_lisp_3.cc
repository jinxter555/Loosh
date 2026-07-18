#include <iostream>
#include "../node.hh"
#include "../lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
  

int main() {
  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_lisp_3 main()", __func__, SLOG_FUNC_INFO);

  LispExpr lisp;
  //string input="(add 1 2 3 (add 5 3))"; //string input;
  //string input="(add 1 2 3 (add 5 3))"; //string input;
  //string input="(add 1 2 3 (def :mod 5 3))"; //string input;
  //string input="(def :module 5 3)"; //string input;
  //string input="(def :module Main (def :fun main(+ 5 3)))"; //string input;
  //string input="(def :module Main (def :fun main(+ 5 3)))"; //string input;
  //lisp.print(); cout << "\n";
  //string input="(add 1 2 3)"; //string input;
  //string input="(print (vector 1 2 3))"; //string input;
  //string input="(vector 1 2 3 (vector 5 6 7))"; //string input;
  //string input="(vector 1  (vector 2 3) )"; //string input;
  //string input="(vector 1  (vector 2))"; //string input;
  //string input="(vector 1  )"; //string input;
  //string input="(module my_mod1 (defun main (argc argv) description_main_func_what (line2 line3)))"; //string input;
  //string input="(add 1 2 3 )"; //string input;

string input="(module Main (defun main (argc argv) \"description main func what\" (print \"hello, world\")))"; //string input;

  //string input="(vector (argc argv))"; //string input;
 // string input="(argc argv)"; //string input;
  //cout << "input: ";
  //cin >> input;
  //auto tokens = reader.tokenize("(plus 1 2)");

  auto result_build  = lisp.build_program(input);
  lisp.print();
  cout << "\n";
  auto result_run  = lisp.run_program();
  //cout << "result: " <<  result <<"\n " ;

  //if(result.first) result.second->print();
  cout << "\n";




}
