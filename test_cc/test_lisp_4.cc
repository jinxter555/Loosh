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

  string input="(root :set (universe line2 line3) \"jack ass\")"; //string input;


  auto result  = lisp.build_program(input);
  //cout << "result: " <<  result <<"\n " ;

  //if(result.first) result.second->print();
  cout << "\n";

  lisp.print();



}