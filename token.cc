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
  auto const &cc_vec  = token->_get_vector_ref();


  token->set(static_cast<UnsignedInteger>(Token::Index::value ), move(v));
  token->set(static_cast<UnsignedInteger>(Token::Index::op),  Node::create(op)) ;
  token->set(static_cast<UnsignedInteger>(Token::Index::line), Node::create(l));
  token->set(static_cast<UnsignedInteger>(Token::Index::col), Node::create(c));

  token->op_ptr = cc_vec[ static_cast<UnsignedInteger>(Token::Index::op)].get();

  //auto &imap = token->_get_imap_ref();
  //cout <<clean_function_name() +  ", token->imap: size()" << imap.size() << "\n";
  return token;
}


Node::Op Token::_get_op() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  auto const &cc_vec  = get<Vector>(m_value);
  auto &op = cc_vec[static_cast<UnsignedInteger>(Token::Index::op)];
  return op->_get_op();

}
Node::ptr_R Token::value() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  auto const &cc_vec  = get<Vector>(m_value);
  auto &value = cc_vec[static_cast<UnsignedInteger>(Token::Index::value)];
  return value->value();
}

string Token::_to_str() const {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);
  if(m_type != Node::Type::Token) return "Not Token";
  auto const &cc_vec = get<Vector>(m_value);
  if(!cc_vec.size()) return "Token{}";
  //cout <<clean_function_name() +  ", imap: size()" << imap.size() << "\n";
  return Token::_to_str(cc_vec);

}
string Token::_to_str(const Vector& cc_vec) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_NODE_OP);

  auto line =   cc_vec[static_cast<UnsignedInteger>(Token::Index::line)]->_to_str();
  auto col  =   cc_vec[static_cast<UnsignedInteger>(Token::Index::col)]->_to_str();
  auto value  =   cc_vec[static_cast<UnsignedInteger>(Token::Index::value)]->_to_str();
  auto op  =   cc_vec[static_cast<UnsignedInteger>(Token::Index::op)]->_to_str();
  
  auto result =  "Token{line: " + line + " " + "col: " + col  + ",  op: " +  op +  ", value: "  + value + "}";
  return result;
}

};