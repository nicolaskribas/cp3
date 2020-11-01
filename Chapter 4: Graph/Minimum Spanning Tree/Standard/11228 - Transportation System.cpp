#include <algorithm>
#include <cmath>
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

double distance(pair<int, int> a, pair<int, int> b)
{
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return hypot(dx, dy);
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    vector<pair<double, pair<int, int>>> edges; //weight, <city u, city v>
    vector<pair<int, int>> cities;
    edges.reserve(2000000);
    cities.reserve(2000);

    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        edges.clear();

        int n, r;
        scanf("%d %d", &n, &r);
        cities.resize(n);
        UnionFind uf(n);
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            cities[i] = make_pair(x, y);
            for (int j = 0; j < i; j++) {
                double dist = distance(cities[i], cities[j]);
                edges.push_back(make_pair(dist, make_pair(i, j)));
            }
        }
        sort(edges.begin(), edges.end());

        int states = 1;
        double roads = 0;
        double railroads = 0;

        for (pair<double, pair<int, int>> edge : edges) {
            if (uf.isSameSet(edge.second.first, edge.second.second))
                continue;

            uf.unionSet(edge.second.first, edge.second.second);

            if (edge.first > r){
                states++;
                railroads += edge.first;
            }else{
                roads += edge.first;
            }
        }

        printf("Case #%d: %d %.0lf %.0lf\n", t, states, round(roads), round(railroads));
    }
    return 0;
}
