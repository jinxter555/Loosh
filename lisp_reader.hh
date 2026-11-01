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
  vector<unique_ptr<Token>> tokenize(const string& input);  // turn everything in to a stream of tokens

};


}