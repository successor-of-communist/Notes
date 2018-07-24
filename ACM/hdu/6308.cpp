#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a,b;
        char ch[100];
        scanf("%d%d",&a,&b);
        scanf("%s",ch);
        int len=strlen(ch);
        int time;
        if(len==5)
        {
            int h=(int)(ch[4]-'0');
            if(ch[3]=='+')
            {
                time=h-8;
            }
            else if(ch[3]=='-')
            {
                time=-8-h;
            }
            time=time*10;
        }
        else if(len==6)
        {
           int h=(int)((int)(ch[4]-'0')*10+(int)(ch[5]-'0'));
           if(ch[3]=='+')
           {
               time=h-8;
           }
           else if(ch[3]=='-')
           {
               time=-8-h;
           }
            time=time*10;
        }
        else if(len==7)
        {
           int h=(int)((int)(ch[4]-'0')*10+(int)(ch[6]-'0'));
            if(ch[3]=='+')
            {
                time=h-8*10;
            }
            else if(ch[3]=='-')
            {
                time=-8*10-h;
            }
        }
        else if(len==8)
        {
            int h=(int)((int)(ch[4]-'0')*100+(int)(ch[5]-'0')*10+(int)(ch[7]-'0'));
            if(ch[3]=='+')
            {
                time=h-8*10;
            }
            else if(ch[3]=='-')
            {
                time=-8*10-h;
            }
        }
        time=time*60;
        time/=10;
        double alltime=a*60+b;
        double finaltime=alltime+time;
        int hour=(((int)finaltime+24*60)/60)%24;
        int minut=((int)finaltime+1440)%60;
        if(hour/10)
        {
            if(minut/10)
            {
                printf("%d:%d\n",hour,minut);
            }
            else
            {
                printf("%d:0%d\n",hour,minut);
            }
        }
        else
        {
            if(minut/10)
            {
                printf("0%d:%d\n",hour,minut);
            }
            else
            {
                printf("0%d:0%d\n",hour,minut);
            }
        }
    }
    return 0;
}

