
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
integer         ({dseq})
float           (({frac}{exp_opt})|({dseq}{exp}))

blank           [ \t\r]           
dqstring        \"([^"\\]|\\.|\\n|\n)*\"

sym_char        [a-zA-Z0-9+\-*/=<>!?_]
symbol          [a-zA-Z+\-*/=<>!?_]{sym_char}*

%%

{blank}+                { /* Skip spaces, tabs, carriage returns */ }
\n+                     { /* Skip standalone newlines */ }
";".*                   { /* Skip line comments */ }

//"("                     { return Loosh::Token::create(Token::Type::Lparen, std::monostate{}, lineno(), columno()); }
"("                     { return Loosh::Token::create(Token::Type::Lparen, 0, lineno(), columno()); }

/*
")"                     { return LSHLexer::Token{LSHLexer::TokenType::RParen, std::monostate{}, lineno(), columno()}; }

{float}                 { return LSHLexer::Token{LSHLexer::TokenType::Float,   std::stod(text()),  lineno(), columno()}; }
{integer}               { return LSHLexer::Token{LSHLexer::TokenType::Integer, std::stoll(text()), lineno(), columno()}; }

{dqstring}              { 
                            std::string str = text();
                            std::string actual_val = str.substr(1, str.length() - 2);
                            return LSHLexer::Token{LSHLexer::TokenType::String, actual_val, lineno(), columno()}; 
                        }

{symbol}                { return LSHLexer::Token{LSHLexer::TokenType::Symbol, text(), lineno(), columno()}; }

.                       { return LSHLexer::Token{LSHLexer::TokenType::Error, text(), lineno(), columno()}; }

<<EOF>>                 { return LSHLexer::Token{LSHLexer::TokenType::End, std::monostate{}, lineno(), columno()}; }

%%
 */
/*

"begin."({symbol})   {
                        // matcher()[1] isolates exactly what was caught in the 1st set of parentheses
                        std::string symbol_text = matcher()[1]; 
                        
                        return LSHLexer::Token{LSHLexer::Token::Type::Symbol, symbol_text, lineno(), columno()};
                     }

*/
