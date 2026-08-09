#include "trace_guard.hh"
    // Thread-local depth counter. Isolated per thread.

thread_local int  TraceGuard::call_depth = 0;

    // 1. Array of standard ANSI Color codes (Foreground types)
    // We omit dark colors like black or dark blue to keep it readable on dark themes.
const std::vector<const char*> TraceGuard::colors = {
  "\033[31m", // Red
  "\033[32m", // Green
  "\033[33m", // Yellow
  "\033[34m", // Blue
  "\033[35m", // Magenta
  "\033[36m", // Cyan
  "\033[37m", // White
  "\033[91m", // Light Red
  "\033[92m", // Light Green
  "\033[93m", // Light Yellow
  "\033[94m", // Light Blue
  "\033[95m", // Light Magenta
  "\033[96m"  // Light Cyan
};
    
// The ANSI code to clear formatting back to default text styles
const char* TraceGuard:: reset_color = "\033[0m";

// Helper to pick a color safely using modulo cycling
const char* TraceGuard::get_color(int depth) const {
  // Ensures we handle negative depth values gracefully if an edge case occurs
  size_t index = static_cast<size_t>(std::abs(depth)) % colors.size();
  return colors[index];
}

string TraceGuard::get_indent() const {
  return std::string(call_depth * 2, ' ');
}

string TraceGuard::get_thread_id_str() const {
  std::stringstream ss;
  ss << std::this_thread::get_id();
  return ss.str();
}

//TraceGuard::TraceGuard(const char* name) : function_name(name) { }
TraceGuard::TraceGuard(const string & name) : function_name(name) {
  const char* current_color = get_color(call_depth);

  instance_id = global_sequence_counter.fetch_add(1, memory_order_relaxed);


  spdlog::info("TraceGuard() name {}", name);
  
  // Wrap the payload with the target color prefix and the reset suffix
  SPDLOG_TRACE("[Thread {}] [Depth {}] [Id: #{}] {}{}-─> Entering: {}{}", 
    get_thread_id_str(), call_depth, instance_id, get_indent(), 
    current_color, function_name, reset_color);
  call_depth++;
}

TraceGuard::~TraceGuard() {
  call_depth--;
  const char* current_color = get_color(call_depth);
  
  SPDLOG_TRACE("[Thread {}] [Depth {}] [Id: #{}] {}{}<──  Exiting: {}{}", 
    get_thread_id_str(), call_depth, instance_id, get_indent(), 
    current_color, function_name, reset_color);
}


