%{

// make one for decimals, signed
// date token

#include <stdio.h>
#include "y.tab.h"
%}

%%	
(false)|(true)|(null)			yylval=strdup(yytext); return BOOL;
[0-9][0-9][0-9].X			yylval=strdup(yytext); return ADDR;
:            				return DICT;
\(					return OPAREN;
\)					return EPAREN;
-*[0-9]+(\.[0-9]+)?			yylval=strdup(yytext); return NUM;
[a-zA-Z0-9][\_a-zA-Z0-9\$&:\/\.-]*	yylval=strdup(yytext); return WORD;
\{\\n\}					return EMPTYSET;
\"            				return QUOTE;
\{            				return OBRACE;
\}            				return EBRACE;
\[            				return OBOX;
\]            				return EBOX;
\n            				/* ignore EOL */
[ \t]+            			/* ignore whitespace */
,            				/* ignore comma */
-					/* ignore space sep dash */
\/					/* ignore space sep slash */
&					/* ignore space sep ampersand */
%%
