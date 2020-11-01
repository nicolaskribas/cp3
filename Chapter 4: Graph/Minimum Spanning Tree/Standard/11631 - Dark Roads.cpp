#include <algorithm>
#include <iostream>
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

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    vector<pair<int, pair<int, int>>> edges;

    int m, n;
    while (scanf("%d %d", &m, &n), !(m == 0 && n == 0)) {
        edges.resize(n);
        UnionFind uf(m);

        int total_length = 0;
        for (int i = 0; i < n; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            total_length += z;

            edges[i] = make_pair(z, make_pair(x, y));
        }

        sort(edges.begin(), edges.end());

        int mst_lenght = 0;
        for (auto edge : edges) {
            if (uf.isSameSet(edge.second.first, edge.second.second))
                continue;
            uf.unionSet(edge.second.first, edge.second.second);

            mst_lenght += edge.first;
        }

        printf("%d\n", total_length - mst_lenght);
    }

    return 0;
}
