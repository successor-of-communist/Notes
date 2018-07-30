#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn=1e5+100;
int b[maxn];
struct Node
{
    ll sum_zero;
    int minval,lazy,ominval;
}ans[maxn<<2];
int nn;
void pushup(int rt)
{
    ans[rt].sum_zero=ans[rt<<1].sum_zero+ans[rt<<1|1].sum_zero;
    ans[rt].minval=min(ans[rt<<1].minval,ans[rt<<1|1].minval);
}
void build(int l,int r,int rt)
{
    ans[rt].lazy=0;
	ans[rt].sum_zero=0;
	if(l==r)
	{
        ans[rt].minval=b[l];
        ans[rt].ominval=b[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pushup(rt);
}
void pushdown(int rt)//ln表示左子树元素节点的个数，rn表示右子树元素节点的个数
{
	if(ans[rt].lazy>0)
    {
        ans[rt<<1].lazy+=ans[rt].lazy;
        ans[rt<<1|1].lazy+=ans[rt].lazy;
        ans[rt<<1].minval-=ans[rt].lazy;
        ans[rt<<1|1].minval-=ans[rt].lazy;
        ans[rt].lazy=0;
    }
}
//区间更新
void range_update(int l,int r,int c,int L,int R,int rt)
{
    if(l<=L&&R<=r)
    {
        if(ans[rt].minval>1)
        {
            ans[rt].lazy+=c;
            ans[rt].minval-=c;
            return;
        }
    }
    if(L==R&&ans[rt].minval==1)
    {
        ans[rt].minval=ans[rt].ominval;
        ans[rt].lazy=0;
        ans[rt].sum_zero++;
        return;
    }
    int mid=(L+R)>>1;
    pushdown(rt);
    if(l<=mid)
        range_update(l,r,c,L,mid,rt<<1);
    if(r>mid)
        range_update(l,r,c,mid+1,R,rt<<1|1);
    pushup(rt);
}
//区间查询
ll range_query(int l,int r,int L,int R,int rt)
{
    if(l<=L&&R<=r)
    {
        return ans[rt].sum_zero;
    }
    //if(ans[rt].minval<=0)
    //    range_update(l,r,1,1,nn,1);
    int mid=(L+R)>>1;
    pushdown(rt);
    ll ANS=0;
    if(l<=mid)
        ANS+=range_query(l,r,L,mid,rt<<1);
    if(r>mid)
        ANS+=range_query(l,r,mid+1,R,rt<<1|1);
    return ANS;
}
int main()
{
    int n,q;
    while(~scanf("%d%d",&n,&q))
    {
        nn=n;
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        build(1,n,1);
        char str[10];
        int l,r;
        for(int i=1;i<=q;i++)
        {
            scanf("%s",str);
            scanf("%d%d",&l,&r);
            if(str[0]=='a')
            {
                range_update(l,r,1,1,n,1);
            }
            else
            {
                ll res=range_query(l,r,1,n,1);
                printf("%lld\n",res);
            }
        }
    }
    return 0;
}
