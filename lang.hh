#ifndef __LANG_HH__
#define __LANG_HH__
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
#include "node.hh"
#include "process.hh"


using namespace std;
class ProcessBranch;

namespace Loosh 
{

//class Node;
using UnsignedInteger = unsigned LOOSH_T_LONG;
using IMap = unordered_map<UnsignedInteger, unique_ptr<Node>>;


class Lang  {
  friend class Node;
private:
protected:
  static std::hash<std::string> hasher;
  Node* m_root;
  Node* m_atoms;
  Node* m_lang;
  ProcessBranch process_branch;
  //static unordered_map<UnsignedInteger , string> Atoms;
  //static IMap Atoms;
  //static  unique_ptr<Node> Atoms;
public:
  //using OpStatus = pair<bool, unique_ptr<Node>>;

  Lang(Node *r) ;
  void add_atoms(unique_ptr<Node>atoms);

  UnsignedInteger str_to_atom(const string& input);
  string unqiue_name(const string& input);
  //Node::OpStatusRef atom_to_str(Node::Integer v);
  string atom_to_str(UnsignedInteger v);
  string atom_to_str_imap(UnsignedInteger v);


  virtual Node::OpStatus run_program(int argc, char *argv[]) =0; // create module structure 
  virtual Node::OpStatus build_program() =0; // create module structure 
  virtual Node::OpStatus build_file_str(const string& input) =0; // create module structure 
};

}

#endif