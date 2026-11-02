#include <iostream>
#include <cstring>
#include "lisp_reader.hh"
#include "lisp.hh"
#include "my_helpers.hh"
#include "lex.yy.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

namespace Loosh 
{

LispReader::LispReader() {};

list<unique_ptr<Token>> LispReader::tokenize_lisp(const string& input_str ) {
  list<unique_ptr<Token>> tokens;
  std::stringstream stream(input_str);
  Loosh::Reader::Inline::Lexer lexer(&stream);

  for(auto raw_token = lexer.lex(); raw_token->type() != Token::Type::done; raw_token = lexer.lex()) {
      cout << "raw token: " <<  raw_token->_to_str() << "\n";
      tokens.push_back(move(raw_token));
  }

  return tokens;

};

Node::ptr_U LispReader::parse_lisp(list<unique_ptr<Token>>& tokens) {
  for(auto &token : tokens ) {

  }

}


}