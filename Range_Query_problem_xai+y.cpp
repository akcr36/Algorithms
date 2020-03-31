#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define mod 1000000009
pair<int,int> lz[100000];
int a[50000];
void upd(int i,int l,int r,int lu,int ru,int xu,int yu)   //updating query for lazy
{
	if(r<lu||l>ru||l>r)   //no overlap ocurs
	return;
	if(lu<=l&&r<=ru)      //fully overlap
	{
		yu+=xu*lz[i].second;
		xu*=lz[i].first;
		lz[i]={xu,yu};
		return;
	}
	int m=(l+r)/2;
	if(lz[i].first==1&&lz[i].second==0)  //no panding work
	{
		upd(2*i+1,l,m,lu,ru,xu,yu);
		upd(2*i+2,m+1,r,lu,ru,xu,yu);
	}
	else
	{
		upd(2*i+1,l,m,l,r,lz[i].first,lz[i].second);       //first finish panding work
		upd(2*i+2,m+1,r,l,r,lz[i].first,lz[i].second);
		lz[i]={1,0};
		upd(2*i+1,l,m,lu,ru,xu,yu);
		upd(2*i+2,m+1,r,lu,ru,xu,yu);
	}
}
void relax(int i,int l,int r,vector<pair<int,int> > &v) //realxig or getting final change in array
{
	v.push_back(lz[i]);   //storing all query for leaf
	if(l==r)  // get leaf, time to change value of array
	{
		int mul=1,ad=0;
		for(int j=v.size()-1;j>=0;j--)
		{
			ad=ad*v[j].first+v[j].second;
			mul*=v[j].first;
		}
		a[l]=mul*a[l]+ad;
		v.pop_back();
		return;
	}
	int m=(l+r)/2;
	relax(2*i+1,l,m,v);
	relax(2*i+2,m+1,r,v);
	v.pop_back();

}
void fn(vector<int> &a, vector<vector<int> > &b) {
    for(int i=0;i<b.size();i++)
    {
        for(int j=b[i][0]-1;j<b[i][1];j++)
        {
            long long int z=a[j];
            a[j]=((z*b[i][2])%mod+b[i][3])%mod;
        }
    }
    for(int i=0;i<a.size();i++)
    cout<<a[i]<<" ";
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int n,q;
	cin>>n>>q;
	vector<int> v1;
	vector<vector<int> > v2;
	//cout<<n<<" "<<q<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		v1.push_back(a[i]);
	}
    for(int i=0;i<100000;i++)
    {
    	lz[i].first=1;
    	lz[i].second=0;
    }
    while(q--)
    {
    	vector<int> v3;
    	int l,r,x,y;
    	cin>>l>>r>>x>>y;
    	v3.push_back(l);
    	v3.push_back(r);
    	v3.push_back(x);
    	v3.push_back(y);
    	v2.push_back(v3);
    	//cout<<x<<" "<<y<<endl;
    	upd(0,1,n,l,r,x,y);
    }
    vector<pair<int,int> > v;
    relax(0,1,n,v);
    for(int i=1;i<=n;i++)
    cout<<a[i]<<" ";
    cout<<endl;
    fn(v1,v2);
}
