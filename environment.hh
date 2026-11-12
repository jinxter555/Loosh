#pragma once
#include "node.hh"

using namespace  std;
namespace Loosh 
{

class Environment : public  Meta{
  friend class Lisp;
private:
public:
  Environment();
  enum class Type { Parent, Scope, Frame, Process, Program };


};
}