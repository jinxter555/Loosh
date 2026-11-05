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

//list<unique_ptr<Token>> LispReader::tokenize_lisp(const string& input_str ) {
Node::List LispReader::tokenize_lisp(const string& input_str ) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  //list<unique_ptr<Token>> tokens;
  Node::List tokens;
  std::stringstream stream(input_str);
  Loosh::Reader::Inline::Lexer lexer(&stream);

  for(auto raw_token = lexer.lex(); raw_token->_get_op() != Token::Op::done; raw_token = lexer.lex()) {
      //cout << "raw token: " <<  raw_token->_to_str() << "\n";
      tokens.push_back(move(raw_token));
  }

  return tokens;

};
//Node::ptr_U LispReader::parse_lisp(list<unique_ptr<Token>>& tokens) {
Node::ptr_U LispReader::parse_lisp(Node::List& tokens) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  bool has_Lparen = false;
  auto code = Node::create(Node::Type::Vector);

  if(tokens.front()->_get_op() == Token::Op::Lparen) {
    tokens.pop_front();
    has_Lparen = true;
  }


  while(! tokens.empty() ) {
    auto &tok = tokens.front();
    if(tok->_get_op() == Token::Op::Lparen) {
      code->push_back( parse_lisp(tokens));
      continue;
    }
    if(tok->_get_op() == Token::Op::Rparen) {
      if(!has_Lparen) {
        auto msg =  "missing '(' ";
        cerr << msg << endl;
        return nullptr;
      }
      tokens.pop_front();
      return code;

    }
    code->push_back(move(tok));
    tokens.pop_front();
  }
  if(has_Lparen){
    auto msg =  "missing ')' ";
    spdlog::error(clean_function_name() + ": " +  msg);
    //MYLOGGER_MSG(trace_function, "Error: " + msg, SLOG_FUNC_INFO);
    cerr << msg << endl;
    return nullptr;
  }
  return code;

}






}