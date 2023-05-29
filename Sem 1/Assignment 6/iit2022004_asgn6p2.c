/*
VATSAL ASHVINBHAI BHUVA
IIT2022004
Assignment 6, Problem 2
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>

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

float power(float a, float b);
float absVal(float a);
int isPrime(int a);

int main(){
    while(1){
        float a,b;
        char op;
        printf("Enter first number: ");
        scanf("%f",&a);
        printf("Enter operation(+, -, /, *, %%, ^) or \n");
        printf("enter letters for abs and prime resp. (a, p) : ");
        scanf(" %c", &op);
        if (tolower(op) != 'a' && tolower(op)!='p'){ 
            //if absolute or prime operation entered, take only one number as input.
            printf("Enter second number: ");
            scanf("%f", &b);
        }
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
            if (b == 0){
                printf("Division by zero error.\n"); flag = 1;
            }
            if (flag == 0)
            {printf("%f / %f = %f\n",a,b,divide(a,b));}
        }
        else if(op == '%'){
            printf("%f %% %f = %d\n",a,b,modulo(a,b));
        }
        else if(op == 'a'){
            printf("Absolute value of %f is %f\n",a,absVal(a));
        }
        else if(op == 'p'){
            printf("%d\n",isPrime(a));
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
        printf("\n");
    }
    
}

float power(float a, float b){
    float pow = 1;
    for (int i = 0; i < b; i++){
        pow *= a;
    }
    return pow;
}

float absVal(float a){
    if (a < 0){
        return -1*a;
    }
    return a;
}

int isPrime(int a){
    for (int i = 2; i < sqrt(a); i++){ //check only till sqrt(a)
        if (a%i==0){
            return("%d",0);
        } 
    }
    return("%d",1);
}
