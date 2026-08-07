#include "environment.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace  std;
namespace Loosh 
{
Environment::Environment(Node::Type t)  : Node(t) {}

//----------------------------------------------------------------------  scope
//Scope::Scope(const Node& scope_node) : scope(scope_node._get_ptr_r()) {}
//Scope::Scope() : Environment(Type::Map) {}

Scope::Scope() : Environment(Type::ObjectMeta) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  obj_data_add("table", Node::create(Type::Map) );
  obj_data_add("parent", nullptr);
  obj_info_add("cc_obj_type", Node::create(Lang::Atom::scope, Type::Atom) );

  scope_map_ptr_r = &_get_map_ref();

  auto table_status = obj_data_get("table");
  table_ptr_r = &table_status.second->get_node();

/*
  cout << "value_ " << _to_str() << "\n";
  cout << "talbe_ptr_r " << *table_ptr_r << "\n";
*/

  if(table_ptr_r==nullptr) { 
    cerr << "Scope::Scope(), table_ptr is nullptr";
    throw system_error();
  }


}

Scope::Scope(Node* parent) : Environment(Type::Map), parent_ptr_r(parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
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
  /*
  try {
    auto table = table_ptr->_get_map_ref();
    auto it = table.find(name);
  } catch(bad_typeid) {

  }*/
 return {false, node_null};

}

Node::OpStatusRef Scope::add(const string&name, Node::ptr_U val) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  MYLOGGER_MSG(trace_function, "val:" + val->_to_str(), SLOG_FUNC_INFO)
  if(table_ptr_r==nullptr) { 
    cerr << "table_ptr is nullptr";
    throw system_error();
  }
//  cout << "1 table_ptr_r: " << table_ptr_r->_to_str() << "\n";
  table_ptr_r->add(name, move(val));
//  cout << "2 table_ptr_r: " << table_ptr_r->_to_str() << "\n";
  return table_ptr_r->get_node(name);
}
//------------------------------ ptr 
void Scope::print() {
  //scope_map_ptr_r->print();
}


//---------------------------------------------------------------------- 
}