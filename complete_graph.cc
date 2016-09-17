const int MAXN = 1e3+2;
// Returns true if the graph with node set nodes and edge set edges
// is a complete graph. Returns false otherwise.
bool complete_graph(vector<int>nodes, vector<int>edges[])
{
	bool seen[MAXN];
	memset(seen, 0, sizeof(seen));
	for(auto &n : nodes) {
		seen[n] = true;
	}
	for(auto &x : nodes) {
		int o_degree = 0;
		for(auto e : edges[x]) {
			o_degree += seen[e];
		}
		if(total != nodes.size() - 1) {
			return false;
		}
	}
	return true;
}

struct graph {
	int num_nodes;
	vector<string>nodes;
	int num_edges;
	vector<int>
};