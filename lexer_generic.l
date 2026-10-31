// --- Named Definitions Section --- 
dseq            ([[:digit:]]+)
dseq_opt        ({dseq}?)
frac            (({dseq_opt}"."{dseq})|{dseq}".")
exp             ([eE][+-]?{dseq})
exp_opt         ({exp}?)
integer_         ({dseq})
float_           (({frac}{exp_opt})|({dseq}{exp}))

blank           [ \t\r]           
dqstring        \"([^"\\]|\\.|\\n|\n)*\"


/* 1. First character MUST be a letter or underscore (Ruby style) */
sym_start       [a-zA-Z_]

/* 2. Subsequent characters can be letters, digits, underscores, or special symbols */
sym_rest        [a-zA-Z0-9+\-*/=<>!?_]

/* 3. Combine them: one start character followed by zero or more rest characters */
identifier          {sym_start}{sym_rest}*


//identifier_an      ([a-zA-Z][a-zA-Z0-9_]*)



//lc_identifier   ([a-z_][a-z0-9_]*)
//cap             ([A-Z_])
