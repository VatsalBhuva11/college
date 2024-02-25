%{
%}

%%

[a-zA-Z_]+ {printf("Valid identifier\n")}
.+ {printf("Invalid identifier\n");}
\n {return 0;}

%%

yywrap() {}

int main(){
    printf("Enter string: ");

    yylex();

    return 0;
}
