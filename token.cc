#include "node.hh"
#include "atom.hh"
#include <memory>

using namespace std;
namespace Loosh 
{
Token::Token() : Node(Node::Type::IMap) {}

unique_ptr<Token> Token::create(Type t, Value v, UnsignedInteger l, UnsignedInteger c ) { 
  auto token = make_unique<Token>();
  token->add(Loosh::Atom::type, Node::create(t));
  token->add(Loosh::Atom::value, Node::create(move(v)));
  token->add(Loosh::Atom::line, Node::create(l));
  token->add(Loosh::Atom::col, Node::create(c));
  return token;
}

Token::Type Token::type() {
  auto &imap = _get_imap_ref();
  return imap[Loosh::Atom::type]->_get_op();
}

};