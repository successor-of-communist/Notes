#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1e2+5;
const int maxm=1e4+5;
struct Edge{
    int u,v;
    double cost;
}edge[maxm];
double cx[maxn],cy[maxn];
int pre[maxn],id[maxn],visited[maxn];
double in[maxn];
double zhuliu(int root,int n,int m)
{
    double res=0;
    int u,v;
    while(1){
        for(int i=0;i<n;i++){
            in[i]=inf;
        }
        for(int i=0;i<m;i++){
            if(edge[i].u!=edge[i].v&&edge[i].cost<in[edge[i].v]){
                pre[edge[i].v]=edge[i].u;
                in[edge[i].v]=edge[i].cost;
            }
        }
        for(int i=0;i<n;i++)
            if(i!=root&&in[i]==inf)
                return -1;
        int tn=0;
        memset(id,-1,sizeof(id));
        memset(visited,-1,sizeof(visited));
        in[root]=0;
        for(int i=0;i<n;i++){
            res+=in[i];
            v=i;
            while(visited[v]!=i&&id[v]==-1&&v!=root){
                visited[v]=i;
                v=pre[v];
            }
            if(v!=root&&id[v]==-1){
                for(u=pre[v];u!=v;u=pre[u])
                    id[u]=tn;
                id[v]=tn++;
            }
        }
        if(tn==0)
            break;
        for(int i=0;i<n;i++)
            if(id[i]==-1)
                id[i]=tn++;
        for(int i=0;i<m;){
            v=edge[i].v;
            edge[i].u=id[edge[i].u];
            edge[i].v=id[edge[i].v];
            if(edge[i].u!=edge[i].v)
                edge[i++].cost-=in[v];
            else
                swap(edge[i],edge[--m]);
        }
        n=tn;
        root=id[root];
    }
    return res;
}
double g[maxn][maxn];
int main(){
    int n,m;
    while(~scanf("%d%d",&n,&m)){
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                g[i][j]=inf;
        int u,v;
        int L=0;
        for(int i=0;i<n;i++){
            scanf("%lf%lf",&cx[i],&cy[i]);
        }
        for(int i=0;i<m;i++){
            scanf("%d%d",&u,&v);
            u--;
            v--;
            if(u==v)
                continue;
            double dis=sqrt((cx[u]-cx[v])*(cx[u]-cx[v])*1.0+(cy[u]-cy[v])*(cy[u]-cy[v])*1.0);
            g[u][v]=min(g[u][v],dis);
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(g[i][j]<inf){
                    edge[L].u=i;
                    edge[L].v=j;
                    edge[L].cost=g[i][j];
                    L++;
                }
        double ans=zhuliu(0,n,L);
        if(ans==-1)
            printf("poor snoopy\n");
        else
            printf("%.2f\n",ans);
    }
    return 0;
}
