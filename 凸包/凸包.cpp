/*
示例：
10
0 0
-1 1
1 1
0 2
1 2
-1 3
0 3
1 3
2 3
0 4


思路：
先求出最低点，
再求出所有的点与该点和平行于x轴的cos值：（不是tan 是因为tan在0~180°范围内不单调，不好排序）
再按照从大到小的顺序排序：
从cos最大的点开始计算，用叉乘计算是不是逆时针旋转。
如果满足取出栈顶，不满足的话出栈，然后继续计算。找到下一个点。
知道找到一个满足的点。
*/


#include<cstdio>
#include<cmath>
#include<stack>
#include<iostream>
#include<algorithm>
using namespace std;
struct Point
{
	int x=0;
	int y=0;
	double coss=1.0;
	int dx=0;
	int dy=0;
};
bool cmp( Point a,Point b)
{
	if(a.y<b.y)
	    return 1;
	if(a.y>b.y) return 0; 
	if(a.x<b.x)
	    return 1;
	return 0;
}
bool cmpp(Point a,Point b)
{
	if(a.coss>b.coss) return 1;
	else return 0;
}
double qcos(int x1,int y1,int x2,int y2)
{
	double len = sqrt((double)((x1-x2)*(x1-x2))+(double)((y1-y2)*(y1-y2)));
	if(len == 0) return 1.0;
	else return (double)(x2-x1)/len;
}
int main()
{
	int n;
	stack<Point> z;
	cin>>n;
	Point *p=new Point[n+1];
	for(int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		p[i].x=x;
		p[i].y=y;
		p[i].coss=1.0;
	}
	sort(p+1,p+n+1,cmp);
	
	p[1].dx=0;
	p[1].dy=0;
	z.push(p[1]);
	Point tmp=z.top();
	for(int i=1;i<=n;++i)
	{
		p[i].coss=qcos(tmp.x,tmp.y,p[i].x,p[i].y);
	}
	sort(p+2,p+n+1,cmpp);
	for(int i=2;i<=n;++i)
	{
		Point tmp= z.top();
		int dx=p[i].x-tmp.x;
		p[i].dx=p[i].x-tmp.x;
		int dy=p[i].y-tmp.y;
		p[i].dy=p[i].y-tmp.y;
		if(dx*tmp.dy-dy*tmp.dx<=0)
		{
			z.push(p[i]); 
			continue;
		}
		while(dx*tmp.dy-dy*tmp.dx>0)
		{
			z.pop();
			tmp=z.top();
		    p[i].dx=p[i].x-tmp.x;
		    p[i].dy=p[i].y-tmp.y;
			
		}
		z.push(p[i]);
	} 
	while(!z.empty())
	{
		Point tmp=z.top();
		z.pop();
		cout<<"X: "<<tmp.x<<" Y: "<<tmp.y<<endl; 
	}
	return 0;
	
} 
