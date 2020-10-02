#include <iostream>
#include <queue>
#include <vector>

#define UNCOLORED 2

using namespace std;

bool is_bipartite;
int color[200];
vector<int> adj_list[200];
queue<int> bfs_queue;

void bfs_check_bipartite()
{
    while (!bfs_queue.empty() && is_bipartite) {
        int u = bfs_queue.front();
        bfs_queue.pop();
        for (int v : adj_list[u]) {
            if (color[v] == UNCOLORED) {
                color[v] = 1 - color[u];
                bfs_queue.push(v);
            } else if (color[v] == color[u]) {
                is_bipartite = false;
                break;
            }
        }
    }
}

void add_edge(int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int n, l, u, v;
    while (cin >> n, n) {

        // reset structures
        is_bipartite = true;
        fill(color, color + 200, UNCOLORED);
        for (int i = 0; i < n; i++)
            adj_list[i].clear();
        while (!bfs_queue.empty())
            bfs_queue.pop();

        cin >> l;

        for (int i = 0; i < l; i++) {
            cin >> u >> v;
            add_edge(u, v);
        }

        color[0] = 0;
        bfs_queue.push(0);

        bfs_check_bipartite();

        if (!is_bipartite)
            cout << "NOT ";
        cout << "BICOLORABLE.\n";
    }
}