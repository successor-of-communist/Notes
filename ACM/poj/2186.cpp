#include<iostream>
#include<string.h>
#include<stack>
#include<queue>
using namespace std;
int head[50005];
int edge[50005];
int nxt[50005];
int cnt;
stack<int>st;
void add(int u,int v)
{
    edge[cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
    cnt++;
}
int dex;
int d[10005];
int dfn[10005];
int low[10005];
bool vis[10005];
int f[10005];
void tarjan(int x)
{
    dfn[x]=low[x]=dex++;
    vis[x]=true;
    st.push(x);
    for(int i=head[x];i!=-1;i=nxt[i])
    {
        int v=edge[i];
        if(vis[v]==false)
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else
        {
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x])
    {
        while(1)
        {
            int v=st.top();
            st.pop();
            f[v]=x;
            if(v==x)
            {
                break;
            }
        }
    }
}
int main()
{
    int n,m;
    memset(nxt,-1,sizeof(nxt));
    memset(head,-1,sizeof(head));
    memset(d,0,sizeof(d));
    memset(vis,false,sizeof(vis));
    cnt=0;
    dex=0;
    cin>>n>>m;
    int a,b;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        add(a,b);
    }
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==false)
            tarjan(i);
    }
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j!=-1;j=nxt[j])
        {
            int v=edge[j];
            if(f[v]!=f[i])
            {
                d[f[i]]++;
            }
        }
    }
    int c=0;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(d[f[i]]==0)
        {
            ans++;
            if(!vis[f[i]])
            {
                c++;
            }
            vis[f[i]]=true;
        }
    }
    if(c==1)
        cout<<ans<<endl;
    else
        cout<<0<<endl;
    return 0;
}
