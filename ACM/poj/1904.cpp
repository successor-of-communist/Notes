#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=4005;
const int maxm=300005;
struct node
{
    int v,nxt;
}edge[maxm];
int head[maxn];
int cnt;
int dfn[maxn],low[maxn],st[maxn],f[maxn];
int dex,pos,scc;
bool vis[maxn];
int n;
void add(int u,int v)
{
    edge[cnt].v=v;
    edge[cnt].nxt=head[u];
    head[u]=cnt++;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++dex;
    vis[x]=1;
    st[pos++]=x;
    for(int i=head[x];i!=-1;i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])
            low[x]=min(low[x],dfn[v]);
    }
    if(dfn[x]==low[x])
    {
        scc++;
        while(1)
        {
            int v=st[--pos];
            f[v]=scc;
            vis[v]=0;
            if(x==v)
                break;
        }
    }
}
int main(){
    while(~scanf("%d",&n))
    {
        cnt=dex=scc=pos=0;
        memset(head,-1,sizeof(head));
        memset(edge,-1,sizeof(edge));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(f,0,sizeof(f));
        memset(vis,false,sizeof(vis));
        int k,m;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&m);
            while(m--)
            {
                scanf("%d",&k);
                add(i+1,n+k);
            }
        }
        for(int i=0;i<n;i++)
        {
            scanf("%d",&k);
            add(n+k,i+1);
        }
        for(int i=1;i<=n+n;i++)
        {
            if(!dfn[i])
                tarjan(i);
        }
        int ans[maxn];
        int c=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=head[i];j!=-1;j=edge[j].nxt)
            {
                int v=edge[j].v;
                if(f[v]==f[i])
                {
                    ans[c++]=v-n;
                }
            }
            sort(ans,ans+c);
            printf("%d",c);
            for(int j=0;j<c;j++)
            {
                printf(" %d",ans[j]);
            }
            printf("\n");
            c=0;
        }
    }
    return 0;
}
