#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1e3+5;
struct node
{
    int id;
    int x,y;
    double deg;
}point[maxn*3];
bool cmp(node a,node b)
{
    if(a.deg!=b.deg)
        return a.deg<b.deg;
    else
        return a.x<b.x;
}
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n*3;i++)
        {
            scanf("%d%d",&point[i].x,&point[i].y);
            point[i].id=i;
            point[i].deg=atan2(point[i].y,point[i].x);
        }
        sort(point+1,point+n*3+1,cmp);
        for(int i=1;i<=n*3;i+=3)
        {
            printf("%d %d %d\n",point[i].id,point[i+1].id,point[i+2].id);
        }
    }
    return 0;
}

