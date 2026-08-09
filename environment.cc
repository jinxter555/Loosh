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
Node::OpStatus Environment::var_add(Map& table_var, const string&name, Node::ptr_U ptr) {
  //auto &var_ptr_u = table[LOOSH_VAR];
  

}

//----------------------------------------------------------------------  scope
//Scope::Scope(const Node& scope_node) : scope(scope_node._get_ptr_r()) {}
//Scope::Scope() : Environment(Type::Map) {}

Scope::Scope() : Environment(Type::ObjectMeta) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  auto ltable_ptr_u  = create(Type::Map);
  ltable_ptr_u->set({LOOSH_IMMUTE}, create(Type::Map), true);
  ltable_ptr_u->set({LOOSH_VAR}, create(Type::Map), true);
  ltable_ptr_u->set({LOOSH_ARG}, create(Type::Map), true);

  obj_data_add(LOOSH_TABLE, move(ltable_ptr_u));
  obj_data_add(LOOSH_PARENT, nullptr);
  obj_info_add(LOOSH_CC_OBJ_TYPE, Node::create(Lang::Atom::scope, Type::Atom) );

  scope_map_ptr_r = &_get_map_ref();

  auto table_status = obj_data_get(LOOSH_TABLE);
  table_ptr_r = &table_status.second->get_node();

/*
  cout << "value_ " << _to_str() << "\n";
  cout << "talbe_ptr_r " << *table_ptr_r << "\n";
*/

  if(table_ptr_r==nullptr) { 
    string msg = "table_ptr is nullptr";
    MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    spdlog::error(clean_function_name() + ": " + msg);
    throw system_error();
  }


}

Scope::Scope(Node* parent) : Environment(Type::Map), parent_ptr_r(parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
}



/*
Node::ptr_U Scope::create(Node *parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  //auto  scope_ptr_u_new  = make_unique<Node>();
  obj_data_add("table", make_unique<Node>(Node::Type::Map));
 // scope_ptr_u_new->obj_data_add("parent", Node::create(parent));
  //return scope_ptr_u_new;
}
*/

Node::OpStatusRef Scope::lookup(const string&name) {
  return Environment::lookup(table_ptr_r->_get_map_ref(), name);
  AUTO_TRACE();
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
    spdlog::error("table_ptr is nullptr");
    throw system_error();
  }
  auto var_ref_status = (*table_ptr_r)[LOOSH_VAR];
  if(!var_ref_status.first) {
    spdlog::error("var_ref error");
    throw system_error();
  }

  var_ref_status.second.add(name,  move(val));
  return {true, Node::create(true)};



}

//---------------------------------------------------------------------- 
}