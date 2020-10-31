#include <iostream>
#include <vector>

using namespace std;

#define UNVISITED -1

int it, num_scc;
vector<vector<int>> adj_list(2001);
vector<int> dfs_num(2001), dfs_low(2001), stack(2001);
vector<bool> in_stack(2001);

void tarjan_scc(int u)
{
    dfs_num[u] = dfs_low[u] = it++;
    stack.push_back(u);
    in_stack[u] = true;

    for (int v : adj_list[u]) {
        if (dfs_num[v] == UNVISITED)
            tarjan_scc(v);

        if (in_stack[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_num[u] == dfs_low[u]) {
        num_scc++;
        while (true) {
            int v = stack.back();
            stack.pop_back();
            in_stack[v] = false;
            if (v == u)
                break;
        }
    }
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int n, m;
    while (scanf("%d %d", &n, &m), !(n == 0 && m == 0)) {
        adj_list.assign(n, vector<int>());

        for (int i = 0; i < m; i++) {
            int v, w, p;
            scanf("%d %d %d", &v, &w, &p);
            v -= 1;
            w -= 1;

            adj_list[v].push_back(w);
            if (p == 2)
                adj_list[w].push_back(v);
        }

        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        stack.clear();
        in_stack.assign(n, false);

        it = num_scc = 0;
        for (int i = 0; i < n; i++) {
            if (dfs_num[i] == UNVISITED)
                tarjan_scc(i);
        }
        if (num_scc == 1)
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}
