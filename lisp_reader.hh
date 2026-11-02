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
public:
  LispReader();
  list<unique_ptr<Token>> tokenize_lisp(const string& input);  // turn everything in to a stream of tokens
  Node::List tokenize_lsh(const string& input);  // turn everything in to a stream of tokens
  Node::ptr_U parse_lisp(list<unique_ptr<Token>>& tokens);  // turn everything in to a stream of tokens

};


}