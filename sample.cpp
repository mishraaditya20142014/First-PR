#include <bits/stdc++.h>
using namespace std;
#define int int64_t

class Node
{
	public:
	string val;
	vector<Node*> children;
	bool is_locked=false;
	Node* _parent=nullptr;
	multiset<string> des;
	int self_uid;
	map<int,int> uid;
	
	bool isLock()
	{
		return is_locked;
	}
	bool Lock(int ud,map<string,Node *> &mp)
	{
		if(isLock())
		return false;
		
		if((int)des.size()>0)
		return false;
		
		Node* parent=_parent;
		while(parent)
		{
			if(parent->isLock())
			return false;
			
			parent=parent->_parent;
		}
		parent=_parent;
		while(parent)
		{
			parent->des.insert(val);
			parent->uid[ud]++;
			parent=parent->_parent;
		}
		self_uid=ud;
		is_locked=true;
		return true;
	}
	bool unlock(int ud,map<string,Node*> &mp)
	{
		if(isLock() and self_uid==ud)
        {
            Node* parent=_parent;
            while(parent)
            {
                parent->des.erase((val));
                parent->uid[ud]--;
                if(parent->uid[ud]==0)
                parent->uid.erase(ud);

                parent=parent->_parent;
            }
            is_locked=false;
            return true;
        }
        return false;
	}
    bool upgrade(int ud,map<string,Node*> &mp)
    {
        if(uid.size()==1 and uid.begin()->first == ud)
        {
            bool ans=true;
            for(auto i:des)
            {
                ans=ans && mp[i]->unlock(ud,mp);
            }
            return Lock(ud,mp);
        }
        return false;
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    map<string,Node*> mp;
    int n,m,k;
    cin>>n>>m>>k;
    vector<Node> A(n);
    for(auto &i:A) cin>>i.val;
    for(int i=0;i<n;i++) mp[A[i].val]=&A[i];
    for(int i=0;m*i<n;i++) 
    {
        for(int j=m*i+1;j<=m*i+m and j<n;j++)
        {
            A[i].children.push_back(&A[j]);
            A[j]._parent=&A[i];
        }
    }
    for(int i=0,a,c;i<k;i++)
    {
        string b;
        cin>>a>>b>>c;
        if(a==1)
        {
            cout<<(mp[b]->Lock(c,mp)?"true":"false")<<"\n";
        }
        else if(a==2)
        {
            cout<<(mp[b]->unlock(c,mp)?"true":"false")<<"\n";
        }
        else{
            cout<<(mp[b]->upgrade(c,mp)?"true":"false")<<"\n";
        }
    }
}
