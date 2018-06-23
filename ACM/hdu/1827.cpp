#include<iostream>
#include<string.h>
using namespace std;
const int MAXN = 20010;//点数
const int MAXM = 100010;//边数
const int inf=1e9;
struct Edge
{
    int to,next;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1~scc
int Index,top;
int scc;//强连通分量的个数
bool Instack[MAXN];
int indeg[MAXN];
int cost[MAXN],fee[MAXN];
void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
void Tarjan(int u)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;
        if( !DFN[v] )
        {
            Tarjan(v);
            if( Low[u] > Low[v] )Low[u] = Low[v];
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u])
    {
        scc++;
        do
        {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
            cost[scc]=min(cost[scc],fee[v]);
        }
        while( v != u);
    }
}
void solve(int N)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    memset(indeg,0,sizeof(indeg));
    Index = scc = top = 0;
    for(int i = 1;i <= N;i++)
        if(!DFN[i])
            Tarjan(i);
    for(int i=1;i<=N;i++)
    {
        for(int j=head[i];j!=-1;j=edge[j].next)
        {
            int v=edge[j].to;
            if(Belong[i]!=Belong[v])
            {
                indeg[Belong[v]]++;
            }
        }
    }
    int ans=0,sumcost=0;
    for(int i=1;i<=scc;i++)
    {
        if(indeg[i]==0)
        {
            ans++;
            sumcost+=cost[i];
        }
    }
    printf("%d %d\n",ans,sumcost);
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int main(){
    int n,m,u,v;
    while(~scanf("%d%d",&n,&m))
    {
        init();
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&fee[i]);
            cost[i]=inf;
        }
        while(m--)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
        }
        solve(n);
    }
    return 0;
}
