#include "environment.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace  std;
namespace Loosh 
{


Environment::Environment()  : Node(Node::Type::MetaObject) {}

Environment::Environment(Node::Type t)  : Node(t) {}

Node::Atom Environment::_get_type(Node* env_ptr) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto &env_node = env_ptr->get_node();
  if(env_node.type_ != Node::Type::MetaObject) {
    string msg =  "Env: "  + env_ptr->_to_str() + "Not a Meta Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw system_error();
  }
  auto meta_node_type = env_node.obj_info_get(LOOSH_CC_OBJ_TYPE);
  cout << clean_function_name() +  ": env_node " <<  env_node << "\n\n";
  cout << clean_function_name() +  ": meta node_type .second " <<  meta_node_type.second->get_node() << "\n";
  return meta_node_type.second->get_node()._get_atom();

  //cout << clean_function_name() +  ": obj info status second " <<  obj_info_status.second->get_node(LOOSH_CC_OBJ_TYPE).second._to_str() << "\n";



}

Node::OpStatusRef  Environment::lookup(Map &table, const string& name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto &arg_ptr_u = table[LOOSH_ARG];
  auto &immute_ptr_u = table[LOOSH_IMMUTE];
  auto &var_ptr_u = table[LOOSH_VAR];

  cout << "lookup() var_ptr_u: " << var_ptr_u->_to_str() << "\n";


  { // argument lookup 
  auto rv_ref_status = arg_ptr_u->get_node(name);
  if(rv_ref_status.first) return rv_ref_status;
  }

  { // immutable lookup
  auto rv_ref_status = immute_ptr_u->get_node(name);
  if(rv_ref_status.first) return rv_ref_status;
  }

  { // variable lookup

  auto rv_ref_status = var_ptr_u->get_node(name);

  //cout << "var rv_ref_status:  " << rv_ref_status << "\n";
  if(rv_ref_status.first) return rv_ref_status;

  }

  string msg = "identifer: " + name +  " not found!";
  MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
  spdlog::error(clean_function_name() + ": " + msg);
  return {false, Error::ref(Error::Type::KeyNotFound )};

}
//Node::OpStatus Environment::var_add(Map& table_var, const string&name, Node::ptr_U ptr) { }

//----------------------------------------------------------------------  scope
//Scope::Scope(const Node& scope_node) : scope(scope_node._get_ptr_r()) {}
//Scope::Scope() : Environment(Type::Map) {}

Scope::Scope() : Scope(nullptr) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  //cout << clean_function_name() << ": _to_str(): " <<  _to_str() << "\n\n";
}

Scope::Scope(Node* parent) : Environment(Node::Type::MetaObject), parent_ptr_r(parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto ltable_ptr_u  = Node::create(Node::Type::Map);
  ltable_ptr_u->set({LOOSH_IMMUTE}, Node::create(Node::Type::Map), true);
  ltable_ptr_u->set({LOOSH_VAR}, Node::create(Node::Type::Map), true);
  ltable_ptr_u->set({LOOSH_ARG}, Node::create(Node::Type::Map), true);

  obj_data_add(LOOSH_TABLE, move(ltable_ptr_u));
  obj_data_add(LOOSH_PARENT, Node::create(parent));
  obj_info_add(LOOSH_CC_OBJ_TYPE, Node::create(Lang::Atom::scope, Node::Type::Atom) );

  scope_map_ptr_r = &_get_map_ref();

  auto table_status = obj_data_get(LOOSH_TABLE);
  table_ptr_r = &table_status.second->get_node();

  //cout  << clean_function_name() <<": table_ptr_r "  << table_ptr_r->_to_str() << "\n";

  if(table_ptr_r==nullptr) { 
    string msg =  "table_ptr_r is nullptr";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw system_error();
  }

}

// MetaPtr is a pointer to a meta object for initializing existing 
// MetaObject 
Scope::Scope(Node* node_ptr_r,  Node::Type nt) : Environment(nt) {

  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  // make sure when type is MetaPtr and node_ptr_r != nullptr
  // existing MetaPtr or MetaNode can't not be nullptr
  if(node_ptr_r==nullptr && nt == Node::Type::MetaPtr) {
    string msg =  "node_ptr is nullptr. You can't initialize an existent scope(MetaPtr) with nullptr";
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    throw system_error();
  }

  value_ = node_ptr_r;
  auto &meta_node = node_ptr_r->get_node();
  cout << "meta_node " << meta_node << "\n";
  if(meta_node.type_ != Node::Type::MetaObject)  {
    string msg =  "Not a meta_object!";
    cerr << clean_function_name()  << ":" << msg<< "\n";
    cout << "meta_node: "  <<  meta_node._to_str() << "\n";
    throw bad_typeid();
  }

  auto table_status = meta_node.obj_data_get(LOOSH_TABLE);
  table_ptr_r = &table_status.second->get_node();
  auto parent_status = meta_node.obj_data_get(LOOSH_PARENT);
  parent_ptr_r = parent_status.second->_get_ptr_r();

  cout << clean_function_name << ": _to_str() "  << _to_str() << "\n";




}


//Node::OpStatus Scope::move_ptr_u() { }

//
Node::ptr_U Scope::create(Node *parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto meta_scope = Node::create(Node::Type::MetaObject);
  //cout << clean_function_name() <<  ": 1meta_create() : *meta_scope: " << meta_scope->_to_str() << "\n";

  auto ltable_ptr_u  = Node::create(Node::Type::Map);
  ltable_ptr_u->set({LOOSH_IMMUTE}, Node::create(Node::Type::Map), true);
  ltable_ptr_u->set({LOOSH_VAR}, Node::create(Node::Type::Map), true);
  ltable_ptr_u->set({LOOSH_ARG}, Node::create(Node::Type::Map), true);

  meta_scope->obj_data_add(LOOSH_TABLE, move(ltable_ptr_u));
  meta_scope->obj_data_add(LOOSH_PARENT, Node::create(parent));
  meta_scope->obj_info_add(LOOSH_CC_OBJ_TYPE, Node::create(Lang::Atom::scope, Node::Type::Atom) );


  //cout << "meta_create() : *meta_scope: " << *meta_scope << "\n";
  //cout << clean_function_name() <<  ": 2meta_create() : *meta_scope: " << meta_scope->_to_str() << "\n";
  return meta_scope;


}
Scope& Scope::meta_map_obj(Node* meta_obj) { }

Node::OpStatusRef Scope::lookup(const string&name) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  AUTO_TRACE();
  return Environment::lookup(table_ptr_r->_get_map_ref(), name);
  /*
  try {
    auto table = table_ptr->_get_map_ref();
    auto it = table.find(name);
  } catch(bad_typeid) {

  }*/

}

/*
Node::OpStatus Scope::add(const string&name, Node::ptr_U val) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  MYLOGGER_MSG(trace_function, "val:" + val->_to_str(), SLOG_FUNC_INFO)
  if(table_ptr_r==nullptr) { 
    cerr << "table_ptr is nullptr";
    throw system_error();
  }
//  cout << "1 table_ptr_r: " << table_ptr_r->_to_str() << "\n";
  table_ptr_r->add(name, move(val));
//  cout << "2 table_ptr_r: " << table_ptr_r->_to_str() << "\n";
  //return table_ptr_r->get_node(name);
}
*/



//------------------------------ ptr 
void Scope::print() {
  //scope_map_ptr_r->print();
}
//------------------------------ ptr 

Node::OpStatus Scope::var_add(const string&name, Node::ptr_U val) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  MYLOGGER_MSG(trace_function, "val:" + val->_to_str(), SLOG_FUNC_INFO)
  AUTO_TRACE();

  if(table_ptr_r==nullptr) { 
    auto msg =  "table_ptr_r is nullptr";
    cerr << msg << "\n";
    spdlog::error(msg);
    throw system_error();
  }


  auto var_ref_status = (*table_ptr_r)[LOOSH_VAR];
  if(!var_ref_status.first) {
    auto msg = "var_ref error";
    cerr << msg << "\n";
    spdlog::error(msg);
    throw system_error();
  }

  var_ref_status.second.add(name,  move(val));
  return {true, Node::create(true)};



}

//---------------------------------------------------------------------- 
}