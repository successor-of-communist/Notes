#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<bitset>
using namespace std;
const int MAXN = 2010;
const int MAXM = 200010;
struct Edge
{
    int to,next;
}edge[MAXM];
int head[MAXN],tot;
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    edge[tot].to = v; edge[tot].next = head[u]; head[u] = tot++;
}
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值1~scc
int Index,top;
int scc;
bool Instack[MAXN];
int num[MAXN];
int cx[MAXN],cy[MAXN];
double dis[MAXN][MAXN];
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
            if(Low[u] > Low[v])Low[u] = Low[v];
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
            num[scc]++;
        }
        while(v != u);
    }
}
bool solvable(int n)//n是总个数,需要选择一半
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    memset(num,0,sizeof(num));
    Index = scc = top = 0;
    for(int i = 0;i < n;i++)
        if(!DFN[i])
            Tarjan(i);
    for(int i = 0;i < n;i += 2)
    {
        if(Belong[i] == Belong[i^1])
            return false;
    }
    return true;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&cx[i*2],&cy[i*2]);
            scanf("%d%d",&cx[i*2+1],&cy[i*2+1]);
        }
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                dis[j*2][i*2]=dis[i*2][j*2]=sqrt(pow(cx[i*2]-cx[j*2],2)+pow(cy[i*2]-cy[j*2],2));
                dis[j*2+1][i*2]=dis[i*2][j*2+1]=sqrt(pow(cx[i*2]-cx[j*2+1],2)+pow(cy[i*2]-cy[j*2+1],2));
                dis[j*2][i*2+1]=dis[i*2+1][j*2]=sqrt(pow(cx[i*2+1]-cx[j*2],2)+pow(cy[i*2+1]-cy[j*2],2));
                dis[j*2+1][i*2+1]=dis[i*2+1][j*2+1]=sqrt(pow(cx[i*2+1]-cx[j*2+1],2)+pow(cy[i*2+1]-cy[j*2+1],2));
            }
        }
        double l=0,r=40000;
        while(r-l>0.001)
        {
            double mid=(l+r)/2.0;
            init();
            for(int i=0;i<n*2;i+=2)
                for(int j=i+2;j<n*2;j++)
                {
                    if(dis[i][j]<mid)
                    {
                        addedge(i,j^1);
                        addedge(j,i+1);
                    }
                    if(dis[i+1][j]<mid)
                    {
                        addedge(i+1,j^1);
                        addedge(j,i);
                    }
                }
            if(solvable(n*2))
                l=mid;
            else
                r=mid;
        }
        printf("%.2lf\n",l/2.0);
    }
    return 0;
}
