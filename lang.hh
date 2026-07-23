#pragma once

#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <unordered_map>                                                                        
#include <functional>

#include "defs.hh"

using namespace std;
namespace Loosh 
{


using Integer = LOOSH_T_LONG; 

class Lang  {
  friend class Node;
protected:
  static const vector<std::string> atoms_key ; 
  static std::hash<std::string> hasher;
  static unordered_map<Integer , string> Atoms;
public:
  class Atom {
  public: 
    static  const Integer fun, server, client, connect, accept, run, ok, error, read, write, read_text, write_text, 
      read_binary, write_binary, is_open, got_text, echo, initialize, finalize,
      match, extract, replace, full, part,
      icase, nosubs, optimize, collate, ecmas, basic, extended, awk, grep, egrep
    ;
  };

  Lang();

  static  Integer str_to_atom(const string& input);
  static string unqiue_name(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  static string atom_to_str(Integer v);
  static string atom_to_str_imap(Integer v);
};

}