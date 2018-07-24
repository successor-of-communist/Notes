#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cmath>
#include<queue>
#include<functional>
using namespace std;
const int maxn=1e5+5;
int num[maxn],cnt[maxn];
struct node
{
    int l,r;
}ar[maxn];
bool cmp(node a,node b)
{
    if(a.l!=b.l)
        return a.l<b.l;
    return a.r>b.r;
}
int main()
{
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&ar[i].l,&ar[i].r);
        }
        sort(ar,ar+m,cmp);
        priority_queue<int,vector<int>,greater<int> > que;
        for(int i=1;i<=n;i++)
        {
            que.push(i);
        }
        memset(cnt,0,sizeof(cnt));
        memset(num,0,sizeof(num));
        cnt[0]=1;
        int pre=0;
        int k=0;
        for(int i=0;i<m;i++)
        {
            if(ar[i].l==pre)
                continue;
            if(ar[i].r<=k)
                continue;
            for(int j=pre;j<ar[i].l;j++)
            {
                if(cnt[num[j]]==0)
                {
                    que.push(num[j]);
                    cnt[num[j]]=1;
                }
            }
            if(ar[i].l>k)
            {
                for(int j=ar[i].l;j<=ar[i].r;j++)
                {
                    num[j]=que.top();
                    cnt[num[j]]=0;
                    que.pop();
                }
            }
            else
            {
                for(int j=k+1;j<=ar[i].r;j++)
                {
                    num[j]=que.top();
                    cnt[num[j]]=0;
                    que.pop();
                }
            }
            k=ar[i].r;
            pre=ar[i].l;
        }
        for(int i=1;i<=n;i++)
        {
            if(num[i]>0)
                printf("%d%c",num[i],i!=n?' ':'\n');
            else
                printf("1%c",i!=n?' ':'\n');
        }
    }
    return 0;
}
