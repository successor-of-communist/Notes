#include<iostream>
#include<string.h>
#include<map>
#include<set>
#include<stdio.h>
using namespace std;
struct node
{
    int num;
    int pos;
    bool operator<(const node x)const
    {
        return num<x.num;
    }
}ar[100010];
int fl[100010],fr[100010];
set<node> se;
int main(){
    int t;
    scanf("%d",&t);
    while(t--)
    {
        se.clear();
        int n;
        scanf("%d",&n);
        memset(fl,0,sizeof(fl));
        memset(fr,0,sizeof(fr));
        for(int i=0;i<n;i++)
        {
            scanf("%d",&ar[i].num);
            ar[i].pos=i;
        }
        se.insert(ar[0]);
        set<node>::iterator it;
        int ans=-1;
        for(int i=1;i<n;i++)
        {
            it=se.lower_bound(ar[i]);
            if(it==se.end())
            {
                set<node>::reverse_iterator rit=se.rbegin();
                if(fr[rit->pos]==1)
                    break;
                fr[rit->pos]=1;
                ans=rit->num;
            }
            else if(it==se.begin())
            {
                if(fl[it->pos]==1)
                    break;
                fl[it->pos]=1;
                ans=it->num;
            }
            else
            {
                if(fl[it->pos]==1)
                {
                    it--;
                    if(fr[it->pos]==1)
                        break;
                    fr[it->pos]=1;
                    ans=it->num;
                }
                else
                {
                    if(fl[it->pos]==1)
                        break;
                    fl[it->pos]=1;
                    ans=it->num;
                }
            }
            se.insert(ar[i]);
            printf("%d\n",ans);
        }
    }
    return 0;
}
