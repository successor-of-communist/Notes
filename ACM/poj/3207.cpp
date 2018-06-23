#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
const int MAXN = 20020;
const int MAXM = 200010;
struct Edge
{
    int to,next;
}edge[MAXM];
int head[MAXM],tot;
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
bool vis[MAXN];//染色标记,为true表示选择
int S[MAXN],top;//栈
bool dfs(int u)
{
    if(vis[u^1])return false;
    if(vis[u])return true;
    vis[u] = true;
    S[top++] = u;
    for(int i = head[u];i != -1;i = edge[i].next)
        if(!dfs(edge[i].to))
            return false;
    return true;
}
bool Twosat(int n)
{
    memset(vis,false,sizeof(vis));
    for(int i = 0;i < n;i += 2)
    {
        if(vis[i] || vis[i^1])continue;
        top = 0;
        if(!dfs(i))
        {
            while(top)vis[S[--top]] = false;
            if(!dfs(i^1)) return false;
        }
    }
    return true;
}
int main()
{
    int n,m;
    int u,v;
    while(~scanf("%d%d",&n,&m))
    {
        init();
        int a[MAXN],b[MAXN];
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            a[i]=min(u,v);
            b[i]=max(u,v);
        }
        for(int i=0;i<m;i++)
        {
            for(int j=i+1;j<m;j++)
            {
                if((a[i]<=a[j]&&b[i]>=a[j]&&b[i]<=b[j])||(a[i]>=a[j]&&a[i]<=b[j]&&b[i]>=b[j]))
                {
                    u=i*2;
                    v=j*2;
                    addedge(u,v+1);
                    addedge(u+1,v);
                    addedge(v,u+1);
                    addedge(v+1,u);
                }
            }
        }
        if(Twosat(2*m))
        {
            printf("panda is telling the truth...\n");
        }
        else printf("the evil panda is lying again\n");
    }
    return 0;
}
