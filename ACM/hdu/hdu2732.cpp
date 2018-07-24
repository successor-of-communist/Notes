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
    edge[tol].to = u;edge[tol].cap = rw;edge[tol].next = head[v];
    edge[tol].flow = 0;head[v]=tol++;
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
int dir[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
int n,m,d;
void dfs(int i,int j,int c,int oi,int oj,int val,int ed)
{
    if(c>d)
        return;
    for(int l=0;l<4;l++)
    {
        int ii=i+dir[l][0],jj=j+dir[l][1];
        if(ii>=0&&ii<n&&jj>=0&&jj<m)
        {
            addedge(oi*m+oj+1+n*m,ii*m+jj+1,INF);
            dfs(ii,jj,c+1,oi,oj,val,ed);
        }
        else
        {
            addedge(oi*m+oj+1+n*m,ed,val);
        }
    }
}
int main(){
    int t;
    scanf("%d",&t);
    for(int k=1;k<=t;k++)
    {
        init();
        int st=0,ed=801;
        scanf("%d%d",&n,&d);
        char str[30];
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            m=strlen(str);
            for(int j=0;j<m;j++)
            {
                int val=str[j]-'0';
                addedge(i*m+j+1,i*m+j+n*m+1,val);
                dfs(i,j,1,i,j,val,ed);
            }
        }
        int sum=0;
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            for(int j=0;j<m;j++)
            {
                if(str[j]=='L')
                {
                    addedge(st,i*m+j+1,1);
                    sum++;
                }
            }
        }
        int ans=sap(st,ed,n*m*2+2);
        if(sum-ans==0)
            printf("Case #%d: no lizard was left behind.\n",k);
        else if(sum-ans==1)
            printf("Case #%d: 1 lizard was left behind.\n",k);
        else
            printf("Case #%d: %d lizards were left behind.\n",k,sum-ans);
    }
    return 0;
}
