#include "node.hh"
#include <iostream>


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
            "Unsupported types for addition! " + _to_str(type_) + 
            " : " + _to_str(other.type_)});
      }
  }, value_, other.value_);
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

  }, value_, other.value_);
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

  }, value_, other.value_);
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
  }, value_, other.value_);
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

  }, value_, other.value_);
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

  }, value_, other.value_);
}

Node Node::operator==(const Node &other) const {

  /*
  switch(type_) {
  case Type::Shared: {
    cout << "shared type ==!";
    auto sptr = get<ptr_S>(value_);
    return *sptr == other;}
  case Type::Raw: {
    auto sptr = get<ptr_R>(value_);
    return *sptr == other;}
  case Type::Unique:  {
    auto &sptr = get<ptr_U>(value_);
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
      cerr << "this.type: " << Node::_to_str(type_) << ", other.type: " << Node::_to_str(other.type_) << "\n";
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for == op"});
    }

  }, value_, other.value_);
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

  }, value_, other.value_);
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

  }, value_, other.value_);
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

  }, value_, other.value_);
}


// bools 

Node Node::operator&&(const Node &other) const {
  if(type_!= Type::Bool || other.type_ != Type::Bool)
    return Node(Error{Error::Type::InvalidOperation, "not Bool type for && op"});
  bool r = get<bool>(value_) && get<bool>(other.value_);
  return Node(r, Type::Bool);
}

Node Node::operator||(const Node &other) const {
  if(type_!= Type::Bool || other.type_ != Type::Bool)
   return Node(Error{Error::Type::InvalidOperation, "not Bool type for || op"});
  bool r = get<bool>(value_) || get<bool>(other.value_);
  return Node(r, Type::Bool);
}
Node Node::operator!() const {
  if(type_!= Type::Bool )
   return Node(Error{Error::Type::InvalidOperation, "not Bool type for !(op)"});
  bool r = get<bool>(value_) ;
  return Node(!r, Type::Bool);
}