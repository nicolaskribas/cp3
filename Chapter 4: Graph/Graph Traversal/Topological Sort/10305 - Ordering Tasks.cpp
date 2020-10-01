#include <bitset>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bitset<101> visited;
vector<int> adj_list[101];
vector<int> toposort;

void dfs_toposort(int i)
{
    if (visited.test(i)) return;

    visited.set(i);

    for (int j : adj_list[i]) dfs_toposort(j);

    toposort.push_back(i);
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int n, m, i, j;

    while (cin >> n >> m, n || m) {
        for (int it = 1; it <= n; it++) adj_list[it].clear();

        for (int it = 0; it < m; it++) {
            cin >> i >> j;
            adj_list[i].push_back(j);
        }

        toposort.clear();
        visited.reset();

        for (int it = 1; it <= n; it++) dfs_toposort(it);

        for (vector<int>::reverse_iterator it = toposort.rbegin();  it != toposort.rend(); it++){
            if(it == toposort.rbegin()) cout << *it;
            else cout << ' ' << *it;
        }
        cout << '\n';
    }
}