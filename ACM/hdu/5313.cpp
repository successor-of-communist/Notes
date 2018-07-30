#include<iostream>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<bitset>
using namespace std;
const int MAXN=1e4+5;
const int MAXM=2e5+5;
int head[MAXN],edge[MAXM],nxt[MAXM];
int tot,cou;
bool vis[MAXN];
int cnt[MAXN][2];
bitset<MAXN> bit;
void addedge(int u,int v)
{
    edge[tot]=v;
    nxt[tot]=head[u];
    head[u]=tot++;
    edge[tot]=u;
    nxt[tot]=head[v];
    head[v]=tot++;
}
void dfs(int u,int pos)
{
    cnt[cou][pos]++;
    vis[u]=true;
    for(int i=head[u];i!=-1;i=nxt[i])
    {
        int v=edge[i];
        if(!vis[v])
            dfs(v,pos^1);
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(head,-1,sizeof(head));
        memset(vis,false,sizeof(vis));
        memset(cnt,0,sizeof(cnt));
        tot=cou=0;
        int n,m,u,v;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
        }
        for(int i=1;i<=n;i++)
        {
            if(!vis[i])
            {
                dfs(i,0);
                cou++;
            }
        }
        bit[0]=1;
        for(int i=0;i<cou;i++)
        {
            bit=bit<<cnt[i][0]|bit<<cnt[i][1];
        }
        int ans=0;
        for(int i=n/2;i>=0;i++)
        {
            if(bit[i])
            {
                ans=i;
                break;
            }
        }
        printf("%d\n",ans*(n-ans)-m);
    }
    return 0;
}
