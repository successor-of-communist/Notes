#include<iostream>
#include<stdio.h>
#include<bitset>
using namespace std;
bitset<1005> bit[1005];
int main(){
    int t;
    scanf("%d",&t);
    for(int cou=1;cou<=t;cou++)
    {
        for(int i=0;i<1005;i++)
            bit[i].reset();
        int n,k,num;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            bit[i][i]=1;
            scanf("%d",&k);
            for(int j=0;j<k;j++)
            {
                scanf("%d",&num);
                bit[i][num-1]=1;
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(bit[j][i])
                    bit[j]|=bit[i];
            }
        }
        double ans=0;
        for(int i=0;i<n;i++)
        {
            num=0;
            for(int j=0;j<n;j++)
            {
                if(bit[j][i])
                    num++;
            }
            ans+=1.0/num;
        }
        printf("Case #%d: %.05lf\n",cou,ans);
    }
    return 0;
}
