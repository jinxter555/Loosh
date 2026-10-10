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
protected:
  static std::hash<std::string> hasher;
  Node* m_root;
  Node* m_atoms;
  //static unordered_map<UnsignedInteger , string> Atoms;
  //static IMap Atoms;
  //static  unique_ptr<Node> Atoms;
public:

  Lang(Node *r) ;
  void add_atoms(unique_ptr<Node>atoms);

  UnsignedInteger str_to_atom(const string& input);
  string unqiue_name(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  string atom_to_str(UnsignedInteger v);
  string atom_to_str_imap(UnsignedInteger v);
};

}