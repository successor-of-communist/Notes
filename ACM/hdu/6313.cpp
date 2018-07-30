#include<iostream>
#include<stdio.h>
using namespace std;
const int maxn=47*47+5;
int a[maxn][maxn];
int main(){
    int n=47;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                a[i*n+j][k*n+(k*j+i)%n]=1;
            }
        }
    }
    printf("2000\n");
    for(int i=0;i<2000;i++)
    {
        for(int j=0;j<2000;j++)
        {
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
