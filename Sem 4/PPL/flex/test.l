%{
    int count = 0;
%}

/* rules */

/* valid identifier (first char is lowercase/uppercase/underscore, etc.) */
%%
[a-zA-Z]+ {printf("Valid identifier\n"); count=yyleng;}
    /*.+ to match a string of invalid characters*/
.+ {printf("Invalid identifier\n");}
\n {return 0;}

%%

yywrap() {}

int main(){
    printf("Enter string: ");

    //The function yylex() is the main flex function that runs the Rule Section and 
    //extension (.l) is the extension used to save the programs.
    yylex();
    printf("Count: %d\n", count);

    // count if single char regex (so that the regex runs for every char)
    // printf("%d matched characters", count);
    return 0;
}


/*

- Here’s what’s happening inside the scanner. Lex reads the 
regexes and generates a state machine to consume input. Below 
is a visualization of the states, with transitions labeled by input 
character. The circles with a double outline indicate states that trigger actions.

- Now’s a good time to take a detour and observe how our user-defined code acts in the generated C file. Lex creates a function called yylex(), 
and inserts the code blocks verbatim into a switch statement. When using lex with a parser, the parser will call yylex() to retrieve tokens, named by integers. For now, our 
user-defined code isn’t returning tokens to a parser, but doing simple print statements.

- 

*/