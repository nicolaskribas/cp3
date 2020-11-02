#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class UnionFind {
private:
    vector<int> p, rank;

public:
    UnionFind(int N)
    {
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j)) {
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y])
                p[y] = x;
            else {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
};

vector<vector<pair<int, int>>> adj_list; // pair<adj, cost>
vector<int> visited;
vector<pair<int, int>> prev_weight;

void add_edge(int u, int v, int cost)
{
    adj_list[u].push_back(make_pair(v, cost));
    adj_list[v].push_back(make_pair(u, cost));
}

bool bfs(int src, int target)
{
    queue<int> q;
    visited[src] = 1;

    q.push(src);

    while (!q.empty())
    {
        int u = q.front(); q.pop();

        if(u == target) return true;

        for(auto v: adj_list[u]){
            if(!visited[v.first]){
                prev_weight[v.first] = make_pair(u, v.second);
                visited[v.first] = 1;
                q.push(v.first);
            }
        }
    }
    return false;    
}

int backtrack(int src, int target){
    int maxWeight = 0;
    while(src != target){
        maxWeight = max(maxWeight, prev_weight[src].second);
        src = prev_weight[src].first;
    }
    return maxWeight;
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    vector<pair<int, pair<int, int>>> edges; //<weight, <crossing u,crossing v>>

    int c, s, q, tc = 1;
    while (scanf("%d %d %d", &c, &s, &q), !(c == 0 && s == 0 && q == 0)) {
        UnionFind uf(c + 1);
        adj_list.assign(c + 1, vector<pair<int, int>>());
        visited.assign(c + 1, 0);
        edges.resize(s);

        for (int i = 0; i < s; i++) {
            int c1, c2, d;
            scanf("%d %d %d", &c1, &c2, &d);
            edges[i] = make_pair(d, make_pair(c1, c2));
        }

        sort(edges.begin(), edges.end());

        for (auto edge : edges) {
            if (uf.isSameSet(edge.second.first, edge.second.second))
                continue;

            uf.unionSet(edge.second.first, edge.second.second);

            add_edge(edge.second.first, edge.second.second, edge.first);
        }
        if(tc != 1) printf("\n");
        printf("Case #%d\n", tc++);
        for (int i = 0; i < q; i++) {

            int c1, c2;
            scanf("%d %d", &c1, &c2);

            prev_weight.assign(c + 1, pair<int, int>());
            visited.assign(c + 1, 0);
            if (bfs(c1, c2)) {
                printf("%d\n", backtrack(c2, c1));
            } else {
                printf("no path\n");
            }
        }
    }

    return 0;
}
