#include <iostream>
#include <queue>
#include <vector>

#define UNCOLORED 2

using namespace std;

bool is_bipartite;
int color[200];
int colored_count[2];

vector<int> adj_list[200];
queue<int> bfs_queue;

int bfs_bipartite_check(int start)
{
    bfs_queue.push(start);
    color[start] = 0;
    colored_count[0] = 1;
    colored_count[1] = 0;

    while (!bfs_queue.empty() && is_bipartite) {
        int u = bfs_queue.front();
        bfs_queue.pop();
        for (int v : adj_list[u]) {
            if (color[v] == UNCOLORED) {
                color[v] = 1 - color[u];
                colored_count[color[v]]++;
                bfs_queue.push(v);
            } else if (color[u] == color[v]) {
                is_bipartite = false;
                break;
            }
        }
    }

    if (min(colored_count[0], colored_count[1]) == 0)
        return max(colored_count[0], colored_count[1]);
    else
        return min(colored_count[0], colored_count[1]);
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

    int T, v, e, f, t, ans;
    cin >> T;

    while (T--) {

        // reset structures
        ans = 0;
        is_bipartite = true;
        fill(color, color + 200, UNCOLORED);
        for (int i = 0; i < 200; i++)
            adj_list[i].clear();
        while (!bfs_queue.empty())
            bfs_queue.pop();

        cin >> v >> e;
        for (int i = 0; i < e; i++) {
            cin >> f >> t;
            add_edge(f, t);
        }

        for (int i = 0; i < v && is_bipartite; i++) {
            if (color[i] == UNCOLORED) {
                ans += bfs_bipartite_check(i);
            }
        }
        if (!is_bipartite)
            cout << "-1\n";
        else
            cout << ans << '\n';
    }
}