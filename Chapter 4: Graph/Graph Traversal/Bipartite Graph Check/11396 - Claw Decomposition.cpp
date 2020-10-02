#include <iostream>
#include <queue>
#include <vector>

#define UNCOLORED 2

using namespace std;

bool is_bipartite;
int color[300];

vector<int> adj_list[300];
queue<int> bfs_queue;

void bfs_bipartite_check()
{
    while (!bfs_queue.empty() && is_bipartite) {
        int u = bfs_queue.front();
        bfs_queue.pop();
        for (int v : adj_list[u]) {
            if (color[v] == UNCOLORED) {
                color[v] = 1 - color[u];
                bfs_queue.push(v);
            } else if (color[u] == color[v]) {
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

    int V, a, b;
    while (cin >> V, V) {

        is_bipartite = true;
        fill(color, color + 300, UNCOLORED);
        for (int i = 0; i < 300; i++)
            adj_list[i].clear();
        while (!bfs_queue.empty())
            bfs_queue.pop();

        while (cin >> a >> b, a || b)
            add_edge(a - 1, b - 1);

        color[0] = 0;
        bfs_queue.push(0);

        bfs_bipartite_check();

        if (is_bipartite)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}