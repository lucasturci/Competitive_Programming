// Implicit multiset of elements between 1 and N (or you can compress them to the range [1, N])
// See https://codeforces.com/blog/entry/49446
/*
	Operations: 
	1. Add an element to a multiset
	2. Split one multiset into two multisets (put first k into the first and remaining into the second)
	3. Split one multiset into two multisets (put all keys less than k into the first and remaining into the second)
	4. Merge two sets into one

	Queries:
	1. Is x in the set? If so, how many of it?
	2. What is the kth element of the set?

	Complexity is O(Q logN), time and memory
	Proof: 

	If there were only add and split operations, for every operation you create additional logN nodes. So everything is O(Q logN )
	Let's call the set of nodes we create S.

	Now, in every merge operation (see code), you visit all the nodes that belong to both segtrees, but don't touch the ones that 
	are not present in at least one of them. So every visited node is present in both segtrees, and in the merge operation you
	discard one of them. This is objectively the same as choosing some nodes from S and removing them from the set. 
	So you never visit more than Q logN nodes in the merge operations

	Note that because of that, you can also add persistence to the merge operation, and the complexity will still remain QlogN time and memory
	(see https://discuss.codechef.com/t/difval-editorial/68523)

	The proof is a little more complex, because now for every node you visit in S, you discard one but you also add one because of persistence.
	But, if you look at merges in a sequence of updates (for example: T1 -> merge something -> T2 -> add something -> T3 -> split -> T4... )
	In a sequence or chain of updates, in every merge operation, you add one node (persistence) and discard **two** (the previous nodes of both trees).
	And now this is enough to prove that it's still QlogN

*/

#include <bits/stdc++.h>
using namespace std;
#define mid ((l+r) >> 1)

const int N = 2000007; // I think this is a good N for 10^5

struct node {
	int l, r; // children left and right
	int s; // sum
};


node seg[N];
stack<int> garbage; // If you are sure you wont use a node anymore, you can add it to garbage, to avoid MLE
int tt;

int new_node() {
	int u;
	if(garbage.size()) u = garbage.top(), garbage.pop();
	else u = ++tt;

	seg[u].l = seg[u].r = seg[u].s = 0;
	return u;
}

// add x occurences of j
void add(int & cur, int l, int r, int j, int x) {
	if(cur == 0) cur = new_node();
	if(l == r) {
		seg[cur].s += x;
	} else {
		if(j <= mid) add(seg[cur].l, l, mid, j, x);
		else add(seg[cur].r, mid+1, r, j, x);
		seg[cur].s = (seg[cur].l? seg[seg[cur].l].s : 0) + (seg[cur].r? seg[seg[cur].r].s : 0);
	}
}


inline int sz(int x) {
	return x == 0? 0 : seg[x].s;
}

// split t1 into t1 and t2, putting first k in t1
void split(int t1, int & t2, int k) {
	if(!t1) return;
	
	t2 = new_node();

	if(sz(seg[t1].l) == k) {
		swap(seg[t1].r, seg[t2].r);
	} else if(sz(seg[t1].l) < k) {
		split(seg[t1].r, seg[t2].r, k - sz(seg[t1].l));
	} else {
		swap(seg[t1].r, seg[t2].r);
		split(seg[t1].l, seg[t2].l, k);
	}
	
	seg[t2].s = seg[t1].s - k;
	seg[t1].s = k;
}

// split t1 into t1 and t2, putting all less than or equal to x into t1
void split(int t1, int & t2, int l, int r, int x) {
	if(!t1) return;
	
	t2 = new_node();

	if(mid == x) {
		swap(seg[t1].r, seg[t2].r);
	} else if(mid < x) {
		split(seg[t1].r, seg[t2].r, mid+1, r, x);
	} else {
		swap(seg[t1].r, seg[t2].r);
		split(seg[t1].l, seg[t2].l, l, mid, x);
	}


	if(l == r) {
		if(x < mid) swap(seg[t1].s, seg[t2].s);
	} else {
		seg[t1].s = (seg[t1].l? seg[seg[t1].l].s : 0) + (seg[t1].r? seg[seg[t1].r].s : 0);
		seg[t2].s = (seg[t2].l? seg[seg[t2].l].s : 0) + (seg[t2].r? seg[seg[t2].r].s : 0);		
	}
}

// merging t1 and t2 into t1
void merge(int & t1, int t2) {
	if(!t1 or !t2) return void(t1 = (t1? t1 : t2));
	merge(seg[t1].l, seg[t2].l);
	merge(seg[t1].r, seg[t2].r);
	seg[t1].s += seg[t2].s;
	garbage.push(t2);
}

// ask for kth
int kth(int cur, int l, int r, int k) {
	if(l == r) return l;

	if(sz(seg[cur].l) >= k) return kth(seg[cur].l, l, mid, k);
	else return kth(seg[cur].r, mid+1, r, k - sz(seg[cur].l));
}

// counts how many x's
int find(int cur, int l, int r, int x) {
	if(!cur or r < x or l > x) return 0;
	if(l == r) return seg[cur].s;
	return find(seg[cur].l, l, mid, x) + find(seg[cur].r, mid+1, r, x);
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
}