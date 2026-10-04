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

class Node;
using UnsignedInteger = unsigned LOOSH_T_LONG;
using IMap = unordered_map<UnsignedInteger, unique_ptr<Node>>;


class Lang  {

  friend class Node;
private:
  Node* root;
protected:
  static std::hash<std::string> hasher;
  //static unordered_map<UnsignedInteger , string> Atoms;
  //static IMap Atoms;
  static  unique_ptr<Node> Atoms;
public:
  class Atom {
  public: 
    static  const UnsignedInteger fun, server, client, connect, accept, run, ok, error, read, write, read_text, write_text, 
      read_binary, write_binary, is_open, got_text, echo, initialize, finalize,
      match, extract, replace, full, part,
      icase, nosubs, optimize, collate, ecmas, basic, extended, awk, grep, egrep,
      scope, frame, process
    ;
  };

  Lang(Node *r) ;

  static  UnsignedInteger str_to_atom(const string& input);
  static string unqiue_name(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  static string atom_to_str(UnsignedInteger v);
  static string atom_to_str_imap(UnsignedInteger v);
};

}