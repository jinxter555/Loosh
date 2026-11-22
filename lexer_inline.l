%top{
#include "node.hh"
#include "atom.hh"
#include "lisp_reader.hh"

#include <string>


// Silences the internal RE/flex name-hiding bug caused by the nested namespace
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Woverloaded-virtual"
#endif

%}

/* Tell RE/flex to generate the Lexer inside the LSHLexer namespace */
%option namespace="Loosh::Reader::Inline"
%option outfile="lex.yy.cc"
%option header-file="lex.yy.hh"
%option token-type="unique_ptr<Loosh::Token>"

%include "lexer_generic.l"

%class{
public:
    LispReader* reader = nullptr;

    void set_reader(LispReader* r) {
        reader = r;
    }
}
%%

{blank}+                { /* Skip spaces, tabs, carriage returns */ }
\n+                     { /* Skip standalone newlines */ }
";".*                   { /* Skip line comments */ }

"("                     { return Loosh::Token::create(Loosh::Token::Op::Lparen, monostate{}, lineno(), columno()); }

")"                     { return Loosh::Token::create(Loosh::Token::Op::Rparen, monostate{}, lineno(), columno()); }
"+"                     { return Loosh::Token::create(Loosh::Token::Op::add , Loosh::Node::Op::add, lineno(), columno()); }
"-"                     { return Loosh::Token::create(Loosh::Token::Op::sub , Loosh::Node::Op::sub, lineno(), columno()); }
"*"                     { return Loosh::Token::create(Loosh::Token::Op::mul , Loosh::Node::Op::mul, lineno(), columno()); }
"/"                     { return Loosh::Token::create(Loosh::Token::Op::div , Loosh::Node::Op::div, lineno(), columno()); }

{float_}                 { return Loosh::Token::create(Loosh::Token::Op::float_,   std::stod(text()),  lineno(), columno()); }
{integer_}               { return Loosh::Token::create(Loosh::Token::Op::integer_, std::stoll(text()), lineno(), columno()); }

{dqstring}              { 
  std::string str = text();
  std::string actual_val = str.substr(1, str.length() - 2);
  return Loosh::Token::create(Loosh::Token::Op::string_, actual_val, lineno(), columno()); 
}

//{symbol}                { return Token::create(Token::Op::Symbol, text(), lineno(), columno()); }
//^{identifier}                { return Loosh::Token::create(Loosh::Token::Op::closurable_begin, text(), lineno(), columno()); }

":"({identifier})      {       // matcher()[1] isolates exactly what was caught in the 1st set of parentheses
  std::string_view atom_match (matcher().begin() + 1, matcher().size() - 1);



  string atom_text = text();
  atom_text.erase(0, 1); // Erase ':' character starting at index 0

  
  //cout << "text(): " << text()<< "\n";
  //cout << "atom_mtach: " << atom_match << "\n";
  //cout << "atom_text: " << atom_text << "\n";
  auto atom_value =  Loosh::Atom::str_to_atom(atom_text);
  //cout << "atom_value: " << atom_value << "\n";
  auto atom_str =  Loosh::Atom::atom_to_str(atom_value);
  //cout << "atom_str: " << atom_str << "\n";

  return Loosh::Token::create(
    Loosh::Token::Op::atom, 
    Loosh::Node::create(atom_value,  Loosh::Node::Type::Atom),
    lineno(), columno()
  );
}

"begin."({identifier})      {       // matcher()[1] isolates exactly what was caught in the 1st set of parentheses
  std::string symbol_text (matcher().begin() + 6, matcher().size() - 6);
  cout << "symbol_text: " << symbol_text << "\n";

  return Loosh::Token::create(Loosh::Token::Op::identifier, symbol_text, lineno(), columno());
}


{identifier}                { 
  string txt = text();
  Node::OpStatus lisp_keyword = reader->lisp->str_to_op(txt);
  if(lisp_keyword.first)  {
    return Loosh::Token::create(lisp_keyword.second->_get_op(), txt, lineno(), columno()); 
  }
  else {
    return Loosh::Token::create(Loosh::Token::Op::identifier, txt, lineno(), columno()); 
  } 



}


{sym_op} {

}

.                       { return Loosh::Token::create(Loosh::Token::Op::error, text(), lineno(), columno()); }

<<EOF>>                 { return Loosh::Token::create(Loosh::Token::Op::done, std::monostate{}, lineno(), columno()); }



%%
