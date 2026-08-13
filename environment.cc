#include "environment.hh"

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace  std;
namespace Loosh 
{


Environment::Environment(Node::Type t)  : Node(t) {}

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

Scope::Scope(Node* parent) : Environment(Type::MetaObject), parent_ptr_r(parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto ltable_ptr_u  = Node::create(Type::Map);
  ltable_ptr_u->set({LOOSH_IMMUTE}, Node::create(Type::Map), true);
  ltable_ptr_u->set({LOOSH_VAR}, Node::create(Type::Map), true);
  ltable_ptr_u->set({LOOSH_ARG}, Node::create(Type::Map), true);

  obj_data_add(LOOSH_TABLE, move(ltable_ptr_u));
  obj_data_add(LOOSH_PARENT, create(parent));
  obj_info_add(LOOSH_CC_OBJ_TYPE, Node::create(Lang::Atom::scope, Type::Atom) );

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
Scope::Scope(Node* meta_ptr, bool use_meta) : Environment(Type::MetaPtr), parent_ptr_r(nullptr) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  if(use_meta) moved = true; 
  value_ = meta_ptr;
  auto &m = meta_ptr->get_node();
  if(m.type_ != Type::MetaObject)  {
    string msg =  "Not a meta_object!";
    cerr << clean_function_name()  << ":" << msg<< "\n";
    cout << "m: "  <<  m._to_str() << "\n";
    throw bad_typeid();
  }

  auto table_status = m.obj_data_get(LOOSH_TABLE);
  table_ptr_r = &table_status.second->get_node();
  auto parent_status = m.obj_data_get(LOOSH_PARENT);
  parent_ptr_r = parent_status.second->_get_ptr_r();

  cout << clean_function_name << ": _to_str() "  << _to_str() << "\n";




}


//Node::OpStatus Scope::move_ptr_u() { }

//
Node::ptr_U Scope::meta_create(Node *parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  auto meta_scope = Node::create(Type::MetaObject);
  cout << clean_function_name <<  ": 1meta_create() : *meta_scope: " << meta_scope->_to_str() << "\n";

  auto ltable_ptr_u  = Node::create(Type::Map);
  ltable_ptr_u->set({LOOSH_IMMUTE}, Node::create(Type::Map), true);
  ltable_ptr_u->set({LOOSH_VAR}, Node::create(Type::Map), true);
  ltable_ptr_u->set({LOOSH_ARG}, Node::create(Type::Map), true);

  meta_scope->obj_data_add(LOOSH_TABLE, move(ltable_ptr_u));
  meta_scope->obj_data_add(LOOSH_PARENT, create(parent));
  meta_scope->obj_info_add(LOOSH_CC_OBJ_TYPE, Node::create(Lang::Atom::scope, Type::Atom) );


  //cout << "meta_create() : *meta_scope: " << *meta_scope << "\n";
  cout << clean_function_name <<  ": 2meta_create() : *meta_scope: " << meta_scope->_to_str() << "\n";
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