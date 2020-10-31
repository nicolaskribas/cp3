#include <iostream>
#include <vector>

using namespace std;

#define UNVISITED -1

int it, num_scc;
vector<vector<int>> adj_list(100000);
vector<int> dfs_num(100000), dfs_low(100000), stack(100000);
vector<int> scc(100000);
vector<bool> same_scc(100000), has_in_edge(100000);

void tarjan_scc(int u)
{
    dfs_num[u] = dfs_low[u] = it++;
    same_scc[u] = true;
    stack.push_back(u);

    for(int v: adj_list[u]){
        if(dfs_num[v] == UNVISITED){
            tarjan_scc(v);
        }

        if(same_scc[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        else
            has_in_edge[scc[v]] = true;


    }

    if(dfs_num[u] == dfs_low[u]){
        num_scc++;
        while(true){
            int v = stack.back();
            stack.pop_back();
            same_scc[v] = false;
            scc[v] = num_scc;
            if(u == v) break;
        }
    }

}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int tc;
    scanf("%d", &tc);
    while (tc--) {
        int n, m;
        scanf("%d %d", &n, &m);
        adj_list.assign(n, vector<int>());

        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj_list[u - 1].push_back(v - 1);
        }

        it = num_scc = 0;
        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, 0);
        same_scc.assign(n, false);
        has_in_edge.assign(n, false);
        scc.assign(n, -1);
        stack.clear();

        for (int i = 0; i < n; i++)
            if (dfs_num[i] == UNVISITED)
                tarjan_scc(i);

        int ans = 0;
        for(int i = 0; i < num_scc; i++){
            if(!has_in_edge[i]) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
