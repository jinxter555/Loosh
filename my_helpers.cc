#include "my_helpers.hh"

std::vector<std::string> 
split_string(const std::string& istr, const std::string& delimiter) {
    std::vector<std::string> result;
    std::string str = istr;
    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    // Add the last remaining substring
    result.push_back(str);

    return result;
}

std::list<std::string> 
split_string_list(const std::string& istr, const std::string& delimiter) {
    std::list<std::string> result;
    std::string str = istr;
    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    // Add the last remaining substring
    result.push_back(str);

    return result;
}
std::deque<std::string> 
split_string_deque(const std::string& istr, const std::string& delimiter) {
    std::deque<std::string> result;
    std::string str = istr;
    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    // Add the last remaining substring
    result.push_back(str);

    return result;
}




std::string trim(const std::string& str, const std::string& whitespace ){
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str, const std::string& fill , const std::string& whitespace ) {
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

std::string match(const std::string& line, const std::string& pattern) {
  std::smatch match;
  std::regex regex(pattern);

  if (std::regex_search(line, match, regex)) {
    // Match found, return the rest of the line after the match
    return line.substr(match.position() + match.str(0).size());
  } else {
    // No match found, return an empty string
    return "";
  }
}
char escaped_char(const char& c) {
  switch (c) {
     case '\\': return '\\'; // Backslash
     case 'n': return '\n'; // Newline
     case 't': return '\t'; // Tab
     case '\"': return '\"'; // Double quote
     case '\'': return '\''; // Single quote
     case 'r': return '\r'; // Carriage return
     case 'b': return  '\b'; // Backspace
     case 'f': return '\f'; // Form feed
     case 'a': return '\a'; // Alert (bell)
     case 'v': return '\v'; // Vertical tab
     case '?': return '\?'; // Question mark
     case '0': return '\0'; // Null character
     default: return c;
  }
}


std::string raw_to_escaped_string(const std::string& s) {
    std::string result;
    std::string::const_iterator it = s.begin();

    while (it != s.end()) {
        char c = *it++;
        if (c == '\\' && it != s.end()) {
            switch (*it++) {
                case '\\':
                    result += '\\'; // Backslash
                    break;
                case 'n':
                    result += '\n'; // Newline
                    break;
                case 't':
                    result += '\t'; // Tab
                    break;
                case '\"':
                    result += '\"'; // Double quote
                    break;
                case '\'':
                    result += '\''; // Single quote
                    break;
                case 'r':
                    result += '\r'; // Carriage return
                    break;
                case 'b':
                    result += '\b'; // Backspace
                    break;
                case 'f':
                    result += '\f'; // Form feed
                    break;
                case 'a':
                    result += '\a'; // Alert (bell)
                    break;
                case 'v':
                    result += '\v'; // Vertical tab
                    break;
                case '?':
                    result += '\?'; // Question mark
                    break;
                case '0':
                    result += '\0'; // Null character
                    break;
                // Add other escape sequences as needed
                default:
                    // Invalid escape sequence - keep the character unchanged
                    result += c;
            }
        } else {
            result += c; // No escape sequence, keep the character as is
        }
    }

    return result;
}

string add_vector_string(const vector<string> &vs, const string& delimiter) {
  string result="[";
  int i, s=vs.size();
  for(i=0; i<s-1; i++) {
    result = result  + vs[i] + delimiter ;
  }
  result = result + vs[i]+ "]";
  return result;
}

string concat_vector_string(const vector<string> &vs, const string& delimiter) {
  string result="";
  int i, s=vs.size();
  for(i=0; i<s-1; i++) {
    result = result  + vs[i] + delimiter ;
  }
  result = result + vs[i];
  return result;
}

std::string extractClassName(const std::string& prettyFunction) {
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos) return "::";
    size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
    size_t end = colons - begin;
    return prettyFunction.substr(begin, end);
}

string  _to_str_ext(const vector<string>& keys) {
  string v="["; size_t i=0, s=keys.size();
  if(s==0) return "[]";
  for(; i<s-1; i++) {
    v = v+ keys[i] + ", ";
  }
  return v+keys[i]+"]";
}

string  _to_str_ext(const deque<string>& keys) {
  string v="["; size_t i=0, s=keys.size();
  if(s==0) return "[]";
  for(; i<s-1; i++) {
    v = v+ keys[i] + ", ";
  }
  return v+keys[i]+"]";
}



string  _to_str_ext(const list<string>& keys) {
  string v="["; size_t i=0, s=keys.size();
  if(s==0) return "[]";
  for(auto key : keys ) {
    if(i++==s-1) break;
    v = v+ key + ", ";
  }
  return v+keys.back()+"]";
}



string join_str(const vector<std::string>& elements, const string& delimiter) {
    stringstream ss;
    for (size_t i = 0; i < elements.size(); ++i) {
        ss << elements[i];
        if (i < elements.size() - 1) {
            ss << delimiter;
        }
    }
    return ss.str();
}

string join_str(const deque<std::string>& elements, const string& delimiter) {
    stringstream ss;
    for (size_t i = 0; i < elements.size(); ++i) {
        ss << elements[i];
        if (i < elements.size() - 1) {
            ss << delimiter;
        }
    }
    return ss.str();
}

std::vector<std::string> split_string_except_quoted(const std::string& s, char delimiter) {
  std::vector<std::string> result;
  std::string current_token;
  bool in_quotes = false;

  for (char c : s) {
    if (c == '"') {
     in_quotes = !in_quotes; // Toggle the in_quotes flag
     // current_token += c; // Optionally keep quotes in the output
    } else if (c == delimiter && !in_quotes) {
     // If the character is the delimiter AND we are not in quotes
     result.push_back(current_token);
     current_token.clear();
    } else {
     current_token += c;
    }
  }

  // Add the last token
  result.push_back(current_token);
  
  return result;
}



std::string addressToHexString(void* ptr) {
    char buffer[20]; // Large enough for 64-bit address + prefix
    auto [p, ec] = std::to_chars(buffer, buffer + 20, reinterpret_cast<uintptr_t>(ptr), 16);
    return "0x" + std::string(buffer, p - buffer);
}
