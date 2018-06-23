#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
const int MAXN = 200010;//点数
const int MAXM = 400010;//边数,因为是无向图,所以这个值要*2
struct Edge
{
    int to,next;
    bool cut;//是否是桥标记
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN];//Belong数组的值是1~block
int Index,top;
int block;//边双连通块数
bool Instack[MAXN];
int isbridge[MAXN];
int fa[MAXN];
int bridge;//桥的数目
void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];edge[tot].cut=false;
    head[u] = tot++;
}
void Tarjan(int u,int pre)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;
        if(v == pre)continue;
        if( !DFN[v] )
        {
            fa[v]=u;
            Tarjan(v,u);
            if( Low[u] > Low[v] )Low[u] = Low[v];
            if(Low[v] > DFN[u])
            {
                bridge++;
                isbridge[v]=1;
                edge[i].cut = true;
                edge[i^1].cut = true;
            }
        }
        else if( Instack[v] && Low[u] > DFN[v] )
            Low[u] = DFN[v];
    }
}
int ans;
void LCA(int u,int v)
{
    while(DFN[u]>DFN[v])
    {
        if(isbridge[u])
        {
            ans--;
            isbridge[u]=0;
        }
        u=fa[u];
    }
    while(DFN[u]<DFN[v])
    {
        if(isbridge[v])
        {
            ans--;
            isbridge[v]=0;
        }
        v=fa[v];
    }
    while(DFN[u]>DFN[v])
    {
        if(isbridge[u])
        {
            ans--;
            isbridge[u]=0;
        }
        u=fa[u];
    }
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void solve()
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    Index = top = 0;
    bridge=0;
    Tarjan(1,0);
    ans=bridge;
    int q,a,b;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&a,&b);
        LCA(a,b);
        printf("%d\n",ans);
    }
}
int main()
{
    int n,m;
    int u,v;
    int t=0;
    while(~scanf("%d%d",&n,&m))
    {
        if(m==0&&n==0)
            break;
        printf("Case %d:\n",++t);
        init();
        while(m--)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        solve();
        printf("\n");
    }
    return 0;
}
