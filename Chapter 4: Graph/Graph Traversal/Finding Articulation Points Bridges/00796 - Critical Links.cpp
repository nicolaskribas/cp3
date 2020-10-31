#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define UNVISITED -1

int n, it, dfs_root, root_children;

vector<vector<int>> adj_list;
vector<pair<int, int>> bridges;
vector<int> dfs_num, dfs_low;
vector<int> dfs_parent;

void find_bridges(int u)
{
    dfs_num[u] = dfs_low[u] = it++;

    for (int v : adj_list[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            if (dfs_root == u)
                root_children++;

            find_bridges(v);

            if (dfs_low[v] > dfs_num[u]) {
                bridges.push_back(make_pair(min(u, v), max(u, v)));
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int u, v, n_adj;

    while (scanf("%d", &n) != EOF) {
        dfs_parent.assign(n, 0);
        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        adj_list.assign(n, vector<int>());
        bridges.clear();

        for (int i = 0; i < n; i++) {
            scanf("%d (%d)", &u, &n_adj);
            for (int j = 0; j < n_adj; j++) {
                scanf("%d", &v);
                adj_list[u].push_back(v);
            }
        }

        it = 0;
        for (int i = 0; i < n; i++) {
            if (dfs_num[i] == UNVISITED) {
                dfs_root = i;
                root_children = 0;
                find_bridges(i);
            }
        }

        sort(bridges.begin(), bridges.end());

        printf("%d critical links\n", bridges.size());
        for (int i = 0; i < bridges.size(); i++) {
            printf("%d - %d\n", bridges[i].first, bridges[i].second);
        }
        printf("\n");
    }
}
