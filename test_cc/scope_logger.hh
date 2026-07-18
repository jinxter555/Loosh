#ifndef SCOPE_LOGGER_HH
#define SCOPE_LOGGER_HH
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define SLOG_MAX_LEVEL 0
#define SLOG_MAX_LEVEL 130000
#define DEBUG


using namespace std;

extern std::fstream log_output;
extern std::fstream trace_function;

class ScopeLogger {
private:
  fstream &out;

  string msg_in, msg_out;

  int id_, current_level;

  inline static vector <int> levels;
  inline static int id_log = 0 ;
  inline static int verbosity = 0;

  int verbosity_obj = 0;
public:
  ScopeLogger( fstream &,  const string & , const string &, int verbose_level=0);
  ~ScopeLogger() ;
  void msg(const string&, int verbose_level=0);
  void set_current_stack_level();
  static void set_current_verbose_level(int);
  string spacing();
};


#ifdef SLOG_DEBUG_TRACE_FUNC
#define MYLOGGER(x, y, z, v) ScopeLogger l_##x##_scope(x, y, z, v);
#define MYLOGGER_MSG(x, y, v) l_##x##_scope.msg(y, v);
#else
#define MYLOGGER(x, y, z)
#define MYLOGGER_MSG(x, y)
#endif

#define SLOG_FUNC_INFO   10
#define SLOG_TO_STR      5000

#define SLOG_NODE_OP      5000
#define LOC_FUN source_location::current().function_name()

#endif
