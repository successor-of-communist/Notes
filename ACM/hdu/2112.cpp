#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<cmath>
#include<string>
#include<vector>
#include<map>
using namespace std;
const int inf=1<<28;
int n;
int cnt;
struct node{
    int x,t;
    node(int xx,int tt)
    {
        x=xx;
        t=tt;
    }
};
vector<node>vec[200];
int spfa(int s,int e)
{
    int dis[200];
    bool vis[200];
    for(int i=1;i<=cnt;i++)
    {
        dis[i]=inf;
        vis[i]=false;
    }
    queue<int> que;
    que.push(s);
    vis[s]=true;
    dis[s]=0;
    while(!que.empty())
    {
        int u=que.front();
        que.pop();
        vis[u]=false;
        int len=vec[u].size();
        for(int i=0;i<len;i++)
        {
            node v=vec[u][i];
            if(dis[v.x]>dis[u]+v.t)
            {
                dis[v.x]=dis[u]+v.t;
                if(!vis[v.x])
                {
                    que.push(v.x);
                    vis[v.x]=true;
                }
            }
        }
    }
    return dis[e];
}
int main()
{
    string s,e;
    while(cin>>n)
    {
        if(n==-1)
            break;
	cnt=0;
	for(int i=0;i<200;i++)
	{
	    vec[i].clear();
	}
	map<string,int> ma;
	ma.clear();
        cin>>s>>e;
	ma[s]=++cnt;
	if(ma[e]==0)
	{
	    ma[e]=++cnt;
	}
        
        string ss,ee;
        int tt;
        for(int i=0;i<n;i++)
        {
            cin>>ss>>ee;
            cin>>tt;
            if(!ma.count(ss))
            {
                ma.insert(pair<string,int>(ss,++cnt));
            }
            if(!ma.count(ee))
            {
                ma.insert(pair<string,int>(ee,++cnt));
            }
            vec[ma[ss]].push_back(node(ma[ee],tt));
            vec[ma[ee]].push_back(node(ma[ss],tt));
        }
        int ans=spfa(ma[s],ma[e]);
        if(ans>=inf)
            printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
