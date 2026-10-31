
%top{
#include "node.hh"

#include <string>
%}

/* Tell RE/flex to generate the Lexer inside the LSHLexer namespace */
%option namespace="Reader::Inline"
%option outfile="lex.yy.cc"
%option header-file="lex.yy.hh"
%option token-type="unique_ptr<Loosh::Token>"

%include "lexer_generic.l"

%%

{blank}+                { /* Skip spaces, tabs, carriage returns */ }
\n+                     { /* Skip standalone newlines */ }
";".*                   { /* Skip line comments */ }

//"("                     { return Loosh::Token::create(Token::Type::Lparen, std::monostate{}, lineno(), columno()); }
"("                     { return Loosh::Token::create(Loosh::Token::Type::Lparen, monostate{}, lineno(), columno()); }

")"                     { return Loosh::Token::create(Loosh::Token::Type::Rparen, monostate{}, lineno(), columno()); }

{float_}                 { return Loosh::Token::create(Loosh::Token::Type::float_,   std::stod(text()),  lineno(), columno()); }
{integer_}               { return Loosh::Token::create(Loosh::Token::Type::integer_, std::stoll(text()), lineno(), columno()); }

{dqstring}              { 
  std::string str = text();
  std::string actual_val = str.substr(1, str.length() - 2);
  return Loosh::Token::create(Loosh::Token::Type::string_, actual_val, lineno(), columno()); 
}

//{symbol}                { return Token::create(Token::Type::Symbol, text(), lineno(), columno()); }
{identifier}                { return Loosh::Token::create(Loosh::Token::Type::identifier, text(), lineno(), columno()); }

"begin."({identifier})      {       // matcher()[1] isolates exactly what was caught in the 1st set of parentheses
   auto group1 = matcher()[1]; // matcher()[1] returns the std::pair<const char*, size_t>
  std::string symbol_text(group1.first, group1.second); // Construct the std::string safely using pointer + length
  return Loosh::Token::create(Loosh::Token::Type::identifier, symbol_text, lineno(), columno());
}

.                       { return Loosh::Token::create(Loosh::Token::Type::error, text(), lineno(), columno()); }

<<EOF>>                 { return Loosh::Token::create(Loosh::Token::Type::done, std::monostate{}, lineno(), columno()); }



%%
