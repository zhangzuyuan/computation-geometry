/*
思路：首先进行排序，虽然可以在递归过程中按照快排方式进行求解，但是写法麻烦
并且对时间复杂度没有太大改进，
所以直接进行排序。然后进行二分，二分到两个节点
或三个节点时进行手动设置凸包。
通过直线方程判断与点相邻的点在直线的上方还是下方，
进行点往上或者往下阶梯状移动， 
之后再把四个边界点之间的点给从凸包中删除，
再把两个凸包合并。
递归求出所有点的凸包。 
*/ 

/*
样例 
6
2 5
7 8
9 6
1 1
2 9
4 7
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
bool tmp[10000000];
struct Node{
	int x;
	int y;
	int num;
	Node *prev=NULL;
	Node *next=NULL;
};
bool cmp(Node a,Node b)
{
	if(a.x>b.x)
	{
		return a.x<b.x;
	}else if(a.x==b.x) return a.y<b.y;
}
void tubao(Node a[],bool bo[],int left,int right)
{
	int mid=(left+right)>>1;
	if(right-left<3)
	{
		if(right-left ==1)
		{
			a[left].next=&a[right];a[left].prev=&a[right];
			a[right].next=&a[left];a[right].prev=&a[left];
			bo[left]=true;
			bo[right]=true;
		} 
		if(right-left==2)
		{
			a[left].next=&a[left+1];a[left+1].next=&a[left+2];a[left+2].next=&a[left];
			a[left].prev=&a[left+2];a[left+1].prev=&a[left];a[left+2].prev=&a[left+1]; 
			bo[left]=true;
			bo[left+1]=true;
			bo[left+2]=true;
			//cout<<"left"<<" "<<left<<" "<<a[left].next<<" "<<a[left].next->num<<" "<<a[left].prev<<endl;
			//cout<<"left+1"<<" "<<left+1<<" "<<a[left+1].next<<" "<<a[left+1].next->num<<" "<<a[left+1].prev<<endl;
			//cout<<"left+2"<<" "<<left+2<<" "<<a[left+2].next<<" "<<a[left+2].next->num<<" "<<a[left+2].prev<<endl;
		}
		return;
	}
	int tleft=mid;
	int tright=mid+1;
	tubao(a,bo,left,mid);
	tubao(a,bo,mid+1,right);
	for(int i=mid;i>=left;i--)
	{
		if(bo[i]==true)
		tleft=i;break;
	}
	for(int i=mid+1;i<=right;++i)
	{
		if(bo[i]==true)
		tright=i;break;
	}
	double k;double b;
	k=((double)a[tleft].y-(double)a[tright].y)/((double)a[tleft].x-(double)a[tright].x);
	b=(double)a[tright].y-k*(double)a[tright].x;
	int ttl=tleft;
	int ttr=tright;
	for(;;)
	{
		int check=true;
		double lans1,lans2;
		lans1=((double)a[ttl].prev->y-(double)a[ttr].y)-k*((double)a[ttl].prev->x-(double)a[ttr].x);
		lans2=((double)a[ttl].next->y-(double)a[ttr].y)-k*((double)a[ttl].next->x-(double)a[ttr].x);
		if(lans1*lans2<0) 
		{
			//bo[ttl]=false;
		    ttl=a[ttl].prev->num;
		    check=false;
		}
		if(lans1<0&&lans2<0)
		{
			ttl=a[ttl].prev->num;
		    check=false;
		}
		double rans1,rans2;
		rans1=((double)a[ttr].prev->y-(double)a[ttr].y)-k*((double)a[ttr].prev->x-(double)a[ttr].x);
		rans2=((double)a[ttr].next->y-(double)a[ttr].y)-k*((double)a[ttr].next->x-(double)a[ttr].x);
		if(rans1*rans2<0) 
		{
			//bo[ttl]=false;
		    ttr=a[ttr].next->num;
		    check=false;
		}
		if(rans1<0&&rans2<0)
		{
			ttr=a[ttr].next->num;
		    check=false;
		}
		if(check==true)
		    break;
		k=((double)a[ttl].y-(double)a[ttr].y)/((double)a[ttl].x-(double)a[ttr].x);
	}
	int downleft=ttl;int downright=ttr;
	
	k=((double)a[tleft].y-(double)a[tright].y)/((double)a[tleft].x-(double)a[tright].x);
	b=(double)a[tright].y-k*(double)a[tright].x;
	ttl=tleft;
	ttr=tright;
	for(;;)
	{
		int check=true;
		double llans1,llans2;
		llans1=((double)a[ttl].prev->y-(double)a[ttr].y)-k*((double)a[ttl].prev->x-(double)a[ttr].x);
		llans2=((double)a[ttl].next->y-(double)a[ttr].y)-k*((double)a[ttl].next->x-(double)a[ttr].x);
		if(llans1*llans2<0) 
		{
			//bo[ttl]=false;
		    ttl=a[ttl].next->num;
		    check=false;
		}
		if(llans1>0&&llans2>0)
		{
			ttl=a[ttl].next->num;
		    check=false;
		}
		double rrans1,rrans2;
		rrans1=((double)a[ttr].prev->y-(double)a[ttr].y)-k*((double)a[ttr].prev->x-(double)a[ttr].x);
		rrans2=((double)a[ttr].next->y-(double)a[ttr].y)-k*((double)a[ttr].next->x-(double)a[ttr].x);
		if(rrans1*rrans2<0) 
		{
			//bo[ttl]=false;
		    ttr=a[ttr].prev->num;
		    check=false;
		}
		if(rrans1>0&&rrans2>0)
		{
			ttr=a[ttr].prev->num;
		    check=false;
		}
		if(check==true)
		    break;
		k=((double)a[ttl].y-(double)a[ttr].y)/((double)a[ttl].x-(double)a[ttr].x);
	}
	int upleft=ttl;int upright=ttr;
	
	
	for(int i=left;i<=mid;i++)
	{
		if(a[i].x>a[upleft].x&&a[i].x>a[downleft].x)
		{
			bo[i]=false;
		}
		if(a[i].x==max(a[upleft].x,a[downleft].x)&&a[i].y<a[upleft].y&&a[i].y>a[downleft].y)
		    bo[i]=false;
		
	}
	for(int i=mid+1;i<=right;i++)
	{
		if(a[i].x<a[upright].x&&a[i].x<a[downright].x)
		{
			bo[i]=false;
		}
		if(a[i].x==min(a[upright].x,a[downright].x)&&a[i].y<a[upright].y&&a[i].y>a[downright].y)
		    bo[i]=false;
	}
	//Node i=a[upleft];
	//while(i.num!=downleft)
	//{
	//	bo[i.prev->num]=false;
	//	i=*(i.prev);
	//}
	//i=a[downright];
	//while(i.num!=upright)
	//{
	//	bo[i.prev->num]=false;
	////	i=*(i.prev);
	//}
	
	a[upleft].next=&a[upright];
	a[upright].prev=&a[upleft];
	a[downright].next=&a[downleft];
	a[downleft].prev=&a[right];
	
}
int main()
{
	int n;
	cin>>n;
	Node *node;
	node=new Node[n+1];
	bool *bo;
	bo = new bool[n+1];
	for(int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		node[i].x=x;
		node[i].y=y;
		bo[i]=false;
	}
	sort(node+1,node+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		node[i].num=i;
	}
	//for(int i=1;i<=n;i++)
	//{
	//	cout<<node[i].x<<" "<<node[i].y<<endl; 
	//}
	tubao(node,bo,1,n);
	
	
	int begin;
	for(int i=1;i<=n;++i)
	{
		if(bo[i]==true)
		  begin=i;
	}
	cout<<endl;
	
	for(int i=1;i<=n;++i)
	{
		if(bo[i]==true)
		cout<<node[i].x<<" "<<node[i].y<<endl;
	}
	delete []node;
	delete []bo; 
	return 0;
} 
