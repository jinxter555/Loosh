#include <string>
#include "interactive.hh"
#include "commandline.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

struct option Commandline::long_options[] = {
  {"inputfile", required_argument, NULL, 'f'},
  {"lang", required_argument, NULL, 'l'},
  {NULL, 0, NULL, 0}
};

//Commandline::Commandline(int argc, char* argv[]) {
Commandline::Commandline(int ac, char* av[]) {
  argc = ac;
  argv = av;
  
  int opt;
  while( (opt = getopt_long(argc, argv, "prhic:l:f:o:", long_options, NULL)) != -1) {
    switch(opt) {
      case 'i': { opt_interactive = true; break; }
      case 'r': { opt_run= true; break;}
      case 'p': { opt_print= true; break;}
      case 'l': {
        if(optarg == string("lisp")) lisp_lang = true;
        if(optarg == string("svlm")) svlm_lang = true;
        if(optarg == string("asm")) assembly_lang = true;
        break;
      }
      case 'f': infile_name  = optarg; opt_file=true; break;
      case 'h': outerr(argv); exit(0); break;
      case 'c': { 
        closurable_file_name=optarg; opt_closurable=true; break; 
      
      }
    }
  }
  for(; optind < argc; optind++){      
    infile_name += " " + string(argv[optind]);  
    opt_file=true;
    opt_run=true;
  } 

}

void Commandline::outerr(char *argv[]) {
  std::cerr 
    << "Usage: " 
    << argv[0] 
    << " [-r ] [-i interactive] [-f inputfile] [--inputfile=inputfile] [-o outputfile] [--outputfile=outputfile]\n"
    << " -r run program after load\n"
    ;


};


void Commandline::printout() {
  /*
  for (auto const& pair : options)
    std::cout 
      << pair.first 
      << ": " 
      << pair.second 
      << std::endl;
  */
  std::cout << "\n";
  for(auto const& str : arguments) 
    std::cout << str << " ";
  std::cout << "\ninfile:" << infile_name << "\n";

  if(opt_interactive)
    std::cout << "interactive: true" << " ";
  else
    std::cout << "interactive: false" << " ";

  std::cout << "\n";
}

void Commandline::run(Interactive* interactive) {

  { // load closurable for macros
    auto& lisp_reader = interactive->get_reader();
    lisp_reader.load_closurable(closurable_file_name);
  }

  if(opt_file){
    load_files(interactive, infile_name);
  }



  interactive->build_program(); // LispExpr post process

  if(opt_run) {
    //interactive->run_program();
    interactive->run_program(argc, argv);
  }

  if(opt_interactive) {
    cout << "interact with interactive lang!\n";
    interactive->ready();
  }
  if(opt_print) interactive->print();
}

// build with mulitple source lisp files
void Commandline::load_files(Interactive *interactive, const string& file_str) {
  MYLOGGER(trace_function , "Commandline::load_files(" + file_str + ")", __func__, SLOG_FUNC_INFO);

  auto files = split_string(trim(file_str), " ");
  for(auto file : files) {
    auto load_status = interactive->load(file);
    if(!load_status.first) { 
      cerr << "load file error: status error:" << load_status << "\n";
      exit(1); 
    }

    auto source_status = (*load_status.second)["source_str"];
    if(!source_status.first) {
      cerr << "map source[] status error" << source_status << "\n";
      return;
    }
    auto build_status  = interactive->build_file_str( source_status.second._get_str());
    if(!build_status.first) {
      cerr << "lang build file str()  error status error: " << build_status << "\n";
      exit(1);
    }
  }

}