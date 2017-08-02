/* ***********************************************
Author        :yuanzhaolin
Created Time  :2017年07月28日 星期五 13时33分17秒
File Name     :code.cpp
************************************************ */

#include <cstdio>
#include <sstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <utility>
using namespace std;
#define repp(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a) for(int i=0;i<a;i++)
#define REP(i,a) for(int i=1;i<=a;i++)
#define per(i,a,b) for(int i=a-1;i>=b;i--)
#define foreach(i,a) for(int i=head[a];i>=0;i=ee[i].next)
#define Foreach(i,a) for(__typeof((a).begin())i=(a).begin();i!=(a).end();i++)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define mp make_pair
#define m0(x) memset(x,0,sizeof(x))
#define mff(x) memset(x,0xff,sizeof(x))
#define fi first
#define se second
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define SZ(x) ((int)(x).size())
#define sqr(x) ((x)*(x))
#define C1(x) cout<<x<<endl
#define C2(x,y) cout<<x<<" "<<y<<endl
#define C3(x,y,z) cout<<x<<" "<<y<<" "<<z<<endl
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector< pair<int,int> > VPII;
const ll mod=(ll)1e9+7;
const ll maxn=(ll)1e5+7;
const ll maxe=(ll)1e6+7;
const ll INF=(ll)1e9+7;
const double PI=acos(-1);
int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};

ull HASH(vector<int> v)
{
	ull h=0;
	for(int i=0;i<v.size();i++)
		h=h*INF+v[i];
	h=h*INF+v.size();
	return h;
}
//节点编号回收站
struct Gar
{
	queue<int> que;
	int cnt;
	bool used[maxn];
	void init()
	{
		while(!que.empty()) que.pop();
		memset(used,false,sizeof(used));
		cnt=0;
	}
	void recycle(int v)
	{
		if(!used[v]) return ;
		que.push(v);
		used[v]=false;
	}
	int ask()
	{
		if(que.empty())
		{
			used[cnt++]=true;
			return cnt-1;
		}
		else
		{
			int v=que.front();
			que.pop();
			used[v]=true;
			return v;
		}
	}
};
Gar gar;


//符号表
struct Alp 
{
	vector<string> slist;
	map<string,int> m;
	void add(string s)
	{
		if(m.find(s)==m.end())
		{
			slist.push_back(s);
			m[s]=slist.size()-1;
		}
	}
	int findID(string s)
	{
		if(m.find(s)==m.end())
		{
			add(s);
		}
		return m[s];	
	}
	bool isIN(string str)
	{
		if(m.find(str)==m.end()) return false;
		return true;
	}
	string findstr(int id)	
	{
		return slist[id];
	}
	void debug()
	{
		for(int i=0;i<slist.size();i++)
			cout<<i<<" "<<slist[i]<<" "<<slist[i].length()<<" "<<isIN(slist[i])<<endl;
	}
};
Alp alp;
//展开式数据结构
struct E
{
	vector<int> p;
	int left;
	string Gid,Rid,part_name;
	E(){}
	E(string s)
	{
		istringstream istr;
		istr.str(s.c_str());
		string buf;	
		istr>>Gid>>buf;
		istr>>part_name>>buf;
		istr>>Rid>>buf>>buf;
		left=alp.findID(buf);
		if(part_name=="syntax")
		{
			istr>>buf;	
			while(istr>>buf)
				p.push_back(alp.findID(buf));
		}
		else if(part_name=="lexicon")
		{
			istr>>buf;	
			getline(istr,buf);
			buf.erase(buf.find_last_not_of(' ')+1);
			vector<int> v;
			p.push_back(alp.findID(buf.substr(1)));
		}
	}
	void debug()
	{
		cout<<Rid<<"\t";
		cout<<left<<" "<<"\t";
		for(int i=0;i<p.size();i++)
			cout<<p[i]<<" ";
		cout<<endl;
	}
};
//文法集合
struct Gra
{
	vector<E> gramma; 
	map<vector<int>,vector<int> > g;
	vector< pair<int,vector<int> > > p;
	void insert(string s1,vector<string> sl)
	{
		vector<int> resV;
		for(int i=0;i<sl.size();i++)
			resV.push_back(alp.findID(sl[i]));
		//g[resV].push_back(alp.findID(s1));
	}
	bool add(string s)
	{
		E e = E(s);
		e.debug();
		if(g.find(e.p)==g.end()) 
		{
			vector<int> tmp;
			g[e.p]=tmp;
		}
		g[e.p].push_back(gramma.size());
		gramma.push_back(e);
		p.push_back(make_pair(e.left,e.p));
		if(e.part_name!="lexicon"&&e.part_name!="syntax") return false;
		return true;
		/*
		istringstream istr;
		istr.str(s.c_str());
		string buf;	
		istr>>buf;
		istr>>buf;
		if(buf=="syntax")
		{
			istr>>buf;	
			istr>>buf;	
			vector<int> v;
			int left=alp.findID(buf);
			istr>>buf;	
			while(istr>>buf)
				v.push_back(alp.findID(buf));
			p.push_back(make_pair(left,v));
			g[v]=left;
		}
		else if(buf=="lexicon")
		{
			istr>>buf;	
			istr>>buf;	
			int left = alp.findID(buf);
			istr>>buf;	
			getline(istr,buf);
			vector<int> v;
			v.push_back(alp.findID(buf.substr(1)));
			g[v]=left;
		}
		*/
		return true;
	}
	vector<int> merge(vector<int> v)
	{
		vector<int> x;
		x.push_back(-1);
		if(g.find(v)==g.end()) return x;
		else return g[v];
	}
	void debug()
	{
		for(int i=0;i<p.size();i++)	
		{
			cout<<p[i].fi<<"\t";
			for(int j=0;j<p[i].se.size();j++)
				cout<<p[i].se[j]<<" ";
			cout<<endl;
		}
	}
};
Gra gra;

struct Node
{
	int T_id,N_id,depth,width,parent_node,aid;
	string term,G_id,R_id,part_name;
	void debug()
	{
		cout<<N_id<<" "<<parent_node<<" "<<term<<endl;
	}
	void log()
	{
		char c=' ';
		cout<<T_id<<c;
		cout<<N_id<<c;
		cout<<term<<c;
		cout<<depth<<c;
		cout<<width<<c;
		cout<<parent_node<<c;
		cout<<G_id<<c;
		cout<<part_name<<c;
		cout<<R_id<<endl;
	}
};
Node tree[maxn];
vector<int> G[maxn];
Node newNode()
{
	return tree[gar.ask()];
}
string sents[maxn];
void test()
{
	for(int i=0;i<5;i++)
	{
		Node &node=tree[gar.ask()];
		node.N_id=i;
	}
	for(int i=0;i<10;i++)
	{
		tree[i].debug();
	}
}
vector<int> splitSent(string s)
{
	vector<int> res;
	vector<string> str;
	istringstream istr(s);
	while(istr>>s)
	{
		if(s==".") continue;
		//s.erase(s.find_last_not_of(' ')+1);
		s.erase(s.find_last_not_of('.')+1);
		str.push_back(s);
	}
	string pre="";
	for(int i=0;i<str.size();i++)
	{
		if(pre=="") pre=str[i];
		else
		pre=pre+" "+str[i];
		/*
		cout<<pre<<endl;
		cout<<pre.length()<<endl;
		*/
		if(alp.isIN(pre))
		{
			res.push_back(alp.findID(pre));
			pre="";
		}
	}
	return res;
}
void input()
{
	while(1)
	{
		char ss[1000];
		string s=ss;
		getline(cin,s);
		//cout<<s<<endl;
		if(s.length()==0||!gra.add(s)) break;
	}
	string sent;
	int cnt=0;
}
void Del(int v)
{
	Node &e = tree[v];
	for(int i=0;i<G[v].size();i++)
		tree[G[v][i]].parent_node=-1;
	e.N_id=0;
	e.aid=0;
	e.term="";
	e.parent_node=-1;
	e.width=0;
	G[v].clear();
	gar.recycle(v);
};
set<ull> SET_vis;
bool isSame(vector<int> v)
{

	for(int i=0;i<v.size();i++)
		v[i]=tree[v[i]].aid;
	ull h=HASH(v);
	if(SET_vis.find(h)!=SET_vis.end()) return true;
	else
	{
		SET_vis.insert(h);
		return false;
	}
}
int dfs(vector<int> v)
{
	if(v.size()<=0)
	{

	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<endl;

	for(int i=0;i<v.size();i++)
		cout<<tree[v[i]].term<<" ";
	cout<<endl;
	for(int i=0;i<v.size();i++)
		cout<<tree[v[i]].aid<<" ";
	cout<<endl;
	cout<<endl;
	}
	if(v.size()==1&&tree[v[0]].aid==alp.findID("\\S"))
	{
		return v[0];		
	}
	if(isSame(v)) return -1;
	for(int i=0;i<v.size();i++)
	{
		vector<int> right;
		for(int j=0;j<3&&i+j<v.size();j++)
		{
			right.push_back(tree[v[i+j]].aid);
			//int res=gra.merge(right);
			vector<int> res_list=gra.merge(right);
			for(int l=0;l<res_list.size();l++)
			{
				int res=res_list[l];
				if(res==-1) continue;
				int nid=gar.ask();
				Node &e = tree[nid];
				e.depth=0;
				for(int k=i;k<=i+j;k++)
				{
					G[nid].push_back(v[k]);
					tree[v[k]].parent_node=nid;
					e.depth=max(tree[v[k]].depth,e.depth);
				}
				e.depth++;
				e.N_id=nid;
				e.aid=gra.gramma[res].left;
				e.term=alp.findstr(e.aid);
				e.part_name=gra.gramma[res].part_name;
				e.G_id=gra.gramma[res].Gid;
				e.R_id=gra.gramma[res].Rid;
				e.parent_node=-1;
				e.width=j+1;
				vector<int> newl=v;
				newl[i]=nid;
				if(j!=0) newl.erase(newl.begin()+i+1,newl.begin()+i+j+1);
				/*
				for(int l=0;l<newl.size();l++)
					cout<<tree[newl[l]].term;
				cout<<endl;
				*/
				int ans=-1;
				if(e.depth<7) 
				ans=dfs(newl);
				if(ans!=-1) return ans;
				Del(nid);
			}
			/*
			for(int p=0;p<right.size();p++)
				cout<<right[p]<<" ";
			cout<<res<<" ";
			cout<<"!!!"<<endl;
			*/
		}
	}
	return -1;
}
void dfs2(int u)
{
	tree[u].log();
	for(int i=0;i<G[u].size();i++)	
	{
		Node &v= tree[G[u][i]];
		v.depth=tree[u].depth+1;	
		dfs2(G[u][i]);
	}
}
void solve(string s)
{
	s[0]+=('a'-'A');
	vector<int> splitRes=splitSent(s);
	cout<<s<<endl;
	for(int i=0;i<splitRes.size();i++)
	{
		cout<<splitRes[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<splitRes.size();i++)
	{
		cout<<alp.findstr(splitRes[i])<<" ";
	}
	cout<<endl;
	vector<int> v;
	for(int i=0;i<splitRes.size();i++)
	{
		int Nid=gar.ask();
		Node &e = tree[Nid];
		e.N_id=Nid;
		e.aid=splitRes[i];
		e.term=alp.findstr(splitRes[i]);
		e.depth=e.width=0;
		e.parent_node=-1;
		e.G_id="";
		e.R_id="";
		e.part_name="";
		v.push_back(Nid);
	}
	int res=dfs(v);
	cout<<res<<endl;
	if(res==-1)
	return ;
	tree[res].depth=0;
	dfs2(res);
	tree[res].depth=0;
}
void init()
{
	SET_vis.clear();
	gar.init();
	for(int i=0;i<maxn;i++)
		G[i].clear();
	
}
void run()
{
	string s;
	int cnt=4;
	while(cnt--)
	{
		init();
		getline(cin,s);
		solve(s);
	}
}
void deg()
{
	set<vector<int> > s;
	for(int i=0;i<gra.gramma.size();i++)
	{
		if(s.find(gra.gramma[i].p)!=s.end())
		{
			printf("FUCK");
			for(int j=0;j<gra.gramma[i].p.size();j++)
				cout<<gra.gramma[i].p[j]<<" ";
			cout<<endl;
		}
		else
		s.insert(gra.gramma[i].p);
	}
}
int main()
{
    //freopen("test.in","r",stdin);
    //freopen("out.txt","w",stdout);
   	input();
//	gra.debug();
	alp.debug();
	//deg();
	run();
    return 0;
}
