#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
const int MAXN = 100010;//点数的最大值
const int MAXM = 400010;//边数的最大值
const int INF = 0x3f3f3f3f;
struct Edge
{
    int to,next,cap,flow;
}edge[MAXM];//注意是MAXM
int tol;
int head[MAXN];
int gap[MAXN],dep[MAXN],pre[MAXN],cur[MAXN];
void init()
{
    tol = 0;
    memset(head,-1,sizeof(head));
}
//加边,单向图三个参数,双向图四个参数
void addedge(int u,int v,int w,int rw=0)
{
    edge[tol].to =v;edge[tol].cap = w;edge[tol].next = head[u];
    edge[tol].flow= 0;head[u] = tol++;
    edge[tol].to =u;edge[tol].cap = rw;edge[tol].next = head[v];
    edge[tol].flow= 0;head[v]=tol++;
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
int main()
{
    int t;
    int r,c,count=0;
    int start,end;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d%d",&r,&c);
        start=0;
        end=r+c+1;
        int tmp,pre=0;
        for(int i=1;i<=r;i++)
        {
            scanf("%d",&tmp);
            addedge(start,i,tmp-pre-c);
            pre=tmp;
        }
        pre=0;
        for(int i=1;i<=c;i++)
        {
            scanf("%d",&tmp);
            addedge(i+r,end,tmp-pre-r);
            pre=tmp;
        }
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                addedge(i,j+r,19);
        sap(start,end,end+1);
        int ans[105][105];
        for(int i=1;i<=r;i++)
        {
            for(int j=head[i];j!=-1;j=edge[j].next)
            {
                int v=edge[j].to;
                if(v>r&&v<=r+c)
                {
                    ans[i][v-r]=edge[j].flow;
                }
            }
        }
        printf("Matrix %d\n",++count);
        for(int i=1;i<=r;i++)
        {
            for(int j=1;j<=c;j++)
            {
                printf("%d%c",ans[i][j]+1,j==c?'\n':' ');
            }
        }
    }
    return 0;
}
