#include<iostream>
#include<string.h>
#include<stack>
using namespace std;
struct node
{
    int v,nxt;
}edge[10010];
int head[110];
int cnt;
int dfn[110],low[110];
stack<int> st;
int dex;
bool vis[110];
int f[110];
int dc[110],dr[110];
int scc;
void tarjan(int x)
{
    dfn[x]=low[x]=++dex;
    vis[x]=true;
    st.push(x);
    for(int i=head[x];i!=-1;i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])
        {
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x])
    {
        scc++;
        while(1)
        {
            int v=st.top();
            st.pop();
            f[v]=scc;
            vis[v]=false;
            if(v==x)
                break;
        }
    }
}
void add1(int u,int v)
{
    edge[cnt].v=v;
    edge[cnt].nxt=head[u];
    head[u]=cnt++;
}
int main(){
    int n;
    dex=0;
    cnt=0;
    scc=0;
    memset(head,-1,sizeof(head));
    memset(edge,-1,sizeof(edge));
    memset(dc,0,sizeof(dc));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(dr,0,sizeof(dr));
    memset(vis,false,sizeof(vis));
    cin>>n;
    int b;
    for(int i=1;i<=n;i++)
    {
        while(cin>>b)
        {
            if(b==0)
                break;
            add1(i,b);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])
            tarjan(i);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j!=-1;j=edge[j].nxt)
        {
            int v=edge[j].v;
            if(f[i]!=f[v])
            {
                dc[f[i]]++;
                dr[f[v]]++;
            }
        }
    }
    int ansn=0,ansm=0;
    for(int i=1;i<=scc;i++)
    {
        if(dc[i]==0)
            ansm++;
        if(dr[i]==0)
            ansn++;
    }
    if(scc==1)
    {
        cout<<1<<endl<<0<<endl;
    }
    else
    {
        cout<<ansn<<endl;
        cout<<max(ansn,ansm)<<endl;
    }
    return 0;
}
