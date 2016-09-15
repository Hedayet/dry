const int MAXM = 1e5+1; // 1 for imp.
int tree[MAXM * 8];

int update(int node, int l, int r, int i, int val)
{

	if(r < i || l > i) {
		return tree[node];
	}
	if(l == r) {
		tree[node] = val;
		return val;
	}
	
	int p = update(node*2, l, (l+r)/2, i, val);
	int q = update(node*2+1, (l+r)/2+1, r, i, val);
	tree[node] = max(p, q);
	return tree[node];
}

int query(int node, int l, int r, int beg, int end)
{
	if(r < beg || l > end) {
		return 1;
	}
	if(beg <= l && r <= end) {
		return tree[node];
	}
	return max(query(node*2, l, (l+r)/2, beg, end), query(node*2+1, (l+r)/2+1, r, beg, end));
}

// driver code
int main()
{
	// to update the value at position pos with value val.
	// update(1, 1, N, pos, val);
	//
	// to query the max between left and right
	// query(1, 1, N, left, right);
}