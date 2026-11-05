#include "node.hh"
#include "atom.hh"
#include "lisp.hh"
#include <memory>

#include "trace_guard.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


using namespace std;
namespace Loosh 
{
//Token::Token() : Node(Node::Type::IMap) {}
Token::Token() : Node(Node::Type::Token) {}

unique_ptr<Token> Token::create(Op op, Value v, UnsignedInteger l, UnsignedInteger c ) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  return create(op, Node::create(move(v)), l, c);
  
  /*
  auto token = make_unique<Token>();
  token->add(Loosh::Atom::value, Node::create(move(v)));
  token->add(Loosh::Atom::line, Node::create(l));
  token->add(Loosh::Atom::col, Node::create(c));
  return token;
  */
}
unique_ptr<Token> Token::create(Op op, ptr_U v, UnsignedInteger l, UnsignedInteger c ) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  auto token = make_unique<Token>();
  token->add(Loosh::Atom::op, Node::create(op));
  token->add(Loosh::Atom::value, move(v));
  token->add(Loosh::Atom::line, Node::create(l));
  token->add(Loosh::Atom::col, Node::create(c));

  //auto &imap = token->_get_imap_ref();
  //cout <<clean_function_name() +  ", token->imap: size()" << imap.size() << "\n";
  return token;
}


Node::Op Token::_get_op() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  //auto &imap = _get_imap_ref();
  auto const &imap = get<IMap>(m_value);
  if(!imap.size()) return Token::Op::error;
  return imap.at(Loosh::Atom::op)->_get_op();
}
Node::ptr_R Token::value() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  auto &imap = _get_imap_ref();
  if(!imap.size()) { 
    cerr <<clean_function_name() +  ", imap: size()" << imap.size() << "returns nullptr\n";
    return nullptr;
  }
  return imap[Loosh::Atom::value].get();
}

string Token::_to_str() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(m_type != Node::Type::Token) return "Not Token";
  auto const &imap = get<IMap>(m_value);
  if(!imap.size()) return "Token{}";
  //cout <<clean_function_name() +  ", imap: size()" << imap.size() << "\n";
  return _to_str(imap);

}
string Token::_to_str(const IMap& imap) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  auto line =   imap.at(Loosh::Atom::line)->_to_str();
  auto col =   imap.at(Loosh::Atom::col)->_to_str();
  auto value =   imap.at(Loosh::Atom::value)->_to_str();
  auto type = Lisp::_to_str( imap.at(Loosh::Atom::op)->_get_op());
  auto result =  "Token{line: " + line + " " + "col: " + col  + ",  " +  type +  ": "  + value + "}";
  return result;
}

};