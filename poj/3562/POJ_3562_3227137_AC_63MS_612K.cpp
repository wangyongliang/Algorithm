#include<stdio.h>
#include<string.h>
char s1[]={"MCXI"};
char s2[]={"MDLV"};
int b[]={1000,100,10,1};
void print(int ans,char str[])
{
	int k,i=0,j;
	if(ans==0) str[i++]='0';
	else
	{
		k=ans/b[0];
		while(k--) str[i++]='M';
		ans%=b[0];
		for(j=1;s1[j];j++)
		{
			k=ans/b[j];
			if(k<4) while(k--) str[i++]=s1[j];
			else if(k==4) str[i++]=s1[j],str[i++]=s2[j];
			else if(k>4&&k<9) 
			{
				str[i++]=s2[j];
				k-=5;
				while(k--) str[i++]=s1[j];
			}
			else str[i++]=s1[j],str[i++]=s1[j-1];
			ans%=b[j];
		}
	}
	str[i]=0;
}
struct node
{
	int index[26];
	int num;
}a[1000000];
int cnt;
void insert(int num,char str[])
{
	int i,j=0,k;
	for(i=0;str[i];i++)
	{
		if(a[j].index[str[i]-'A']==-1)
		{
			for(k=0;k<26;k++) a[cnt].index[k]=-1;
			a[cnt].num=-1;
			a[j].index[str[i]-'A']=cnt++;
		}
		j=a[j].index[str[i]-'A'];
	}
	a[j].num=num;
}
void init()
{
	int i;
	char str[30];
	for(i=0;i<26;i++) a[0].index[i]=-1;
	a[0].num=-1;
	cnt=1;
	for(i=1;i<4000;i++)
	{
		print(i,str);
		insert(i,str);
	}
}
char s[20][20];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int ans,n,m;
bool flg[20][20];
void dfs(int x,int y,int j)
{
	int xx,yy,i;
	if(j==-1) return;
	if(y==m-1)  ans=ans>a[j].num?a[j].num:ans;
	else
	{
		for(i=0;i<4;i++)
		{
			xx=x+dx[i];
			yy=y+dy[i];
			if(xx>=0&&xx<n&&yy>=0&&y<m&&flg[xx][yy]==0)
			{
				flg[xx][yy]=1;
				dfs(xx,yy,a[j].index[s[xx][yy]-'A']);
				flg[xx][yy]=0;
			}
		}
	}
}
int main()
{
	init();
	int i,j;
	char str[30];
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(i=0;i<n;i++)
		{
			scanf("%s",s[i]);
			for(j=0;j<m;j++) flg[i][j]=0;
		}
		ans=4000;
		for(i=0;i<n;i++)
		{
			flg[i][0]=1;
			dfs(i,0,a[0].index[s[i][0]-'A']);
			flg[i][0]=0;
		}
		if(ans==4000) printf("NO\n");
		else 
		{
			print(ans,str);
			printf("%s\n",str);
		}
	}
	return 0;
}
