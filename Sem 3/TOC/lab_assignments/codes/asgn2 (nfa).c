//1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


int main()
{

    char s[100];
    scanf("%s",s);
  
    int init_st = 0;

      int j = 0;
    while(s[j] != '\0')
    {
        if(init_st == 0 && s[0] == 'a')
            init_st = 1;
        else if(init_st == 0 && s[1] == 'b')
            init_st = 2;
        else if(init_st == 2 && s[j] == 'a')
            init_st = 3;
        else if(init_st == 3 && s[j] == 'b')
            init_st = 2;
        else if(init_st == 3 && s[j] == 'a')
            init_st = 1;
        j++;
    }
    if(init_st == 3)
    printf(" yes ,string is Accepted\n");
    else
    printf("no,string is Rejected");
    
    return 0;
}

//2
/*
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main()
{
    char * s;
    scanf("%s",s);
    
    int init_st = 0;
    int j = 0;
    while(s[j] != '\0')
    {
        if(init_st == 0)
        {
            if(s[j] == 'a')
                init_st = 1;
            else if(s[j] == 'b')
                init_st = 2;
        }
        else if( (s[j+1] == '\0') && (init_st == 1 || init_st == 2) )
        {
            if(init_st == 1 && s[j] == 'a')
                init_st = 3;
            else if(init_st == 2 && s[j] == 'b')
                init_st = 3;
        }
        j++;
    }
    if(init_st == 3 || j == 1)
    printf("yes,string is accepted\n");
    else
    printf("no,string is  rejected ");

    return 0;
}
*/