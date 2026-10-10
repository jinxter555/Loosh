#pragma once
#include <sstream>
#include <map>
#include <string>
#include <functional>

#include "prompt.hh"
#include "commandline.hh"
#include "environment.hh"
#include "lisp.hh"

#include "lisp_reader.hh"


//class LispExpr;


namespace Loosh 
{

class Interactive : public LangPrompt {
private:
  Program env;

  Lisp jli; // 
  static  Node *proc_shell;
public:
  Interactive(const std::string&hf, const std::string&ps);//  : LangPrompt(hf, ps) {};
  void accept_prompt(const std::string&l) override; // readyline prompt
  void parse(const std::string &line) override; // parse readline line
  void parse_prompt(const std::string &line); // parse readline line
  void interact(Commandline &cmdline) ; // parse readline line
  //Node::OpStatus load(const std::string &filename) override; // load files from command line
  Node::OpStatus load(const std::string &filename) ; // load files from command line
  void reload(const string &filename); // reload file

  Node::OpStatus build_program(); // create module structure 
  Node::OpStatus build_file_str(const string& input); // create module structure 
  void run_program(const std::string &l="") override;
  void run_program(int argc, char *argv[]) ;


  PromptSwitch ready(); // ready for user readline input
  string read(Node *process_ptr); // ready for user readline input, process_ptr for variable completion
  LispReader& get_reader(); // lisp lexer and parser




  // command completion
  map<string, function<void(const std::string&)>> command_functions;

  static vector<string> line_buff_keys;
  static vector<string> map_children_keys;

  static char **command_completion(const char *text, int start, int end);
  static void convert_buff_to_keys();
  static vector<string> lookup_last_string_for_map_keys();

  static char* command_generator(const char *text, int state);
  //static std::vector<std::string> get_ui_commands(const std::vector<std::string> &ptk={});                                                 
  static vector<string> get_ui_commands();
  static vector<string> get_map_var_children(const string&map_var);

  void print();

};

}