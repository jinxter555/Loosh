#pragma once
#ifndef TRACE_GUARD_HH
#define TRACE_GUARD_HH


#ifndef SPDLOG_ACTIVE_LEVEL 
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE 
#endif

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <string>
#include <thread>
#include <sstream>
#include <vector>
#include "defs.hh"

using namespace std;

class TraceGuard {
private:
  //const char* function_name;
  const string function_name;
   LOOSH_T_LONG instance_id;

  // Thread-local depth counter. Isolated per thread.
  static thread_local int call_depth ;
  inline static atomic<LOOSH_T_LONG>  global_sequence_counter{0};

  // 1. Array of standard ANSI Color codes (Foreground types)
  // We omit dark colors like black or dark blue to keep it readable on dark themes.
  static const vector<const char*> colors ;
  
  // The ANSI code to clear formatting back to default text styles
  static const char* reset_color ;

  // Helper to pick a color safely using modulo cycling
  const char* get_color(int depth) const ;

  std::string get_indent() const ;

  string get_thread_id_str() const ;

public:
  //TraceGuard(const char* name) ;
  TraceGuard(const string& name) ;

  ~TraceGuard() ;

  TraceGuard(const TraceGuard&) = delete;
  TraceGuard& operator=(const TraceGuard&) = delete;
};

//#define AUTO_TRACE() TraceGuard trace_guard_obj(__func__)
#define AUTO_TRACE() TraceGuard trace_guard_obj(clean_function_name())



#endif