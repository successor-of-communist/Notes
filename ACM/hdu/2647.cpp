#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<queue>
using namespace std;
int n,m;
vector<int> vec[10010];
int d[10010];
int dis[10010];
void solve()
{
    queue<int> que;
    for(int i=1;i<=n;i++)
    {
        if(d[i]==0)
            que.push(i);
        dis[i]=-1;
    }
    int tmp=888;
    while(!que.empty())
    {
        int len=que.size();
        while(len--)
        {
            int u=que.front();
            que.pop();
            dis[u]=tmp;
            int usize=vec[u].size();
            for(int i=0;i<usize;i++)
            {
                int v=vec[u][i];
                d[v]--;
                if(d[v]==0)
                    que.push(v);
            }
        }
        tmp++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=dis[i];
        if(dis[i]==-1)
        {
            ans=-1;
            break;
        }
    }
    cout<<ans<<endl;
}
int main(){
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<=n;i++)
            vec[i].clear();
        memset(d,0,sizeof(d));
        int a,b;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&a,&b);
            vec[b].push_back(a);
            d[a]++;
        }
        solve();
    }
    return 0;
}
