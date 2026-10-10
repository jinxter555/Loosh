#include <iostream>
#include <cstring>
#include "lisp_reader.hh"
#include "lisp_expr.hh"
#include "my_helpers.hh"


#include <stack>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

using namespace std;

bool sym_lang(char c) {
  switch(c) {
  case '$' : return true;
  case '@' : return true;
  case '~' : return true;
  case '"' : return true;
  case ':' : return true;
  case '_' : return true;
  default: return false;
  }
  return false;
} 


// Updated Tokenizer to handle \( ... ) as a single literal token
vector<string> tokenize_infix(string infix) {
  MYLOGGER(trace_function, "tokenize_infix(string& infix)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "infix_input " + infix , SLOG_FUNC_INFO+30);

  vector<string> tokens;
  for (size_t i = 0; i < infix.length(); i++) {
    if (isspace(infix[i])) continue;

    // Handle Escape Character \( ... )
    if (infix[i] == '\\' && i + 1 < infix.length() && infix[i+1] == '(') {
      string literal = "(";
      int bracketCount = 1;
      i += 2; // Move past '\('
      while (i < infix.length() && bracketCount > 0) {
          if (infix[i] == '(') bracketCount++;
          if (infix[i] == ')') bracketCount--;
          literal += infix[i++];
      }
      tokens.push_back(literal); // Push the whole inner expression as one token
      i--; // Adjust for outer loop increment
    } 
    else if (isalnum(infix[i]) || infix[i]=='.' || sym_lang(infix[i])) {
        string current;
        while (i < infix.length() && (isalnum(infix[i]) || infix[i]=='.' || sym_lang(infix[i]))) {
            current += infix[i++];
        }
        //cout << "current: " << current << "\n";
        tokens.push_back(current);
        i--;
    } 
    else {
      string op;
      while (i < infix.length() ) {
        if(isalnum(infix[i]) || isspace(infix[i]) || sym_lang(infix[i])) { i--; break;}
        op += infix[i++];
      }
      tokens.push_back(op);
    }
  }
  if(tokens.size() == 1) {
    return tokens;
  }
  //if(tokens.size() == 2) { return tokens; }
  if(tokens.size() == 2) { 
    //cout << "2 tokens: " << _to_str_ext(tokens) << "\n";
    tokens.push_back("noop");
    return tokens; 
  }

  if(tokens.size() < 3) {
   auto msg = "infix tokens need to be than 1 or 3 parameters  in froms [a op b]: but got [" + infix + "]";
    cerr << msg << "\n";
    return {"(", "error", ")"};
  }
  return tokens;
}

int precedence(string op) {
  if (op == "==" || op == "!=") return 1;
  if (op == "<=" || op == ">=") return 1;
  if (op == "<" || op == ">") return 1;
  if (op == "+" || op == "-") return 2;
  if (op == "*" || op == "/" || op == "%") return 3;
  if (op == "^") return 4;
  return 0;
}


string infixToLispPrefix(string infix) {
  vector<string> tokens = tokenize_infix(infix);
  stack<string> operands;
  stack<string> operators;

  auto processOp = [&]() {
      if (operands.size() < 2) return; 
      string op = operators.top(); operators.pop();
      string op2 = operands.top(); operands.pop();
      string op1 = operands.top(); operands.pop();
      operands.push("(" + op + " " + op1 + " " + op2 + ")");
  };

  for (const string& token : tokens) {
    // If it's an operand OR an escaped literal (starts with '(')
    if (isalnum(token[0]) || sym_lang(token[0]) || (token.size() > 1 && token[0] == '(')) {
        operands.push(token);
    } else if (token == "(") {
        operators.push(token);
    } else if (token == ")") {
        while (!operators.empty() && operators.top() != "(") {
            processOp();
        }
        if (!operators.empty()) operators.pop();
    } else {
        while (!operators.empty() && operators.top() != "(" && 
               precedence(operators.top()) >= precedence(token)) {
            processOp();
        }
        operators.push(token);
    }
  }

  while (!operators.empty()) processOp();
  return operands.empty() ? "" : operands.top();
}



vector<string> find_bracketed_strings(const std::string& input) {
    // R"(\[([^\]]*)\])"
    // \[ matches the literal [
    // ([^\]]*) captures any characters that are NOT ]
    // \] matches the literal ]
    std::regex bracket_regex(R"(\[([^\]]*)\])");
    std::smatch matches;
    vector<string> result;

    auto search_start = input.cbegin();
    while (std::regex_search(search_start, input.cend(), matches, bracket_regex)) {
        // matches[1] contains the captured group (inner string)
        result.push_back(matches[1].str());
        // Move to the next part of the string
        search_start = matches.suffix().first;
    }
    return result;
}


std::string replace_bracketed_string(std::string input, const std::string& replacement) {
    // R"(\[[^\]]*\])"
    // \[      -> Literal opening bracket
    // [^\]]*  -> Matches any character except a closing bracket (non-greedy)
    // \]      -> Literal closing bracket
    std::regex bracket_regex(R"(\[[^\]]*\])");

    // regex_replace returns a new string with all matches substituted
    return std::regex_replace(input, bracket_regex, replacement, std::regex_constants::format_first_only);
}


void LispReader::convert_to_infix(string& infix_input) {
  MYLOGGER(trace_function, "LispReader::convert_to_infix(string&infx_input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "infix_input " + infix_input , SLOG_FUNC_INFO+30);

  auto bracket_strings  = find_bracketed_strings(infix_input);

  string input = infix_input;

  for(auto infix_str : bracket_strings) {
    auto lisp_prefix_str =  infixToLispPrefix(infix_str);
    MYLOGGER_MSG(trace_function, "lisp_prefix " + lisp_prefix_str , SLOG_FUNC_INFO+30);
    input  = replace_bracketed_string(input, lisp_prefix_str);
  }
  infix_input = input;
}