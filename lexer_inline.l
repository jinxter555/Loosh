
%top{
#include "node.hh"
#include "atom.hh"

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
  auto atom_value =  Loosh::Atom::str_to_atom(text());
  cout << "atom_value: " << atom_value << "\n";

  return Loosh::Token::create(
    Loosh::Token::Op::atom, 
    Loosh::Node::create(atom_value,  Loosh::Node::Type::Atom),
    lineno(), columno()
  );
}

"begin."({identifier})      {       // matcher()[1] isolates exactly what was caught in the 1st set of parentheses
  auto group1 = matcher()[1]; // matcher()[1] returns the std::pair<const char*, size_t>
  std::string symbol_text(group1.first, group1.second); // Construct the std::string safely using pointer + length
  return Loosh::Token::create(Loosh::Token::Op::identifier, symbol_text, lineno(), columno());
}


{identifier}                { return Loosh::Token::create(Loosh::Token::Op::identifier, text(), lineno(), columno()); }

.                       { return Loosh::Token::create(Loosh::Token::Op::error, text(), lineno(), columno()); }

<<EOF>>                 { return Loosh::Token::create(Loosh::Token::Op::done, std::monostate{}, lineno(), columno()); }



%%
