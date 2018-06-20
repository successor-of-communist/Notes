#include<iostream>
#include<string.h>
using namespace std;
const int maxn=1e4+5;
const int maxm=1e5+5;
struct node
{
    int v,nxt;
}edge[maxm];
int cnt;
int head[maxn];
int dfn[maxn],low[maxn];
int st[maxn];
int pos;
bool vis[maxn];
int dex;
int scc;
int f[maxn];
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
        if(vis[v]==false)
        {
            tarjan(v);
            low[x]=min(low[v],low[x]);
        }
        else
        {
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(low[x]==dfn[x])
    {
        scc++;
        do{
            int v=st[--pos];
            f[v]=scc;
            if(x==v)
                break;
        }while(1);
    }
}
int main(){
    int n,m;
    int a,b;
    while(cin>>n>>m)
    {
        if(n==0&&m==0)
            break;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(head,-1,sizeof(head));
        memset(edge,-1,sizeof(edge));
        memset(vis,false,sizeof(vis));
        cnt=0;
        dex=0;
        pos=0;
        scc=0;
        for(int i=0;i<m;i++)
        {
            cin>>a>>b;
            add(a,b);
        }
        for(int i=1;i<=n;i++)
        {
            if(dfn[i]==0)
            {
                tarjan(i);
            }
        }
        if(scc==1)
            cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
