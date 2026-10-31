#pragma once
#include  "node.hh"
#include "lisp.hh"
#include <map>

namespace Loosh 
{

struct MyToken {
  Node::Integer m_col;
  Node::Integer m_line;
  string m_value;
} ;




class LispReader  {
friend class Lisp;
private:
  Node::Integer m_col=1;
  Node::Integer m_line=1;
  static const Node lisp_op_map;
  Lisp *lisp;   // lisp to atom hasher

  string extract_quoted_string(const string&input, size_t &i);
  string extract_single_quoted_string(const string&input, size_t &i);
  void to_newline(const string&input, size_t &i);

  //unordered_map<string, bool> closurable_user_defined={{"forloop", true}};
  unordered_map<string, bool> closurable_user_defined;
  vector<string>  end_list;
  //MyToken token_previous={};
public:
  LispReader();
  string tokenize_preprocess(const string& input);
  string tokenize_preprocess_multiline(const string& input) ;
  string tokenize_preprocess_multim_lineparenthesis(const string& input) ;

  void convert_to_infix(string&); // convert string to infix

  list<MyToken> tokenize(const string& input);  // turn everything in to a stream of tokens
  vector<string> tokenize_pre(const string& input);  // turn everything in to a stream of tokens
  Node::OpStatus parse(list<MyToken>& tokens);  // turn everything in to stream of node
  Node::OpStatus parse_sequence(list<MyToken>& tokens);  // turn everything in to stream of node
  Lisp::Op str_to_op(const string&input);
  static string _to_str(const list<MyToken>& tokens);
  static bool is_complete_parenthesis(const string& input); // (...) internal contains all complete pairs of ()
  void reset();
  bool is_closurable(Lisp::Op op); // if this can be a block of {identifier end}
  bool is_closurable(const string&token_str) ;
  bool is_endable(const string&token_str) ;

  bool load_closurable(const string&file);
};
}