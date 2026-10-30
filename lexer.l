
%top{
#include "node.hh"

#include <string>
%}

/* Tell RE/flex to generate the Lexer inside the LSHLexer namespace */
%option namespace="Loosh"
%option outfile="lex.yy.cc"
%option header-file="lex.yy.hh"
%option token-type="unique_ptr<Loosh::Token>"

/* --- Named Definitions Section --- */
dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)
integer_         ({dseq})
float_           (({frac}{exp_opt})|({dseq}{exp}))

blank           [ \t\r]           
dqstring        \"([^"\\]|\\.|\\n|\n)*\"

sym_char        [a-zA-Z0-9+\-*/=<>!?_]
symbol          [a-zA-Z+\-*/=<>!?_]{sym_char}*
identifier      ([a-zA-Z][a-zA-Z0-9_]*)
//lc_identifier   ([a-z_][a-z0-9_]*)
//cap             ([A-Z_])

%%

{blank}+                { /* Skip spaces, tabs, carriage returns */ }
\n+                     { /* Skip standalone newlines */ }
";".*                   { /* Skip line comments */ }

//"("                     { return Loosh::Token::create(Token::Type::Lparen, std::monostate{}, lineno(), columno()); }
"("                     { return Token::create(Token::Type::Lparen, nullptr, lineno(), columno()); }

")"                     { return Token::create(Token::Type::Rparen, monostate{}, lineno(), columno()); }

{float_}                 { return Token::create(Token::Type::float_,   std::stod(text()),  lineno(), columno()); }
{integer_}               { return Token::create(Token::Type::integer_, std::stoll(text()), lineno(), columno()); }

{dqstring}              { 
  std::string str = text();
  std::string actual_val = str.substr(1, str.length() - 2);
  return Token::create(Token::Type::string_, actual_val, lineno(), columno()); 
}

//{symbol}                { return Token::create(Token::Type::Symbol, text(), lineno(), columno()); }
{identifier}                { return Token::create(Token::Type::identifier, text(), lineno(), columno()); }

"begin."({symbol})      {       // matcher()[1] isolates exactly what was caught in the 1st set of parentheses
   auto group1 = matcher()[1]; // matcher()[1] returns the std::pair<const char*, size_t>
  std::string symbol_text(group1.first, group1.second); // Construct the std::string safely using pointer + length
  return Token::create(Token::Type::identifier, symbol_text, lineno(), columno());
}

.                       { return Token::create(Token::Type::error, text(), lineno(), columno()); }

<<EOF>>                 { return Token::create(Token::Type::done, std::monostate{}, lineno(), columno()); }



%%
