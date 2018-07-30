#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<string.h>
#include<bitset>
using namespace std;
const int MAXN = 2010;
const int MAXM = 2000010;
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
    int n,m;
    while(~scanf("%d",&n))
    {
        scanf("%d",&m);
        init();
        int a,b,u,v;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d%d",&a,&b,&u,&v);
            addedge(a*2+u,b*2+(v^1));
            addedge(b*2+v,a*2+(u^1));
        }
        if(solvable(2*n))
        {
            printf("YES\n");
        }
        else
            printf("NO\n");
    }
    return 0;
}

