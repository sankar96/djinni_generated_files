%{
    #include "tokens.h"
%}

relative-row-reference ([1-9]|[1-8][0-9]|9[0-9]|[1-8][0-9]{2}|9[0-8][0-9]|99[0-9]|[1-8][0-9]{3}|9[0-8][0-9]{2}|99[0-8][0-9]|999[0-9]|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-6])
relative-column-reference [a-hA-H][a-zA-Z]|[A-Za-z]|[i][a-vA-V]
absolute-row-reference ($){relative-row-reference}
absolute-column-reference ($){relative-column-reference}
row-reference {absolute-row-reference}|{relative-row-reference}
column-reference {absolute-column-reference}|{relative-column-reference}
cell-reference {column-reference}{row-reference}
defined-name ([A-Za-z_]([A-Za-z0-9]*))

%option noyywrap
%%

"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
{cell-reference} {return CELLREFERENCE;}
([0-9]+([\.][0-9]*)?|[\.][0-9]+)([Ee][0-9]+)?       {return NUMBER;} 


%%

void* setUpBuffer(char const* text)
{
    YY_BUFFER_STATE buffer  = yy_scan_string(text);
    yy_switch_to_buffer(buffer);
    return buffer;
}

void tearDownBuffer(void* buffer)
{
    yy_delete_buffer((YY_BUFFER_STATE)buffer);
}