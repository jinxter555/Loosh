#include <iostream>
#include <cstring>
#include "lisp_reader.hh"
#include "lisp.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

namespace Loosh 
{
ostream& operator<<(ostream& os, const Token& v) {
  cout << v.m_value;
  return os;
}
ostream& operator<<(ostream& os, list<Token>& l) {
  for(auto v: l) {
    cout << v << " ";
  }
  return os;
}

LispReader::LispReader() {
  MYLOGGER(trace_function, "LispReader::LispReader(LispExpr *) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("keywords init: ") , SLOG_FUNC_INFO);

}

void LispReader::reset() { col_=1; line_=1; }

void LispReader::to_newline(const string&input, size_t &i) {
  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(c=='\n') break;
  }
}

string LispReader::extract_quoted_string(const string&input, size_t &i) {
  string result;
  bool in_quote = true;
  bool escaped = false;
  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(escaped) {
      //result += c;
      result += escaped_char(c);
      escaped = false;
    }  else if(c == '\\') {
      escaped = true;
    } else if(c =='"') {
      in_quote = !in_quote;
      break;
    } else {
      result += c;
    }
    
  }
  return result;
}

string LispReader::extract_single_quoted_string(const string&input, size_t &i) {
  string result="";
  bool in_quote = true;
  bool escaped = false;
  size_t origin_start = i;

  for(++i; i<input.size(); i++) {
    char c = input[i];
    if(escaped) {
      result += c;
      escaped = false;
    // } else if(isspace(c)) {
    } else if(c == '\n') {
      i = origin_start; 
      return "";
    } else if(c == '\'') {
      in_quote = !in_quote;
      break;
    } else {
      result += c;
    }
  }
  // if(i>=input.size() && input[i] != '\'') { i= origin_start; return ""; };
  if(i==input.size()) { i = origin_start; return ""; };
  return result;
}


//------------------------------------------------------------------------ tokenize string  a list of tokens 
list<Token> LispReader::tokenize(const string& input)  {
  MYLOGGER(trace_function, "LispReader::tokenize(string&input)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("input: ") + input, SLOG_FUNC_INFO+30);

  list<Token> tokens;
  Token token; 
  string token_str;
  bool token_begin = false;
  //for(char c : input) {
  for(size_t i=0; i<input.size(); i++) {
    char c = input[i];
    if(isspace(c)) {
      token_begin = true;
      if(!token_str.empty()) {
        //token.line_ = line_; token.col_ = col_;
        token.m_value = move(token_str);
        tokens.push_back(token);
      }
      if(c=='\n') { line_++; col_= 1; continue;}

    } else if(c=='(' || c==')') {
      token_begin = true;

      if(!token_str.empty()) {
        //token.line_ = line_; token.col_ = col_-1;
        token.m_value = move(token_str);
        tokens.push_back(token);
      }
      //token.line_ = line_; token.col_ = col_-1;
      token.m_value = string(1,c);
      tokens.push_back(token);

    } else if(c == '"') {
      //token.m_value = move(extract_quoted_string(input, i));
      token.m_value = "\"" + move(extract_quoted_string(input, i));
      tokens.push_back(token);
      token_begin = true;


    } else if(c == '\'') {
      auto result_str  =  move(extract_single_quoted_string(input, i));
      if(result_str != "") {
        token.m_value = '\'' + result_str;
        tokens.push_back(token);
        token_begin = true;
      } else {
        if(token_begin) { token.col_ = col_; token_begin=false;}
        token_str += c;

      }

    } else if(c == '#') {
      token_begin = true;
      if(!token_str.empty()) {
        token.m_value = move(token_str);
        tokens.push_back(token);
      }
      to_newline(input, i);
      line_++; col_ = 1; 
      continue;

    } else {
      if(token_begin) { token.col_ = col_; token_begin=false;}
      token_str += c;

    }
    col_++;
  }

  if(!token_str.empty()) {
    //token.line_ = line_; token.col_ = col_-1;
    token.m_value = move(token_str);
    tokens.push_back(token);
  }
  return tokens;

}

string LispReader::_to_str(const list<Token>& tokens) {
  string result="[";
 
  //size_t i=0, s=tokens.size();
  for(auto token : tokens) {
    result = result + ","  + token.m_value;
  }
  return result + "]";
}


//------------------------------------------------------------------------ parse sequences of tokens after '('
Node::OpStatus LispReader::parse_sequence(list<Token>& tokens) {
  MYLOGGER(trace_function, "LispReader::sequence(list<Token>&tokens)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("tokens: ") + _to_str(tokens), SLOG_FUNC_INFO+30);
  Node::List list;
  bool is_first_element=true;
  string token_str;
  auto endable = tokens.front().m_value ;

  while(tokens.front().m_value != ")" ) {


    auto token_status = parse(tokens); //if(first_loop_run && token.m_value!= "(") {


    if(!token_status.first) return { false, 
      Node::create_error(Node::Error::Type::Parse, 
      "parsed error: " + token_status.second->_to_str() + "\n") };

    if(is_first_element) {
      is_first_element = false;

      // got a list after parse
      if(token_status.second->m_type== Node::Type::List) { list.push_back(move(token_status.second)); continue; }

      try {  // see if (keyword) or (scalar)

        token_str = get<string>(token_status.second->m_value);
        auto op = lisp->keyword_to_op(token_str); // Lisp::Op
        //MYLOGGER_MSG(trace_function, string("op: ") + Lisp::_to_str(op), SLOG_FUNC_INFO+30);

        if(op != Lisp::Op::scalar)  { // identifier or scalar
          MYLOGGER_MSG(trace_function, string("Lisp::Op: ") + Lisp::_to_str(op), SLOG_FUNC_INFO+30);
          list.push_back(Node::create(op));
          continue;
        }

          //MYLOGGER_MSG(trace_function, string("scalar: ") + token_str, SLOG_FUNC_INFO+30);
          //list.push_back(move(token_status.second));
      } catch(...) {}

    } 
    // for endables returns a ')', break out
    // if(token_status.second->is_nil()) break;
    


    list.push_back(move(token_status.second));
  }


  //token_previous.m_value = ")";
  tokens.pop_front(); // remove ')' token
  return {true, Node::create(move(list))};

}

//------------------------------------------------------------------------ parse a list of tokens
Node::OpStatus LispReader::parse(list<Token>& tokens) {
  MYLOGGER(trace_function, "LispReader::parse(list<Token>&tokens)", __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("lookup input: ") + input, SLOG_FUNC_INFO+30);

  if(tokens.empty()) 
    return {false, Node::create_error(Node::Error::Type::Incomplete, "Unexpected EOF parsing LispExpr.")};

  //Token token = tokens.front(); tokens.erase(tokens.begin());
  Token token_next, token = tokens.front(); tokens.pop_front();

  //cout << "token: '" <<  token << "', token_previous: '" << token_previous << "' \n";

  if(token.m_value == "'") { //  parse escaped literal list
    token_next = tokens.front(); tokens.pop_front();
    if(token_next.m_value == "(") {
      tokens.push_front({token_next.col_, token_next.line_, "literal"});
      return parse_sequence(tokens);
    }
  }

  if(token.m_value == "(") {
    //token_previous.m_value = "(";
    return parse_sequence(tokens);

  } else if(token.m_value==")") {

    return {false, Node::create_error(Node::Error::Type::Incomplete, "Unexpected ')'.")};

  } else {
    // Float
    if(token.m_value.find(".")  != std::string::npos) {
      try { 
        auto v = stod(token.m_value);  //cout << "d v:" << v << "\n";
        return {true, Node::create(v)};
      } catch(...) {}
    }

    // Integer
    try { 
      auto v = stol(token.m_value);  // cout << "l v:" << v << "\n";
      return {true, Node::create(v)}; 
    } catch(...) {}

    // atom
    if(token.m_value[0]==':') {
      token.m_value.erase(0, 1);
      auto v = lisp->str_to_atom(token.m_value); //auto node_ptr = Node::create(atom);
      auto node_ptr = Node::create(v); node_ptr->set_atom();
      return {true, move(node_ptr)}; 
    }
    // " quoted srepeat with 
    if(token.m_value[0]=='"') {
      token.m_value.erase(0, 1);
      string esc_str = raw_to_escaped_string(token.m_value);
      return {true, Node::create(esc_str)}; 

    }

    if(token.m_value[0]=='\'') {
      string esc_str =  token.m_value.erase(0, 1);
      //string esc_str = raw_to_escaped_string(token.m_value);
      return {true, Node::create(esc_str)}; 
    }



    if(token.m_value[0]=='@') {
      if(token.m_value.size() == 1 ) return {true, Node::create("this", Node::Type::Identifier)}; 
      token.m_value.erase(0, 1);
      string esc_str = "this." + token.m_value;
      return {true, Node::create(esc_str, Node::Type::Identifier)}; 
    }



    if(token.m_value=="true") {
      return {true, Node::create(true)}; 
    }
    if(token.m_value=="false") {
      return {true, Node::create(false)}; 
    }


    
  }

  /*
  if(is_endable(token.m_value) ) {
    //cout << "is_endable! token: '" <<  token << "' return nil\n";
    tokens.push_front(token);
    return {true, Node::create()};
  }*/

  // liis_closurable as in begin{}end
  /*
  if(is_closurable(token.m_value) && token_previous.m_value != "(") { 
    tokens.push_front(token);
    end_list.push_back(token.m_value); 
    token_previous.m_value = "(";
    return parse_sequence(tokens);
  }
*/


  // lisp identifier 
  /*
  cout << "token: '" <<  token << "', token_previous: '" << token_previous << "' \n";
  token_previous.col_= token.col_;
  token_previous.line_= token.line_;
  token_previous.m_value = token.m_value;
*/
  //token_previous.m_value = token.m_value;

  auto node_ptr = Node::create(token.m_value); 
  node_ptr->set_identifier();
  return {true, move(node_ptr)};
}

//------------------------------------------------------------------------ pre tokenize string
string LispReader::tokenize_preprocess(const string& input) {
  auto input_paren = 
    tokenize_preprocess_multiline_parenthesis(
      tokenize_preprocess_multiline(input));
  //cout << "after putting ():\n" << input_paren <<"\n\n";

  return input_paren;
}


string LispReader::tokenize_preprocess_multiline(const string& input) {

  istringstream stream(input); // Wrap the string in an input string stream
  string line_current, line_result;
  bool multi_line = false;

  while (getline(stream, line_current)) {
    if(multi_line) { // multi line begins

      if(line_current.back() == '\\') { 
        line_current.pop_back(); // get rid multi line character
        multi_line = true;
      } else {
        multi_line = false;
        line_current += "\n";
      }
      line_result += line_current;
      continue;
    }

    if(line_current.back() == '\\') {
      line_current.pop_back();
      multi_line = true;
    } else {
      multi_line = false;
      line_current += "\n";

    }

    line_result += line_current;
  }
  convert_to_infix(line_result);

  return line_result;
}



string LispReader::tokenize_preprocess_multiline_parenthesis(const string& input) {
  istringstream stream(input); // Wrap the string in an input string stream

  string line_current, line_result;

  while (getline(stream, line_current)) {
    auto line = trim(line_current);



    // ignore all comments
    size_t comment_pos = line.find("#");
    if (comment_pos != std::string::npos) {
        line.erase(comment_pos);
    }

    if(line == "") continue;
    //auto line_vector = split_string(line, " ");
    auto line_vector = tokenize_pre(line);

    if(line_vector.front() == "#") continue;

    if(is_closurable(line_vector.front())) {
      //cout << "line is closurable " <<  line_vector[0] <<  " " <<line_vector.back() << "\n";
      line_result += "(" + join_str(line_vector) + "\n";
      end_list.push_back(line_vector[0]); 
      continue;
    }
    if(is_endable( line_vector.back()) )  {
      auto line_back_vector = split_string(line_vector.back(), ".");
      auto back = end_list.back();

      if(back != line_back_vector.back()) {
        cout << "endlist " << _to_str_ext(end_list) << "\n";
        cout << "error with parsing closing token! '" << back <<"' \n";
        exit(1);
      }  
      end_list.pop_back();


      line_result += ")\n";
      continue;
    }


    if(line.front() != '(' && line.back() == ')' && is_complete_parenthesis(line)){ 
      line_result += "(" + line + ")"+"\n";
      continue;
    }

    if(line.front() != '(' && line.back() != ')'){ //   lispfun arg1 arg2 ...
      line_result += "(" + line + ")"+"\n";
      continue;
    } 

    line_result +=  line +"\n";

  }

//  cout << "\nline result:\n" << line_result << "\n";
  return line_result;
}



//------------------------------------------------------------------------ 

bool LispReader::is_closurable(const string&token_str) {
  MYLOGGER(trace_function, "LispReader::is_closurable(const string&token_str) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "token_str: " + token_str , SLOG_FUNC_INFO);


  if(closurable_user_defined.count(token_str)  
  && closurable_user_defined.at(token_str)==true) 
    return true;

  auto op = lisp->keyword_to_op(token_str); // Lisp::Op



  return is_closurable(op);
}


//------------------------------------------------------------------------ 
bool LispReader::is_closurable(Lisp::Op op) {
  switch(op) {
  case Lisp::Op::class_:
  case Lisp::Op::module_:
  case Lisp::Op::loop:
  case Lisp::Op::while_:
  case Lisp::Op::repeat:
  case Lisp::Op::for_:
  case Lisp::Op::do_:
  case Lisp::Op::if_:
  case Lisp::Op::iif:
  case Lisp::Op::cond:
  case Lisp::Op::case_:
  case Lisp::Op::match:
  case Lisp::Op::def:
  case Lisp::Op::defun:
  case Lisp::Op::lambda:
  case Lisp::Op::defmacro:
  case Lisp::Op::quote:
  case Lisp::Op::pipe:
  case Lisp::Op::curry:
  //case Lisp::Op::eval:
    return true;
  default: {}}
  return false;
}
//------------------------------------------------------------------------ 
bool LispReader::is_endable(const string&token_str) {
  MYLOGGER(trace_function, "LispReader::is_endable(const string&token_str) ", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "token_str: " + token_str , SLOG_FUNC_INFO);

  auto list =  split_string(token_str, ".");
  //cout << "is_endalbe() token_str: " << token_str <<  ", list.size(): " << list.size() << "\n";

  string end="", op_str="";
  if(list.size() == 1)  { 
   op_str = list[0];
   if(op_str != "end") return false;
  } else if (list.size() == 2) {
    end=list[0], 
    op_str=list[1];
   if(end != "end") return false;
  }

  //cout << "end : " << end<< "\n";
  //cout << "opstr: " << op_str << "\n";

  // use user defined as well 
  return is_closurable(op_str);

  // might need to get rid of these two lines

  auto op = lisp->keyword_to_op(op_str); // Lisp::Op
  return is_closurable(op);
}


bool LispReader::is_complete_parenthesis(const string& input) {
  vector<char> plist;
  size_t s=input.size();
  for(size_t i=0; i<s; i++) {
    char c = input[i];
    if(input[i] == '(') {
      plist.push_back(c);
    }
    if(input[i] == ')') {
      if(plist.empty()) return false;
      plist.pop_back();
    }
  }
  if(plist.size() != 0)
    return false;
  return true;
}



vector<string> LispReader::tokenize_pre(const string& input) {
  vector<string> tokens;
  string token;
  for (char c : input) {
      if (isspace(c)) {
          if (!token.empty()) tokens.push_back(token), token.clear();
      } else if (c == '(' || c == ')') {
          if (!token.empty()) tokens.push_back(token), token.clear();
          tokens.push_back(string(1, c));
      } else {
          token += c;
      }
  }
  if (!token.empty()) tokens.push_back(token);
  return tokens;
}

bool LispReader::load_closurable(const string&file) {
  std::ifstream infile(file);
  if(! infile.is_open()) {
    return false;
  }

  string line, source_str; 

  while(getline(infile, line) ) {
    closurable_user_defined[line] = true;

  }
//  for(auto&p : closurable_user_defined) cout << "p.first: " << p.first << ", p.second: " << p.second << "\n";

  infile.close();
  return true;

}
}