#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <readline/readline.h>


#include "../commandline.hh"
#include "../interactive.hh"



#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"
#include "../error.hh"

#include "../io_file.hh"


// init some static vars 
void init() {
  File::init();
  Error::init();

}


Interactive *it_ptr;

int main(int argc, char *argv[]) {



  trace_function.open("trace.log", std::ios::out);
ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+30);
// ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
//  MYLOGGER(trace_function, "int main(int, char*[])", __func__, SLOG_FUNC_INFO);

  init();

  Interactive lang_interactive(".loosh_history", "loosh> ");
  //rl_variable_bind("completion-append-space", "off");
  rl_attempted_completion_function = lang_interactive.command_completion;
  it_ptr = &lang_interactive;
  Commandline cml(argc, argv);
  lang_interactive.interact(cml);
  lang_interactive.pop_last_exit_history();
  lang_interactive.save_history();
  //cout << "\n"; lang_it.print(); cout << "\n";





}
