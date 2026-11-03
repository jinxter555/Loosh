#include "node.hh"
#include "lisp.hh"
#include "lisp_reader.hh"
#include "my_helpers.hh"
#include "interactive.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace  std;
namespace Loosh 
{

//------------------------------------------------------------------------
Node::OpStatus Lisp::build_file_str(const string& input) { 
  MYLOGGER(trace_function, "LispExpr::build_program(const string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  //auto token_list = reader.tokenize( reader.tokenize_preprocess( input)); // list<Token> raw text tokens

  Node::OpStatus op_status;


}


Node::OpStatus Lisp::run_program(int argc, char *argv[]) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)

  auto kernel =  process_branch.create_kernel();

  interface->load_history();
  
  

  while(true) {
    auto input_str = interface->read(kernel);
    if(input_str=="exit") break;
    auto tokens  = reader.tokenize_lisp(input_str);
    cout << "token size before parse: " << tokens.size() << "\n";
    auto tree = reader.parse_lisp(tokens);
    if(tree==nullptr) {
      cout << "tree is nullptr error";
      continue;
    }
    cout << "token size after parse: " << tokens.size() << "\n";
    cout << "tree: " <<  tree->_to_str() << "\n\n";

    /*
    std::stringstream stream(input_str);
    Loosh::Reader::Inline::Lexer lexer(&stream);
        
    for(auto raw_token = lexer.lex(); raw_token->type() != Token::Type::done; raw_token = lexer.lex()) {
      cout << "raw token: " <<  raw_token->_to_str() << "\n";
    }
    */



    cout << input_str <<endl;
  }
  
  cout << "run program!\n";
  return {true, Node::create()};
}
Node::OpStatus Lisp::build_program() {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)
  return {true, Node::create()};
}

}