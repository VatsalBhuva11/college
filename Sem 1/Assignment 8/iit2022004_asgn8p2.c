/*
VATSAL BHUVA
IIT2022004
Assignment 8 - Problem 2
*/

#include <stdio.h>
#include <math.h>

struct points {
    float x;
    float y;
};

float dist(struct points a, struct points b){
    float ans = sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2));
    return ans;
}

int main(){
    struct points coords[5];
    for (int i = 0; i<5; i++){
        printf("Enter x%d: ", i+1);
        scanf("%f", &coords[i].x);
        printf("Enter y%d: ", i+1);
        scanf("%f", &coords[i].y);
    }
    int flag = 0; float min;
    struct points ans1, ans2;
    for (int i = 0; i<5; i++){
        for (int j = i+1; j<5; j++){
            float distance = dist(coords[i], coords[j]);
            if (flag==0){
                min = distance;
                ans1 = coords[i]; ans2 = coords[j];
                flag = 1;
            }
            else{
                if (distance < min){
                    min = distance;
                    ans1 = coords[i]; ans2 = coords[j];
                }
            }
        }
    }
    printf("Minimum distance is: %f, between points (%f,%f) and (%f,%f)", min,ans1.x,ans1.y,ans2.x,ans2.y);
}