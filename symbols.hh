#pragma once
#include "node.hh"


using namespace  std;
namespace Loosh 
{



// symbols table
//class Symbols : public Meta {
class Symbols : public Meta {
public:
  Symbols() ;  

  static unique_ptr<Symbols> create();

  OpStatus add_or_lookup(const string&name);
  OpStatus lookup(const string&name);
  Lookup_t add(const string&name);

};

}