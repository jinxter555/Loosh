#include <map>
#include <vector>
#include "color_esc.hh"




std::string to_ansi_escape(int code) { return "\033[" + std::to_string(code) + "m"; }
