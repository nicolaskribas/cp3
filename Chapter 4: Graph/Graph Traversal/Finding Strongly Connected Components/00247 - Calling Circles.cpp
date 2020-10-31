#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define UNVISITED -1

int it;
vector<vector<int>> adj_list, ans;
map<string, int> name_number;
vector<string> number_name;
vector<int> dfs_num, dfs_low, stack, visited;

void tarjan_scc(int u)
{
    dfs_low[u] = dfs_num[u] = it++;
    stack.push_back(u);
    visited[u] = 1;
    for (int v : adj_list[u]) {
        if (dfs_num[v] == UNVISITED)
            tarjan_scc(v);

        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        vector<int> scc;
        while (1) {
            int v = stack.back();
            stack.pop_back();
            visited[v] = 0;
            scc.push_back(v);
            if (u == v)
                break;
        }
        ans.push_back(scc);
    }
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int n, m, number, u, v, set = 1;
    string u_name, v_name;

    bool first_set = true;
    while (scanf("%d %d", &n, &m), !(n == 0 && m == 0)) {
        if(!first_set) cout << '\n';
        first_set = false;

        number = 0;
        adj_list.assign(n, vector<int>());
        ans.clear();
        name_number.clear();
        number_name.clear();

        for (int i = 0; i < m; i++) {
            cin >> u_name >> v_name;
            if (name_number.find(u_name) == name_number.end()) {
                name_number.emplace(make_pair(u_name, number++));
                number_name.push_back(u_name);
            }
            u = name_number[u_name];

            if (name_number.find(v_name) == name_number.end()) {
                name_number.emplace(make_pair(v_name, number++));
                number_name.push_back(v_name);
            }
            v = name_number[v_name];

            adj_list[u].push_back(v);
        }

        dfs_num.assign(n, UNVISITED);
        dfs_low.assign(n, UNVISITED);
        visited.assign(n, 0);
        it = 0;
        for (int i = 0; i < n; i++) {
            if (dfs_num[i] == UNVISITED)
                tarjan_scc(i);
        }

        printf("Calling circles for data set %d:\n", set++);
        for (vector<int> scc : ans) {
            bool first = true;
            for (int number : scc) {
                if (!first)
                    cout << ", ";

                cout << number_name[number];

                first = false;
            }
            cout << '\n';
        }
    }

    return 0;
}
