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
Token::Token() : Node(Node::Type::IMap) {}
//Token::Token() : Node(Node::Type::Token) {}

unique_ptr<Token> Token::create(Type t, Value v, UnsignedInteger l, UnsignedInteger c ) { 
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  auto token = make_unique<Token>();
  token->add(Loosh::Atom::type, Node::create(t));
  token->add(Loosh::Atom::value, Node::create(move(v)));
  token->add(Loosh::Atom::line, Node::create(l));
  token->add(Loosh::Atom::col, Node::create(c));
  return token;
}

Token::Type Token::type() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  auto &imap = _get_imap_ref();
  return imap[Loosh::Atom::type]->_get_op();
}

string Token::_to_str() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  //if(m_type != Node::Type::Token) return "Not Token";
  auto const &imap = get<IMap>(m_value);
  return _to_str(imap);

}
string Token::_to_str(const IMap& imap) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  cout << "imap Node::_to_str(imap) " << Node::_to_str(imap) << "\n";

  auto line =   imap.at(Loosh::Atom::line)->_to_str();
  auto col =   imap.at(Loosh::Atom::col)->_to_str();
  auto value =   imap.at(Loosh::Atom::value)->_to_str();
  auto type = Lisp::_to_str( imap.at(Loosh::Atom::type)->_get_op());
  auto result =  "Token{line: " + line + " " + "col: " + col  + ",  " +  type +  ": "  + value + "}";
  return result;
}

};