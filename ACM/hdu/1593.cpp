#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<cmath>
using namespace std;
double s[1010][1010];
bool vis[1010];
int n;
double solve(int u,int v)
{
    double d[1010];
    for(int i=1;i<=n;i++)
        d[i]=0;
    d[u]=1;
    for(int i=1;i<=n;i++)
    {
        int k=0;
        double m=0;
        for(int j=1;j<=n;j++)
            if(!vis[j]&&m<d[j])
                m=d[k=j];
        vis[k]=true;
        for(int j=1;j<=n;j++)
            d[j]=max(d[j],s[k][j]*d[k]);
    }
    return d[v];
}
int main()
{
    while(~scanf("%d",&n))
    {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%lf",&s[i][j]);
    int q;
    int u,v;
    double ans=1;
    scanf("%d",&q);
    while(q--)
    {
        memset(vis,false,sizeof(vis));
        scanf("%d%d",&u,&v);
        ans=solve(u,v);
        if(ans==0)
            printf("What a pity!\n");
        else printf("%.3lf\n",ans);
    }
    }
    return 0;
}
