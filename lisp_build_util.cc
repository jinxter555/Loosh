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

  auto token_list = reader.tokenize( reader.tokenize_preprocess( input)); // list<Token> raw text tokens

  Node::OpStatus op_status;


  /*
  do{
    auto tokens_interpreted  = reader.parse(token_list);  
    //if(token_list.size() != 0) cout << "error parsing left over tokens! [" << token_list<< "]\n";
  
//    cout << "reader.endlist: " << _to_str_ext(reader.end_list) << "\n";

    if(!tokens_interpreted.first) {
      cout << "missing reader.endlist: " << _to_str_ext(reader.end_list) << "\n";
      cerr << "building_program: Reader.tokenize() and Reader.parser(): parse error for input string:\n" << input  << "\n\n";
      cerr << "error: " <<  *tokens_interpreted .second << "\n";
      return  tokens_interpreted ;
    }
  
    auto mod_code_status =  parse_build(*tokens_interpreted.second); 
  
    if(!mod_code_status.first) {
      cerr << "parse build interpreter error!" <<  mod_code_status.second->_to_str() <<"\n";
      return mod_code_status;
    }

    if(type_of(*mod_code_status.second) == Lisp::Op::module_)  {

      op_status = attach_module(move(mod_code_status.second));
     //cout << "it is a module!\n";
    }
    //  op_status = attach_module(move(mod_code_status.second));

  } while(token_list.size()!=0) ;

  build_namespace.clear();
  build_namespace.push_back(build_namespace_default);

  return op_status;
  */
}


Node::OpStatus Lisp::run_program(int argc, char *argv[]) {
  MYLOGGER(trace_function, clean_function_name(), clean_function_name(), SLOG_FUNC_INFO)

  auto kernel =  process_branch.create_kernel();
  

  while(true) {
    auto input_str = interface->read(kernel);
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