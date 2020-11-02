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

int n;
vector<pair<int, pair<int, int>>> edges;

int kruskal(int deleted_edge)
{
    UnionFind uf(n + 1);
    int s2 = 0, n_edges = 0;
    for (int i = 0; i < edges.size(); i++) {
        if (i == deleted_edge)
            continue;
        if (uf.isSameSet(edges[i].second.first, edges[i].second.second))
            continue;

        uf.unionSet(edges[i].second.first, edges[i].second.second);
        s2 += edges[i].first;
        n_edges++;
    }
    if(n_edges < n - 1) return 300 *100;
    return s2;
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int t;
    scanf("%d", &t);
    while (t--) {
        int m;
        scanf("%d %d", &n, &m);
        edges.clear();
        edges.reserve(m);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            edges.push_back(make_pair(c, make_pair(a, b)));
        }
        sort(edges.begin(), edges.end());

        UnionFind uf(n + 1);
        int s1 = 0, s2 = 300 * 100;
        for (int i = 0; i < edges.size(); i++) {
            if (uf.isSameSet(edges[i].second.first, edges[i].second.second))
                continue;
            uf.unionSet(edges[i].second.first, edges[i].second.second);

            s1 += edges[i].first;
            s2 = min(s2, kruskal(i));
        }
        printf("%d %d\n", s1, s2);
    }
    return 0;
}
