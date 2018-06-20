#include<iostream>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
const int inf=1<<28;
int n,m;
int cnt[110][110];
int sum[110];
vector<int> vec[110];
int d[110][110];
int used[110][110][110];
struct node
{
    int u,v;
}edge[3010];
int spfa(int x,int k)
{
    int dis[110];
    bool vis[110];
    for(int i=0;i<=n;i++)
    {
        dis[i]=inf;
        vis[i]=false;
    }
    queue<int> que;
    que.push(x);
    vis[x]=true;
    dis[x]=0;
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        vis[u]=false;
        int len=vec[u].size();
        for(int i=0;i<len;i++)
        {
            int v=vec[u][i];
            int dd=d[u][v];
            if(dis[v]>dis[u]+dd)
            {
                dis[v]=dis[u]+dd;
                if(!vis[v])
                {
                    if(!k)
                        used[x][u][v]=used[x][v][u]=1;
                    que.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(dis[i]==inf)
            return inf;
        ans+=dis[i];
    }
    return ans;
}
int main(){
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<110;i++)
            vec[i].clear();
        memset(used,0,sizeof(used));
        memset(cnt,0,sizeof(cnt));
        int u,v;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            edge[i].u=u,edge[i].v=v;
            cnt[u][v]=++cnt[v][u];
            if(cnt[u][v]==1)
            {
                vec[u].push_back(v);
                vec[v].push_back(u);
                d[u][v]=d[v][u]=1;
            }
        }
        int ans=0;
        int sum[110];
        for(int i=1;i<=n;i++)
        {
            sum[i]=spfa(i,0);
            if(sum[i]==inf)
            {
                ans=inf;
                break;
            }
            ans+=sum[i];
        }
        for(int i=1;i<=m;i++)
        {
            int s=ans;
            if(ans>=inf)
            {
                printf("INF\n");
                continue;
            }
            u=edge[i].u;v=edge[i].v;
            if(cnt[u][v]>1)
            {
                printf("%d\n",ans);
            }
            else
            {
                d[u][v]=d[v][u]=inf;
                for(int j=1;j<=n;j++)
                {
                    if(used[j][u][v]==1)
                    {int tmp=spfa(j,1);
                        if(tmp==inf)
                        {
                            s=inf;
                            break;
                        }
                        s=s-sum[j]+tmp;
                    }
                }
                d[u][v]=d[v][u]=1;
                if(s>=inf)
                    printf("INF\n");
                else printf("%d\n",s);
            }
        }
    }
    return 0;
}
