#pragma once
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "node.hh"


using namespace std;

enum class PromptSwitch {
  exit,
  begin,
  vasm,
  svlm,
};


class LangPrompt {

  std::string history_filename, prompt_string;
  std::vector<std::string> history;

public:
  virtual void accept_prompt(const std::string &) = 0;
  LangPrompt(const std::string&hf, const std::string&ps)
    : history_filename( hf), prompt_string( ps) {};
  virtual void parse(const std::string &line) = 0; // parse readline line
  virtual Node::OpStatus load(const std::string &filename) = 0; // load files from command line
  virtual void run_program(const std::string& line) = 0; // load files from command line

  void save_history();
  void load_history();
  void pop_last_exit_history(); // remove exit
  PromptSwitch ready(); // ready for user readline input
  string read(); // ready for user readline input

};