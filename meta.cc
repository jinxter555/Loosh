#include "node.hh"

//#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#include "node_tmpl_cc.hh"
#include "atom.hh"


using namespace std;
namespace Loosh {

Meta::Meta() : Meta::Node(create_vec()) {
  m_type=Node::Type::Meta;
  
}
Meta::Meta(Node::Type t)  : Node(t) {
  if(t==Node::Type::Meta ) {
    m_value = create_vec();
    return;
  }

}
Node::Vector Meta::create_vec() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  //MetaObject cc_vec(ObjectIndex::count);
  Vector cc_vec(Index::count);


  cc_vec[MetaObjectIndex::Parent] = nullptr;
  cc_vec[Index::Info] = Node::create(Node::Type::IMap);
  cc_vec[Index::AtomMap] = Node::create(Node::Type::IMap);
  cc_vec[Index::VectorArray] = Node::create(Node::Type::Vector);
  cc_vec[Index::StringMap] = Node::create(Node::Type::Map);
  cc_vec[Index::MetaLock] = Node::create(Node::Type::Lock);
  cc_vec[Index::cc_class] = Node::create(Node::Type::Atom);
  cc_vec[Index::WalkerCount] = Node::create(Node::Type::AtomicInteger);

  return cc_vec;
}

string Meta::_to_str() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  string result="";
  auto& cc_vec = get<Vector>(m_value);

  result  += "Map:" + cc_vec[Index::StringMap]->_to_str() + "\n";
  //result  += "Atom:" + cc_vec[Index::AtomMap]->get_node()._to_str() + "\n";
  result  += "Atom:" + cc_vec[Index::AtomMap]->_to_str() + "\n";
  //result  += "Vector: " + cc_vec[Index::VectorArray]->get_node()._to_str() + "\n";
  result  += "Vector: " + cc_vec[Index::VectorArray]->_to_str() + "\n";
  return result;
}

string Meta::_to_str(const Vector& cc_vec)  {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_TO_STR)
  string result;
  result  += "Map:" + cc_vec[Index::StringMap]->_to_str() + "\n";
  //result  += "Atom:" + cc_vec[Index::AtomMap]->get_node()._to_str() + "\n";
  result  += "Atom:" + cc_vec[Index::AtomMap]->_to_str() + "\n";
  //result  += "Vector: " + cc_vec[Index::VectorArray]->get_node()._to_str() + "\n";
  result  += "Vector: " + cc_vec[Index::VectorArray]->_to_str() + "\n";
  return result;

}

unique_ptr<Meta> Meta::create(ptr_R parent) {
  auto obj = make_unique<Meta>();
  obj->set_parent(parent);
  return obj;
}

//------------------------------------------------------------------------ 
bool Meta::set_parent(ptr_R parent) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  if(m_type != Type::Meta) {
    string msg = "Type: " + Node::_to_str(m_type) + " , Value:"  +  _to_str() + " is Not a Meta Object" ;
    cerr << clean_function_name() <<  ":" + msg << "\n";
    spdlog::error(msg);
    return false;
  }
  auto &obj = get<VecObject>(m_value);
  obj[Index::Parent] = create(parent);
  return true;
}


}