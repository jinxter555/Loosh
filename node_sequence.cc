#include "node.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"
#include "color_esc.hh"

using namespace std;
namespace Loosh 
{

//---------------------------------------------------------------------- 
Node::OpStatusRef Node::get_node(Integer index) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  MYLOGGER_MSG(trace_function, "index: " + to_string(index), SLOG_NODE_OP+30)

  //cout << "get_node value:  " << _to_str() << "\n";
  //cout << "get_node type: " << _to_str(type_) << "\n";
  switch(type_) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(value_);
    return rptr->get_node(index); }

  case Type::Unique:  {
    auto &uptr = get<ptr_U>(value_);
    return uptr->get_node(index); }
  case Type::Vector:  {
    auto &cc_vec = get<Vector>(value_);
    const Integer cc_vec_size =  static_cast<Integer>(cc_vec.size());
    if(index < 0 || index >= cc_vec_size ) return {false, Error::ref(Error::Type::IndexOutOfBounds)};
    return {true, *cc_vec[index]};}

  case Type::IMap: {
    IMap& imap = get<IMap>(value_);
    if (auto it = imap.find(index); it != imap.end())  return {true, *imap[index]};
    return {false,
      Error::ref(Error::Type::KeyNotFound,
        "IMap::Operator[] (key) " + to_string(index) +" not found: " + _to_str(type_)
    )};}

  default: {}
  }

  return {false,
    Error::ref( Error::Type::InvalidOperation,
      "Operator[] (index) can only be used on vector/IMap nodes. Current type: " + _to_str(type_)
  )};
}

//----------------------------------- push_front
Node::OpStatus Node::push_front(unique_ptr<Node> node_uptr) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(type_) {
  case Type::List: {
    List& cc_list = get<List>(value_);
    cc_list.push_front(move(node_uptr)); 
    
    break; }

  case Type::DeQue: {
    DeQue& cc_dq = get<DeQue>(value_);
    cc_dq.push_front(move(node_uptr));
    break; }
  case Type::Vector: {
    Vector& cc_vec= get<Vector>(value_);
    auto msg = "Warning!: Node::push_front() with vector object";
    cerr << msg << "\n";
    MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
    cc_vec.insert(cc_vec.begin(), move(node_uptr));
    break; }
  default: {
    auto msg =  clean_function_name() +  ": Cannot push_front() element to a non-Node::__Sequence__ node." 
      + "\nNode::type: " + _to_str(type_) + ", Node::value_ " +  _to_str() + "\n";
    spdlog::error(msg);
    MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }}

  return {true, Node::create(true)};
}

//----------------------------------- push_back
Node::OpStatus Node::push_back(unique_ptr<Node> node_uptr) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(type_) {
  case Type::List: {
    List& cc_list = get<List>(value_);
    cc_list.push_back(move(node_uptr)); 
    
    break; }

  case Type::DeQue: {
    DeQue& cc_dq = get<DeQue>(value_);
    cc_dq.push_back(move(node_uptr));
    break; }
  case Type::Vector: {
    Vector& cc_vec= get<Vector>(value_);
    cc_vec.push_back(move(node_uptr));
    break; }
  default: {
    auto msg =  clean_function_name() +  ": Cannot push_back() element to a non-Node::__Sequence__ node.";
    //cerr << msg <<  "\n" <<_to_str(type_) << ", Node::value_ " <<  _to_str() << "\n";
    spdlog::error(msg);
    MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }}

  return {true, Node::create(true)};
}

Node::OpStatus Node::pop_front() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(type_) {
  case Type::List: {
    List& cc_list = get<List>(value_);
    auto front = move(cc_list.front());
    cc_list.pop_front();
    return {true, move(front)}; 
  }

  case Type::DeQue: {
    DeQue& cc_dq = get<DeQue>(value_);
    auto front = move(cc_dq.front());
    cc_dq.pop_front();
    return {true, move(front)}; 
  }

  case Type::Vector: {
    Vector& cc_vec= get<Vector>(value_);
    auto front = move(cc_vec.front());
    auto msg = clean_function_name() + " with vector object";
    spdlog::warn(msg);
    MYLOGGER_MSG(trace_function, "Warning:" + msg, SLOG_FUNC_INFO);
    cc_vec.erase(cc_vec.begin());
    return {true, move(front)}; 
  }
  default: {
    auto msg =  clean_function_name() +  ": Cannot pop_front() element to a non-Node::__Sequence__ node.";
    //cerr << msg <<  "\n" <<_to_str(type_) << ", Node::value_ " <<  _to_str() << "\n";
    spdlog::error(msg);
    MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }}

  return {false, Node::create()};
}

Node::OpStatus Node::pop_back() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  switch(type_) {
  case Type::List: {
    List& cc_list = get<List>(value_);
    auto back = move(cc_list.back());
    cc_list.pop_back();
    return {true, move(back)}; 
  }

  case Type::DeQue: {
    DeQue& cc_dq = get<DeQue>(value_);
    auto back = move(cc_dq.back());
    cc_dq.pop_back();
    return {true, move(back)}; 
  }

  case Type::Vector: {
    Vector& cc_vec= get<Vector>(value_);
    auto back = move(cc_vec.back());
    auto msg = clean_function_name() + " with vector object";
    spdlog::warn(msg);
    MYLOGGER_MSG(trace_function, "Warning:" + msg, SLOG_FUNC_INFO);
    cc_vec.pop_back();
    return {true, move(back)}; 
  }
  default: {
    auto msg =  clean_function_name() +  ": Cannot push_back() element to a non-Node::__Sequence__ node.";
    //cerr << msg <<  "\n" <<_to_str(type_) << ", Node::value_ " <<  _to_str() << "\n";
    spdlog::error(msg);
    MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
    throw std::bad_typeid();
  }}
  return {false, Node::create()};

}


}