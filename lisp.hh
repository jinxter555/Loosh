#ifndef __LISP_HH__
#define __LISP_HH__

#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "lang.hh"
#include "node.hh"


using namespace  std;
namespace Loosh 
{


class Environment;
class LispReader;


 static const vector<string> cc_path_module; 


class Lisp : public Lang {
  friend class Node;
  friend class Environment;
  friend class Tree;
  friend class Interactive;

  //unique_ptr<LispReader> reader;
  LispReader& reader;

  Node* m_lisp;
  Node* m_ops;

public:
  using Op=Node::Op;
  using List = list<unique_ptr<Node>>;
  using Vector = vector<unique_ptr<Node>>;


//  Lisp(Environment& env);

  Lisp(Tree& t, LispReader& r);
  static string _to_str(Lisp::Op op);
  void set_op_str() ;
  Op str_to_op(const string &input) ; // convert lisp string op keyword string 


  //-- utilies to communicate with out side. aka interactive 
  Node::OpStatus run_program(int argc, char *argv[]) override; // create module structure 
  Node::OpStatus build_program() override; // create module structure 
  Node::OpStatus build_file_str(const string& input) override; // create module structure 

  // build lisp lang code structure 
  Node::OpStatus parse_build(Node& tokens) ;



    // 
  Node::OpStatus build_parsed_list(Node& node);
  Node::OpStatus build_parsed_vector(Node& node);
  Node::OpStatus build_parsed_deque(Node& node);
  // 
  Node::OpStatus build_parsed_list(List& cc_list);
  Node::OpStatus build_parsed_pipe(List& cc_list);
  Node::OpStatus build_parsed_vector(List& cc_list);
  Node::OpStatus build_parsed_deque(List& cc_list);
  Node::OpStatus build_parsed_map(List& cc_list); // ((k1 v1)(k2 v2)...)
  Node::OpStatus build_parsed_alias(List& cc_list); // ((k1 v1)(k2 v2)...)

  Node::OpStatus build_parsed_fun(List& cc_list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_macro(List& cc_list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_module(List& cc_list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_class(List& cc_list); // (fun_name (param_list)(code list))
  Node::OpStatus build_parsed_root(List& cc_list); // (fun_name (param_list)(code list))

  //
  Node::OpStatus build_parsed_def(List& cc_list);
  Node::OpStatus build_parsed_if(List& cc_list);

  //OpStatus attach_cc_fun(const string&name, const Node::Fun& f);// create module structure 
  //OpStatus attach_cc_fun(const string&name_mod, const string&name_fun, const Node::Fun& f);// create module structure 
  //OpStatus attach_cc_fun(const vector<string>&name, const Node::Fun& f);// 

  Node::OpStatusRef symbol_lookup(Node&process, const string&name ) ; // 
  Node::OpStatusRef symbol_lookup_frame(Node&process, Node&frame, const string&name ) ; // 

  // auto complete
  vector<string> get_local_vars(Node&process);


  
  //template <typename T>

  //OpStatus build_parsed_func(List& list) ;

  Node::OpStatus use_at_parse_build(List& cc_list);
  Node::OpStatus use_at_run(Node&process, const Vector &cc_vec, size_t start=0);





};



}

#endif