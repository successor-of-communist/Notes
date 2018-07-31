#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
const int maxn=1e3+5;
const int maxm=1e5+5;
struct Edge{
    int u,v,cost;
}edge[maxm];
int pre[maxn],id[maxn],visit[maxn],in[maxn];
int pos;
ll zhuliu(int root,int n,int m){
    ll res=0,u,v;
    while(1){
        for(int i=0;i<n;i++)
            in[i]=inf;
        for(int i=0;i<m;i++)
            if(edge[i].u!=edge[i].v&&edge[i].cost<in[edge[i].v]){
                pre[edge[i].v]=edge[i].u;
                in[edge[i].v]=edge[i].cost;
                if(edge[i].u==root)
                    pos=i;            //不定根位置
            }
        for(int i=0;i<n;i++)
            if(i!=root&&in[i]==inf)
                return -1;
        int tn=0;
        memset(id,-1,sizeof(id));
        memset(visit,-1,sizeof(visit));
        in[root]=0;
        for(int i=0;i<n;i++){
            res+=in[i];
            v=i;
            while(visit[v]!=i&&id[v]==-1&&v!=root){
                visit[v]=i;
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
        for(int i=0;i<m;i++){
            v=edge[i].v;
            edge[i].u=id[edge[i].u];
            edge[i].v=id[edge[i].v];
            if(edge[i].u!=edge[i].v)
                edge[i].cost-=in[v];
        }
        n=tn;
        root=id[root];
    }
    return res;
}
int main(){
    int n,m;
    int u,v,cost;
    ll sum;
    while(~scanf("%d%d",&n,&m)){
        sum=0;
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&u,&v,&cost);
            edge[i].u=u;
            edge[i].v=v;
            edge[i].cost=cost;
            sum+=cost;
        }
        sum++;                //大于总和
        for(int i=m;i<m+n;i++){
            edge[i].u=n;
            edge[i].v=i-m;
            edge[i].cost=sum;
        }
        ll ans=zhuliu(n,n+1,n+m);
        if(ans==-1||ans-sum>=sum){
            printf("impossible\n");
        }
        else
            printf("%lld %d\n",ans-sum,pos-m);
        printf("\n");
    }
    return 0;
}
