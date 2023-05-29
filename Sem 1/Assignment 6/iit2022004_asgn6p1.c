/*
VATSAL ASHVINBHAI BHUVA
IIT2022004
Assignment 6, Problem 1
*/

#include <stdio.h>
#include <ctype.h>

float add(float a, float b){
    return a+b;
}
float subtract(float a, float b){
    return a-b;
}
float multiply(float a, float b){
    return a*b;
}
float divide(float a, float b){
    return a/b;
}
int modulo(int a, int b){
    return a%b;
}

int main(){
    while(1){
        float a,b;
        char op;
        printf("Enter first number: ");
        scanf("%f",&a); //first number as input
        printf("Enter operation(+, -, /, *, %%) : ");
        scanf(" %c", &op);
        printf("Enter second number: ");
        scanf("%f", &b); //second number as input
        if (op == '+'){
            printf("%f + %f = %f\n",a,b,add(a,b));
        }
        else if(op == '-'){
            printf("%f - %f = %f\n",a,b,subtract(a,b));
        }
        else if(op == '*'){
            printf("%f * %f = %f\n",a,b,multiply(a,b));
        }
        else if(op == '/'){
            int flag = 0;
            if (b == 0){ //checking if denominator is 0.
                printf("Division by zero error.\n"); flag = 1;
            }
            if (flag == 0)
            {printf("%f / %f = %f\n",a,b,divide(a,b));}
        }
        else if(op == '%'){
            printf("%f %% %f = %d\n",a,b,modulo(a,b));
        }
        else{
            printf("Invalid operation.\n");
        }
        char choice;
        printf("Would you like to continue? (y/n) : ");
        scanf(" %c", &choice);
        if (tolower(choice) == 'n'){
            break;
        }
    }
    
}