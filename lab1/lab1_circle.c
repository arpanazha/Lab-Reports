#include<stdio.h>
#define pi 3.147

int main(){
    int radius;
    float area;
    printf("enter the radius of the circle");
    scanf("%d",&radius);
    area = pi * radius *radius;
    printf("the area of the circle is %f",area);
}