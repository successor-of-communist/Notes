#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int MAXN = 1010;//点数的最大值
const int MAXM = 40010;//边数的最大值
const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow;
    int f;
}edge[MAXM],Edge[MAXM];//注意是MAXM
int tol,Tol;
int head[MAXN],Head[MAXN];
int gap[MAXN],dep[MAXN],pre[MAXN],cur[MAXN];
int deg[MAXN];
int que[MAXN];
int pos;
void init()
{
    tol = 0;
    Tol = 0;
    pos=0;
    memset(head,-1,sizeof(head));
    memset(Head,-1,sizeof(Head));
    memset(deg,0,sizeof(deg));
}
//加边,单向图三个参数,双向图四个参数
void addedge(int u,int v,int w,int rw=0)
{
    edge[tol].to=v;edge[tol].cap = w;edge[tol].next = head[u];
    edge[tol].f=1;
    edge[tol].flow=0;head[u] = tol++;
    edge[tol].to=u;edge[tol].cap = rw;edge[tol].next = head[v];
    edge[tol].f=0;
    edge[tol].flow=0;head[v]=tol++;
}
void addEdge(int u,int v)
{
    Edge[Tol].to=v;Edge[Tol].next=Head[u];
    Edge[Tol].f=1;
    Head[u]=Tol++;
}
//输入参数:起点、终点、点的总数
//点的编号没有影响,只要输入点的总数
int sap(int start,int end,int N)
{
    memset(gap,0,sizeof(gap));
    memset(dep,0,sizeof(dep));
    memcpy(cur,head,sizeof(head));
    int u = start;
    pre[u] = -1;
    gap[0] = N;
    int ans = 0;
    while(dep[start] < N)
    {
        if(u == end)
        {
            int Min = INF;
            for(int i = pre[u];i != -1; i = pre[edge[i^1].to])
                if(Min > edge[i].cap - edge[i].flow)
                    Min = edge[i].cap - edge[i].flow;
            for(int i = pre[u];i != -1; i = pre[edge[i^1].to])
            {
                edge[i].flow += Min;
                edge[i^1].flow -= Min;
            }
            u = start;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u]; i != -1;i = edge[i].next)
        {
            v = edge[i].to;
            if(edge[i].cap - edge[i].flow && dep[v]+1 == dep[u])
            {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if(flag)
        {
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != -1;i = edge[i].next)
            if(edge[i].cap - edge[i].flow && dep[edge[i].to] < Min)
            {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if(!gap[dep[u]])return ans;
        dep[u] = Min+1;
        gap[dep[u]]++;
        if(u != start) u = edge[pre[u]^1].to;
    }
    return ans;
}
void euler(int x)
{
    for(int i=Head[x];i!=-1;i=Edge[i].next)
    {
        int v=Edge[i].to;
        if(Edge[i].f==1)
        {
            Edge[i].f=0;
            euler(v);
            que[pos++]=v;
        }
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)
    {
        init();
        int n,m;
        scanf("%d%d",&n,&m);
        int a,b;
        int s=0,e=n+1;
        char ch;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d %c",&a,&b,&ch);
            deg[a]++;
            deg[b]--;
            if(ch=='U')
            {
                addedge(a,b,1);
            }
            else
            {
                addEdge(a,b);
            }
        }
        bool flag=false;
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            if(deg[i]%2!=0)
            {
                flag=true;
                break;
            }
            if(deg[i]>0)
            {
                sum+=deg[i]/2;
                addedge(s,i,deg[i]/2);
            }
            if(deg[i]<0)
            {
                addedge(i,e,-deg[i]/2);
            }
        }
        if(flag||sap(s,e,n+2)!=sum)
        {
            printf("No euler circuit exist\n");
        }
        else
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=head[i];j!=-1;j=edge[j].next)
                {
                    int v=edge[j].to;
                    if(v==s||v==e||edge[j].f==0)
                        continue;
                    if(edge[j].flow>0)
                        addEdge(v,i);
                    else
                        addEdge(i,v);
                }
            }
            euler(1);
            printf("1");
            for(int i=pos-1;i>=0;i--)
            {
                printf(" %d",que[i]);
            }
            printf("\n");
        }
        if(t)
            printf("\n");
    }
    return 0;
}
