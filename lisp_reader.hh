#pragma once
#include  "node.hh"
#include "lang.hh"
#include "lisp.hh"
#include <map>

namespace Loosh 
{

struct Token {
  Node::Integer col_;
  Node::Integer line_;
  string m_value;
} ;




class LispExpr;

class LispReader  {
friend class LispExpr;
private:
  Node::Integer col_=1;
  Node::Integer line_=1;
  static const Node lisp_op_map;
  Lisp *lisp;   // lisp to atom hasher

  string extract_quoted_string(const string&input, size_t &i);
  string extract_single_quoted_string(const string&input, size_t &i);
  void to_newline(const string&input, size_t &i);

  //unordered_map<string, bool> closurable_user_defined={{"forloop", true}};
  unordered_map<string, bool> closurable_user_defined;
  vector<string>  end_list;
  //Token token_previous={};
public:
  LispReader();
  string tokenize_preprocess(const string& input);
  string tokenize_preprocess_multiline(const string& input) ;
  string tokenize_preprocess_multiline_parenthesis(const string& input) ;

  void convert_to_infix(string&); // convert string to infix

  list<Token> tokenize(const string& input);  // turn everything in to a stream of tokens
  vector<string> tokenize_pre(const string& input);  // turn everything in to a stream of tokens
  Node::OpStatus parse(list<Token>& tokens);  // turn everything in to stream of node
  Node::OpStatus parse_sequence(list<Token>& tokens);  // turn everything in to stream of node
  Lisp::Op str_to_op(const string&input);
  static string _to_str(const list<Token>& tokens);
  static bool is_complete_parenthesis(const string& input); // (...) internal contains all complete pairs of ()
  void reset();
  bool is_closurable(Lisp::Op op); // if this can be a block of {identifier end}
  bool is_closurable(const string&token_str) ;
  bool is_endable(const string&token_str) ;

  bool load_closurable(const string&file);
};
}