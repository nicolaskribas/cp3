#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int ctoi(char c)
{
    return c - 'A';
}

char itoc(int i)
{
    return i + 'A';
}

bool has_solution;
vector<int> nodes;
vector<int> adj_list[26];
bitset<26> visited;

int ans[26];

bool is_valid(int i)
{
    for (int adj : adj_list[i])
        if (visited.test(adj))
            return false;

    return true;
}

void backtrack_toposort(int idx)
{
    if (idx == nodes.size()) {
        cout << itoc(ans[0]);
        for (int i = 1; i < idx; i++)
            cout << ' ' << itoc(ans[i]);
        cout << '\n';

        has_solution = true;
        return;
    }

    for (int i = 0; i < nodes.size(); i++) {
        if (visited.test(nodes[i]))
            continue;

        if (!is_valid(nodes[i]))
            continue;

        visited.set(nodes[i]);
        ans[idx] = nodes[i];
        backtrack_toposort(idx + 1);
        visited.reset(nodes[i]);
    }
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    char c1, c2, skip_char;
    string line;
    stringstream line_stream;

    int T;
    cin >> T;

    while (T--) {
        has_solution = false;
        nodes.clear();
        visited.reset();
        for (int i = 0; i < 26; i++)
            adj_list[i].clear();

        scanf("\n");

        getline(cin, line);
        line_stream.clear();
        line_stream.str(line);

        while (line_stream >> c1)
            nodes.push_back(ctoi(c1));
        sort(nodes.begin(), nodes.end());

        getline(cin, line);
        line_stream.clear();
        line_stream.str(line);

        while (line_stream >> c1 >> skip_char >> c2)
            adj_list[ctoi(c1)].push_back(ctoi(c2));

        backtrack_toposort(0);

        if (!has_solution)
            cout << "NO\n";

        if (T)
            cout << '\n';
    }

    return 0;
}
