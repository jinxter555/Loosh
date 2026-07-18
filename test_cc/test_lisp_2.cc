#include "../node.hh"
#include "../lisp_reader.hh"
#include "../lisp_expr.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
  

int main() {
  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_lisp_2 main()", __func__, SLOG_FUNC_INFO);

  LispExpr lispexpr;
  //string input="(add 1 2 3 hello :world (sub 5 3))"; //string input;
  //string input="(add 1 2 3 :hello (plus 5 3))"; //string input;
  //string input="(add 1 2 3 (mul  5 3))"; //string input;
  string input="(print (list 5 3))"; //string input;
  //cout << "input: ";
  //cin >> input;
  //auto tokens = reader.tokenize("(plus 1 2)");
  LispExpr lisp;
  LispReader& reader= lispexpr.get_reader();
  cout << "input:"  << "\n" << input <<"\n";
  auto tokens = reader.tokenize(input);
  for(auto token : tokens ){ 
    cout << "col: " << token.col_ ;
    cout << " line: " << token.line_ ;
    cout << " token: " << token.value_ << "\n";
  }

  cout << "\n";
  auto pts = reader.parse(tokens);
  if(pts.first) {
    cout << "parsed list: \n";
    Node::print_value_recursive(*pts.second, 0);

  }
  cout << "\n";


}