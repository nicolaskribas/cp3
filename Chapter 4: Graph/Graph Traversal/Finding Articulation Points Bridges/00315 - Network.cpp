#include <bitset>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<int>> adj_list;
bitset<100> visited;

void bfs(int u)
{
    queue<int> bfs_queue;
    visited.set(u);
    bfs_queue.push(u);

    while (!bfs_queue.empty()) {
        u = bfs_queue.front();
        bfs_queue.pop();

        for (int adj : adj_list[u]) {
            if (visited.test(adj))
                continue;

            visited.set(adj);
            bfs_queue.push(adj);
        }
    }
}

int connected_components(int articulation_candidate)
{
    int cc = 0;
    visited.reset();
    if (articulation_candidate != -1)
        visited.set(articulation_candidate);

    for (int u = 0; u < adj_list.size(); u++) {
        if (visited.test(u))
            continue;
        cc++;
        bfs(u);
    }
    return cc;
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

    int N, u, v, cc, articulation_points;
    string line;
    stringstream line_stream;
    while (cin >> N, N != 0) {
        articulation_points = 0;
        adj_list.assign(N, vector<int>());

        while (true) {

            scanf("\n");

            getline(cin, line);
            line_stream.clear();
            line_stream.str(line);

            line_stream >> u;
            if (u == 0)
                break;

            while (line_stream >> v)
                add_edge(u - 1, v - 1);
        }

        cc = connected_components(-1);

        for (u = 0; u < N; u++) {
            if (connected_components(u) > cc)
                articulation_points++;
        }

        cout << articulation_points << '\n';
    }
}