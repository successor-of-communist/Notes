#include<iostream>
#include<queue>
#include<cmath>
#include<string.h>
using namespace std;
bool a[50000000];
struct node
{
    char s[4][5];
    int step;
    bool operator<(const node nod)const
    {
        return step>nod.step;
    }
};
bool check(char str[4][5])
{
    for(int i=0;i<4;i++)
    {
        if(str[i][0]==str[i][1]&&str[i][1]==str[i][2]&&str[i][2]==str[i][3]
                &&(str[i][0]=='X'||str[i][0]=='Y'))
            return true;
        if(str[0][i]==str[1][i]&&str[1][i]==str[2][i]&&str[2][i]==str[3][i]
                &&(str[0][i]=='X'||str[0][i]=='Y'))
            return true;
    }
    if(str[0][0]==str[1][1]&&str[1][1]==str[2][2]&&str[2][2]==str[3][3]
            &&(str[0][0]=='X'||str[0][0]=='Y'))
        return true;
    if(str[0][3]==str[1][2]&&str[1][2]==str[2][1]&&str[2][1]==str[3][0]
            &&(str[0][3]=='X'||str[0][3]=='Y'))
        return true;
    return false;
}
int m[16];
int cal(char str[4][5])
{
    int sum=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(str[i][j]=='X')
            {
                sum+=m[i*4+j];
            }
            else if(str[i][j]=='Y')
            {
                sum+=m[i*4+j]*2;
            }
        }
    }
    return sum;
}
int dir[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
int bfs(node tmp)
{
    priority_queue<node> que;
    tmp.step=0;
    que.push(tmp);
    while(!que.empty())
    {
        node tm=que.top();
        que.pop();
        if(check(tm.s))
        {
            return tm.step;
        }
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(tm.s[i][j]!='O')
                {
                    for(int k=0;k<4;k++)
                    {
                        int x=i+dir[k][0];
                        int y=j+dir[k][1];
                        if(x>=0&&x<4&&y>=0&&y<4&&tm.s[x][y]=='O')
                        {
                            node t=tm;
                            t.s[x][y]=t.s[i][j];
                            t.s[i][j]='O';
                            int cur=cal(t.s);
                            if(a[cur]==0)
                            {
                                a[cur]=1;
                                t.step+=1;
                                que.push(t);
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}
int main()
{
    int t;
    cin>>t;
    m[0]=1;
    for(int i=1;i<16;i++)
    {
        m[i]=m[i-1]*3;
    }
    while(t--)
    {
        memset(a,0,sizeof(a));
        char str[5];
        node c;
        for(int i=0;i<4;i++)
        {
            cin>>str;
            strcpy(c.s[i],str);
        }
        a[cal(c.s)]=1;
        cout<<bfs(c)<<endl;
    }
    return 0;
}
