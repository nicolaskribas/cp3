#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

int in_degree[100];
vector<int> adj_list[100];
string bev_name[100];
map<string, int> bev_idx;
priority_queue<int, vector<int>, greater<int>> bfs_queue;

void bfs_toposort()
{
    while (!bfs_queue.empty()) {
        int bev = bfs_queue.top();
        bfs_queue.pop();

        cout << ' ' << bev_name[bev];

        for (int adj : adj_list[bev]) {
            in_degree[adj]--;
            if (in_degree[adj] == 0)
                bfs_queue.push(adj);
        }

        adj_list[bev].clear();
    }
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int N, M;
    string B1, B2;

    for (int tc = 1; cin >> N; tc++) {
        bev_idx.clear();
        memset(in_degree, 0, sizeof(in_degree));
        for (int i = 0; i < N; i++)
            adj_list[i].clear();

        for (int i = 0; i < N; i++) {
            cin >> bev_name[i];
            bev_idx[bev_name[i]] = i;
        }

        cin >> M;

        for (int i = 0; i < M; i++) {
            cin >> B1 >> B2;
            adj_list[bev_idx[B1]].push_back(bev_idx[B2]);
            in_degree[bev_idx[B2]]++;
        }

        for (int i = 0; i < N; i++)
            if (in_degree[i] == 0)
                bfs_queue.push(i);

        printf("Case #%d: Dilbert should drink beverages in this order:", tc);
        bfs_toposort();
        cout << ".\n\n";
    }
}