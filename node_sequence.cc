#include "node.hh"
#include "my_helpers.hh"

#include "atom.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"
#include "color_esc.hh"

using namespace std;
namespace Loosh 
{

//---------------------------------------------------------------------- 
Node::OpStatusRef Node::get_node(UnsignedInteger index) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP)
  MYLOGGER_MSG(trace_function, "index: " + to_string(index), SLOG_NODE_OP+30)

  //cout << "get_node value:  " << _to_str() << "\n";
  //cout << "get_node type: " << _to_str(m_type) << "\n";
  switch(m_type) {
  case Type::Raw: {
    auto rptr = get<ptr_R>(m_value);
    return rptr->get_node(index); }

  case Type::Unique:  {
    auto &uptr = get<ptr_U>(m_value);
    return uptr->get_node(index); }
  case Type::Vector:  {
    auto &cc_vec = get<Vector>(m_value);
    UnsignedInteger cc_vec_size =  static_cast<UnsignedInteger>(cc_vec.size());
    if(index < 0 || index >= cc_vec_size ) return {false, Error::ref(Error::Type::IndexOutOfBounds)};
    return {true, *cc_vec[index]};}

  case Type::IMap: {
    IMap& imap = get<IMap>(m_value);
    if (auto it = imap.find(index); it != imap.end())  return {true, *imap[index]};
    //cout << "\n\n" + clean_function_name() + "  Imap: " << _to_str() << "\n\n";
    return {false,
      Error::ref(Error::Type::KeyNotFound,
        clean_function_name() + " (key) " + Loosh::Atom::atom_to_str_imap(index) +" not found: " + _to_str(m_type)
    )};}

  default: {}
  }

  return {false,
    Error::ref( Error::Type::InvalidOperation,
      "Operator[] (index) can only be used on vector/IMap nodes. Current type: " + _to_str(m_type)
  )};
}

Node::OpStatus Node::push_front(unique_ptr<Node> value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return visit([&](auto&& arg) -> OpStatus {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, Vector>){
      //cout << clean_function_name()  + ":" <<  value->_to_str() << "\n";
      auto msg = "Warning!: Node::push_front() with vector object";
      MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
      cerr << msg << "\n";
      arg.insert(arg.begin(), move(value));
      return {true, create(true)}; 

    } else if constexpr (is_same_v<T, List>){
      arg.push_front(move(value));
      return {true, create(true)}; 

    } else if constexpr (is_same_v<T, DeQue>){
      arg.push_front(move(value));
      return {true, create(true)}; 

    } else {
      string msg =  "Cannot push_front() element to a non-Node::__Sequence__ node Node::type: " + _to_str(m_type) + ", Node::value: " +  _to_str() ;
      spdlog::error(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
      cerr << clean_function_name() + ": " + msg << "\n";
      throw std::bad_typeid();

    }
  }, m_value);
}



//----------------------------------- push_back
Node::OpStatus Node::push_back(unique_ptr<Node> value) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return visit([&](auto&& arg) -> OpStatus {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, Vector>){
      //cout << clean_function_name()  + ":" <<  value->_to_str() << "\n";
      arg.push_back(move(value));
      return {true, create(true)}; 

    } else if constexpr (is_same_v<T, List>){
      arg.push_back(move(value));
      return {true, create(true)}; 

    } else if constexpr (is_same_v<T, DeQue>){
      arg.push_back(move(value));
      return {true, create(true)}; 

    } else {
      string msg =  "Cannot push_back() element to a non-Node::__Sequence__ node Node::type: " + _to_str(m_type) + ", Node::value: " +  _to_str() ;
      spdlog::error(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
      cerr << clean_function_name() + ": " + msg << "\n";
      throw std::bad_typeid();

    }
  }, m_value);
}



//----------------------------------- back

Node::OpStatusRef Node::back() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  return visit([&](auto&& arg) -> OpStatusRef {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, Vector>){
      //cout << clean_function_name()  + ":" <<  value->_to_str() << "\n";
      return {true, *arg.back()};

    } else if constexpr (is_same_v<T, List>){
      return {true, *arg.back()};

    } else if constexpr (is_same_v<T, DeQue>){
      return {true, *arg.back()};

    } else {
      string msg =  "Cannot get back() element to a non-Node::__Sequence__ node Node::type: " + _to_str(m_type) + ", Node::value: " +  _to_str() ;
      spdlog::error(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
      cerr << clean_function_name() + ": " + msg << "\n";
      throw std::bad_typeid();

    }
  }, m_value);
}

Node::OpStatusRef Node::front() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  return visit([&](auto&& arg) -> OpStatusRef {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, Vector>){
      //cout << clean_function_name()  + ":" <<  value->_to_str() << "\n";
      return {true, *arg.front()};

    } else if constexpr (is_same_v<T, List>){
      return {true, *arg.front()};

    } else if constexpr (is_same_v<T, DeQue>){
      return {true, *arg.front()};

    } else {
      string msg =  "Cannot get front() element to a non-Node::__Sequence__ node Node::type: " + _to_str(m_type) + ", Node::value: " +  _to_str() ;
      spdlog::error(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
      cerr << clean_function_name() + ": " + msg << "\n";
      throw std::bad_typeid();

    }
  }, m_value);
}


Node::OpStatus Node::pop_back() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return visit([&](auto&& arg) -> OpStatus {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, Vector>){
      //cout << clean_function_name()  + ":" <<  value->_to_str() << "\n";
      auto back = move(arg.back());
      arg.pop_back();
      return {true, move(back)}; 

    } else if constexpr (is_same_v<T, List>){
      auto back = move(arg.back());
      arg.pop_back();
      return {true, move(back)}; 

    } else if constexpr (is_same_v<T, DeQue>){
      auto back  = move(arg.back());
      arg.pop_back();
      return {true, move(back)}; 

    } else {
      string msg =  "Cannot pop_back() element to a non-Node::__Sequence__ node Node::type: " + _to_str(m_type) + ", Node::value: " +  _to_str() ;
      spdlog::error(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
      cerr << clean_function_name() + ": " + msg << "\n";
      throw std::bad_typeid();
    }
  }, m_value);
}

Node::OpStatus Node::pop_front() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return visit([&](auto&& arg) -> OpStatus {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, Vector>){
      //cout << clean_function_name()  + ":" <<  value->_to_str() << "\n";
      auto msg = "Warning!: Node::pop_front() with vector object";
      MYLOGGER_MSG(trace_function, msg, SLOG_FUNC_INFO);
      spdlog::error(clean_function_name() + ": " + msg);
      cerr << msg << "\n";
      auto front = move(arg.front());
       arg.erase(arg.begin());
      return {true, move(front)}; 

    } else if constexpr (is_same_v<T, List>){
      auto front = move(arg.front());
      arg.pop_front();
      return {true, move(front)}; 

    } else if constexpr (is_same_v<T, DeQue>){
      auto front = move(arg.front());
      arg.pop_front();
      return {true, move(front)}; 

    } else {
      string msg =  "Cannot pop_front() element to a non-Node::__Sequence__ node Node::type: " + _to_str(m_type) + ", Node::value: " +  _to_str() ;
      spdlog::error(clean_function_name() + ": " + msg);
      MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
      cerr << clean_function_name() + ": " + msg << "\n";
      throw std::bad_typeid();

    }
  }, m_value);
}







}