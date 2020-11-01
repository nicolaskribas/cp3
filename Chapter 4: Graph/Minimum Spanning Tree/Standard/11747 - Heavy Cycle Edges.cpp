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

    int n, m;
    while (scanf("%d %d", &n, &m), !(n == 0 && m == 0)) {
        UnionFind uf(n);
        edges.resize(m);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            edges[i] = make_pair(w, make_pair(u, v));
        }
        sort(edges.begin(), edges.end());

        vector<int> ans;
        for(auto edge: edges){
            if(uf.isSameSet(edge.second.first, edge.second.second)){
                ans.push_back(edge.first);
            }else{
                uf.unionSet(edge.second.first, edge.second.second);
            }
        }
        if(ans.size() == 0) printf("forest\n");
        else{
            sort(ans.begin(), ans.end());
            bool first = true;
            for(int weight: ans){
                if(!first) printf(" ");
                first = false;
                printf("%d", weight);
            }
            printf("\n");
        }
    }

    return 0;
}
