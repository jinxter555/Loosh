#pragma once
#include "node.hh"

using namespace  std;
namespace Loosh 
{

class Environment : public Node {
  friend class Lisp;
private:
public:
  Environment();
  Environment(Node::Type t) ;
  enum class Type { Parent, Scope, Frame, Process, Program };


};
}