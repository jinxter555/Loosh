#include "node.hh"
#include <iostream>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace std;
namespace Loosh 
{



//------------------------------------------------------------------------
Node Node::operator+(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> && is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> && is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs + rhs));
      else
        return Node(static_cast<Float>(lhs) + static_cast<Float>(rhs));
      } else if constexpr (is_same_v<L, string> && is_same_v<R, string>) {
        return Node(lhs + rhs);
      } else {
        return Node(Error{Error::Type::InvalidOperation, 
            "Unsupported types for addition! " + _to_str(m_type) + 
            " : " + _to_str(other.m_type)});
      }
  }, m_value, other.m_value);
}


Node Node::operator-(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs - rhs));
      else
        return Node(static_cast<Float>(lhs) - static_cast<Float>(rhs));
    } else {
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for subtraction"});
    }

  }, m_value, other.m_value);
}

Node Node::operator*(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs * rhs));
      else
        return Node(static_cast<Float>(lhs) * static_cast<Float>(rhs));
    } else {
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for multiplication"});
    }

  }, m_value, other.m_value);
}


Node Node::operator/(const Node &other) const {

  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if(static_cast<Float>(rhs) == 0.0)
        return Node(Error{Error::Type::DivideByZero,
          "Divide by zero "});
      return Node(static_cast<Float>(lhs) / static_cast<Float>(rhs));
    } else {
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for Division"});
    }
  }, m_value, other.m_value);
}

//------------------------------------------------------------------------
Node Node::operator>(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs)  > static_cast<Integer>(rhs), Type::Bool);
      else
        return Node(static_cast<Float>(lhs) > static_cast<Float>(rhs), Type::Bool);
    } else {
      return Node::create(false);
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for > op"});
    }

  }, m_value, other.m_value);
}

Node Node::operator<(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs) < static_cast<Integer>(rhs), Type::Bool);
      else
        return Node(static_cast<Float>(lhs) < static_cast<Float>(rhs), Type::Bool);
    } else {
      return Node::create(false);
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for < op"});
    }

  }, m_value, other.m_value);
}

Node Node::operator==(const Node &other) const {

  /*
  switch(m_type) {
  case Type::Shared: {
    cout << "shared type ==!";
    auto sptr = get<ptr_S>(m_value);
    return *sptr == other;}
  case Type::Raw: {
    auto sptr = get<ptr_R>(m_value);
    return *sptr == other;}
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(m_value);
    return *sptr == other; }}
*/

  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs) == static_cast<Integer>(rhs), Type::Bool);
      else
        return Node(static_cast<Float>(lhs) == static_cast<Float>(rhs), Type::Bool);
    } else {
      if constexpr (is_same_v<L, string> &&  is_same_v<R, string>) {
        return Node(static_cast<string>(lhs) == static_cast<string>(rhs), Type::Bool);
      }

      return Node::create(false);

      cerr << "this: " << _to_str() << ", other: " << other._to_str() << "\n";
      cerr << "this.type: " << Node::_to_str(m_type) << ", other.type: " << Node::_to_str(other.m_type) << "\n";
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for == op"});
    }

  }, m_value, other.m_value);
}

Node Node::operator!=(const Node &other) const {
  return ! (*this == other);
  /*
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs) != static_cast<Integer>(rhs), Type::Bool);
      else
        return Node(static_cast<Float>(lhs) != static_cast<Float>(rhs), Type::Bool);
    } else {
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for != op"});
    }

  }, m_value, other.m_value);
*/
}






Node Node::operator<=(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs) <= static_cast<Integer>(rhs), Type::Bool);
      else
        return Node(static_cast<Float>(lhs) <= static_cast<Float>(rhs), Type::Bool);
    } else {
      return Node::create(false);
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for <= op"});
    }

  }, m_value, other.m_value);
}

Node Node::operator>=(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs) >= static_cast<Integer>(rhs), Type::Bool);
      else
        return Node(static_cast<Float>(lhs) >= static_cast<Float>(rhs), Type::Bool);
    } else {
      return Node::create(false);
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for >= op"});
    }

  }, m_value, other.m_value);
}


// bools 

Node Node::operator&&(const Node &other) const {
  if(m_type!= Type::Bool || other.m_type != Type::Bool)
    return Node(Error{Error::Type::InvalidOperation, "not Bool type for && op"});
  bool r = get<bool>(m_value) && get<bool>(other.m_value);
  return Node(r, Type::Bool);
}

Node Node::operator||(const Node &other) const {
  if(m_type!= Type::Bool || other.m_type != Type::Bool)
   return Node(Error{Error::Type::InvalidOperation, "not Bool type for || op"});
  bool r = get<bool>(m_value) || get<bool>(other.m_value);
  return Node(r, Type::Bool);
}
Node Node::operator!() const {
  if(m_type!= Type::Bool )
   return Node(Error{Error::Type::InvalidOperation, "not Bool type for !(op)"});
  bool r = get<bool>(m_value) ;
  return Node(!r, Type::Bool);
}
}