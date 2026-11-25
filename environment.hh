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


/*
  virtual OpStatus lookup(const string&name);
  virtual void  add(const string&name, ptr_U value);

  virtual Lookup_t set(Lookup_t idx, ptr_U value );
  virtual OpStatus lookup(Lookup_t idx);
*/

};

}