#ifndef __NODE_TPP__
#define __NODE_TPP__
#pragma once

#include "trace_guard.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



// ============================================================================
// NON-CONST VERSION (Allows inline modifications)
// ============================================================================

namespace Loosh 
{

//------------------------------------------------------------------------
template <typename T> const T& Node::get_value() const {
  return  get<T>(m_value);
}

template <typename T> T& Node::get_value() {
  return const_cast<T&>(
    static_cast<const Node*>(this)->get_value<T>()
  );
}

//------------------------------------------------------------------------
template <typename T>
const T& Node::unwrap_value() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();

  // 1. Unified Delegation Loop: Keep tunneling down if this node is just a pointer link
  switch(m_type) {
    case Type::Raw: {
      auto ptr_r = get<ptr_R>(m_value);
      if (!ptr_r) throw runtime_error("Null raw pointer during unwrap");
      return ptr_r->template unwrap_value<T>(); // 'template' keyword required for nested templates
    }
    case Type::Unique: {
      const auto &ptr_u = get<ptr_U>(m_value);
      if (!ptr_u) throw std::runtime_error("Null unique pointer during unwrap");
      return ptr_u->template unwrap_value<T>();
    }
    default: 
      break; // Reached the true terminal leaf node in the chain
  }

  // 2. Base Fallback Case: Check the target type only once at the end
  if constexpr (is_same_v<T, Node>) {
    cout << "node::unwrap_value<Node>\n";
    return *this; 
  } else {
    auto tmpl_type = get_tmpl_type<T>();
//    string msg =  "template type: " +  Node::_to_str(tmpl_type)  + " != " + Node::_to_str(m_type);
//    cout << "node::unwrap_value<T>: "  << msg <<"\n";
    if( tmpl_type != m_type) {
      string msg =  "Runtime error: template type: " +  Node::_to_str(tmpl_type)  + " != " + Node::_to_str(m_type);
      throw runtime_error(clean_function_name() + ":" + msg );
    }
    return get<T>(m_value); 
  }
}




template <typename T> 
T& Node::unwrap_value() {
  return const_cast<T&>(
    static_cast<const Node*>(this)->unwrap_value<T>()
  );
}

template <typename T> Node::Type Node::get_tmpl_type() const  {
  if constexpr (is_same_v<T, monostate>) return Type::Null;
  else if constexpr (is_same_v<T, bool>) return Type::Bool;
  else if constexpr (is_same_v<T, Error>) return Type::Error;
  else if constexpr (is_same_v<T, Integer>) return Type::Integer;
  else if constexpr (is_same_v<T, Float>) return Type::Float;
  else if constexpr (is_same_v<T, string>) return Type::String;
  else if constexpr (is_same_v<T, List>) return Type::List;
  else if constexpr (is_same_v<T, MetaObject>) return Type::Vector;
  else if constexpr (is_same_v<T, Vector>) return Type::Vector;
  else if constexpr (is_same_v<T, DeQue>) return Type::DeQue;
  else if constexpr (is_same_v<T, Map>) return Type::Map;
  else if constexpr (is_same_v<T, SimpleObject>) return Type::Map;
  else if constexpr (is_same_v<T, IMap>) return Type::IMap;
  else if constexpr (is_same_v<T, ptr_R>) return Type::Raw;
  else if constexpr (is_same_v<T, ptr_U>) return Type::Unique;
  else if constexpr (is_same_v<T, Fun>) return Type::Fun;
}


}

#endif