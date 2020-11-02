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

vector<pair<int, int>> nodes_scoordinates;
vector<pair<double, pair<int, int>>> edges; //<weight, <node u, node v>>

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

    int n;
    scanf("%d", &n);
    while (n--) {
        edges.clear();

        int s, p;
        scanf("%d %d", &s, &p);
        nodes_scoordinates.resize(p);
        for (int i = 0; i < p; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            nodes_scoordinates[i] = make_pair(x, y);
            for (int j = 0; j < i; j++) {
                double dist = distance(nodes_scoordinates[i], nodes_scoordinates[j]);
                edges.push_back(make_pair(dist, make_pair(i, j)));
            }
        }

        sort(edges.begin(), edges.end());
        UnionFind uf(p);

        double d = 0;
        int selected_edges = 0, edges_to_select = p - s;
        for (auto edge : edges) {
            if (uf.isSameSet(edge.second.first, edge.second.second))
                continue;
            uf.unionSet(edge.second.first, edge.second.second);
            selected_edges++;
            d = max(d, edge.first);

            if(selected_edges == edges_to_select) break;
        }
        printf("%.2lf\n", d);
    }
    return 0;
}
