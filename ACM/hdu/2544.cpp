#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#include<queue>
using namespace std;
int n,m;
const int inf=1<<28;
struct node
{
	int v;
	int l;
	node(int vv,int ll)
	{
		v=vv;
		l=ll;
	}
};
vector<node> vec[110];
int spfa()
{
	queue<int> que;
	bool vis[110];
	int dis[110];
	memset(vis,false,sizeof(vis));
	for(int i=0;i<=n;i++)
		dis[i]=inf;
	que.push(1);
	dis[1]=0;
	vis[1]=true;
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		vis[u]=false;
		int len=vec[u].size();
		for(int i=0;i<len;i++)
		{
			node t=vec[u][i];
			if(dis[t.v]>dis[u]+t.l)
			{
				dis[t.v]=dis[u]+t.l;
				if(!vis[t.v])
				{
					vis[t.v]=true;
					que.push(t.v);
				}
			}
		}
	}
	return dis[n];
}
int main(){
	while(cin>>n>>m)
	{
		if(n==0&&m==0)
			break;
		for(int i=0;i<=n;i++)
			vec[i].clear();
		int a,b,c;
		for(int i=0;i<m;i++)
		{
			cin>>a>>b>>c;
			vec[a].push_back(node(b,c));
			vec[b].push_back(node(a,c));
		}
		cout<<spfa()<<endl;
	}
	return 0;
}
