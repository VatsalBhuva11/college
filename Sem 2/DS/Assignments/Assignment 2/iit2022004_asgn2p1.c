/*
Assignment 2 - Problem 1
Vatsal Bhuva
IIT2022004
*/
#include <stdio.h>
#include <math.h>

struct point{
    float x;
    float y;
};

float distance(struct point a, struct point b){
    float dist = sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
    return dist;
}

struct point midPoint(struct point a, struct point b){
    struct point ans;
    ans.x = (a.x+b.x)/2;
    ans.y = (a.y+b.y)/2;
    return ans;
}

int main(){
    
    struct point points[2];
    for (int i =0; i<2; i++){
        printf("Enter x coord of point %d: ",i+1);
        scanf("%f",&points[i].x);
        printf("Enter y coord of point %d: ",i+1);
        scanf("%f",&points[i].y);
    }
    printf("\n");
    printf("Distance between the points: %f\n", distance(points[0], points[1]));
    struct point ans = midPoint(points[0],points[1]);
    printf("Midpoint: (%f,%f)\n",ans.x,ans.y);
    
return 0;
}