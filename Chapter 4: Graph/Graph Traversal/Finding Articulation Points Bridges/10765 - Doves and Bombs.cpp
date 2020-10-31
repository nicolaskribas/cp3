#include <algorithm>
#include <bitset>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define UNVISITED -1

vector<vector<int>> adj_list;
vector<pair<int, int>> station_pigeon;
vector<int> dfs_num, dfs_low;
vector<int> dfs_parent;
vector<int> cc;

int it, dfs_root, root_children;

void find_articulation_points(int u)
{
    dfs_num[u] = dfs_low[u] = it++;

    for (int v : adj_list[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            if (dfs_root == u)
                root_children++;

            find_articulation_points(v);

            if (dfs_low[v] >= dfs_num[u]) {
                cc[u]++;
            }
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

void add_edge(int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int n, m, x, y;
    while (scanf("%d %d", &n, &m), !(n == 0 && m == 0)) {
        adj_list.assign(n, vector<int>());
        dfs_low.assign(n, 0);
        dfs_num.assign(n, UNVISITED);
        dfs_parent.assign(n, 0);
        it = 0;
        cc.assign(n, 0);
        station_pigeon.clear();

        while (scanf("%d %d", &x, &y), !(x == -1 && y == -1)) {
            add_edge(x, y);
        }
        for (int i = 0; i < n; i++)
            if (dfs_num[i] == UNVISITED) {
                root_children = 0;
                dfs_root = 0;
                find_articulation_points(0);
                cc[dfs_root] = root_children - 1;
            }

        for (int i = 0; i < n; i++) {
            station_pigeon.push_back(make_pair(i, cc[i] + 1));
        }

        sort(station_pigeon.begin(), station_pigeon.end(), cmp);

        for (int i = 0; i < m; i++) {
            printf("%d %d\n", station_pigeon[i].first, station_pigeon[i].second);
        }
        printf("\n");
    }
}