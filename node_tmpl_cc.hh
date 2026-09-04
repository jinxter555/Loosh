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
      if (!ptr_r) throw std::runtime_error("Null raw pointer during unwrap");
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
    cout << "node::unwrap_value<Node>!\n";
    return *this; 
  } else {
    cout << "node::unwrap_value<T>!\n";
    return get<T>(m_value); 
  }
}




/*
template <typename T> 
const T& Node::unwrap_value() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  //cout << "node::unwrap_value<T>!\n";
  //cout << "type: " << Node::_to_str(m_type) <<  "\n";

  if constexpr (is_same_v<T, Node>) {
    cout << "node::unwrap_value<Node>!\n";
    switch(m_type) {
    case Type::Raw: {
      auto ptr_r = get<ptr_R>(m_value);
      return ptr_r->unwrap_value<Node>();
    }
    case Type::Unique: {
      auto &ptr_u = get<ptr_U>(m_value);
      return ptr_u->unwrap_value<Node>();
    }
    default: {}}
    return *this;

  } else {
    cout << "node::unwrap_value<T>!\n";


    switch(m_type) {
    case Type::Raw: {
      cout << "Raw!\n";
      auto ptr_r = get<ptr_R>(m_value);
      return ptr_r->unwrap_value<T>();
    }
    case Type::Unique: {
      cout << "Unique!\n";
      auto &ptr_u = get<ptr_U>(m_value);
      return ptr_u->unwrap_value<T>();
    }
    default: {
      cout << "type: " << Node::_to_str(m_type) <<  "\n";
    }}
  
    return get<T>(m_value);
  }

}


template <> const Node& Node::unwrap_value<Node>() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  AUTO_TRACE();
  cout << "node::unwrap_value<Node>!\n";
    switch(m_type) {
    case Type::Raw: {
      auto ptr_r = get<ptr_R>(m_value);
      return ptr_r->unwrap_value<Node>();
    }
    case Type::Unique: {
      auto &ptr_u = get<ptr_U>(m_value);
      return ptr_u->unwrap_value<Node>();
    }
    default: {}}
    return *this;
}
    */

template <typename T> 
T& Node::unwrap_value() {
  return const_cast<T&>(
    static_cast<const Node*>(this)->unwrap_value<T>()
  );
}

}

#endif