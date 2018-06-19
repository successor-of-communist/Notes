#include<iostream>
#include<queue>
#include<cmath>
#include<string.h>
using namespace std;
#define maxn 200005
#define maxm 9000005
int root[maxn],v[maxm],ls[maxm],rs[maxm];
int cnt;
int n,m;
void build(int &k,int l,int r)
{
    k=++cnt;
    if(l==r)
    {
        v[k]=l;
        return;
    }
    int mid=(l+r)/2;
    build(ls[k],l,mid);
    build(rs[k],mid+1,r);
}
int query(int k,int l,int r,int pos)
{
    if(l==r)
        return v[k];
    int mid=(l+r)>>1;
    if(pos<=mid)
        return query(ls[k],l,mid,pos);
    else
        return query(rs[k],mid+1,r,pos);
}
void insert(int x,int &y,int l,int r,int pos,int val)
{
    y=++cnt;
    if(l==r)
    {
        v[y]=val;
        return;
    }
    int mid=(l+r)>>1;
    ls[y]=ls[x];
    rs[y]=rs[x];
    if(pos<=mid)
        insert(ls[x],ls[y],l,mid,pos,val);
    else
        insert(rs[x],rs[y],mid+1,r,pos,val);
}
int find(int &r,int x)
{
    int tmp=query(r,1,n,x);
    if(tmp==x)
        return x;
    else
    {
        int ret=find(r,tmp);
        insert(r,r,1,n,x,ret);
        return ret;
    }
}
int main()
{
    while(cin>>n>>m)
    {
        build(root[0],1,n);
        for(int i=1;i<=m;i++)
        {
            int f;
            cin>>f;
            if(f==1)
            {
                int x,y;
                cin>>x>>y;
                int fx=find(root[i-1],x),fy=find(root[i-1],y);
                if(fx==fy)
                    root[i]=root[i-1];
                else
                    insert(root[i-1],root[i],1,n,fx,fy);
            }
            else if(f==2)
            {
                int x;
                cin>>x;
                root[i]=root[x];
            }
            else{
                int x,y;
                cin>>x>>y;
                root[i]=root[i-1];
                int fx=find(root[i],x),fy=find(root[i],y);
                if(fx==fy)
                    cout<<"YES"<<endl;
                else
                    cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}
