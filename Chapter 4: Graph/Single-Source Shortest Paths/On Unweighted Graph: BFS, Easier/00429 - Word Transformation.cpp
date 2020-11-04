#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
#define INF 1000000000

bool has_one_letter_difference(string a, string b)
{
    if (a.size() != b.size())
        return false;

    int diff = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            diff++;
    }

    if (diff == 1)
        return true;

    return false;
}

vector<vi> adj_list;
void add_edge(int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int N;
    scanf("%d", &N);
    for(int n = 0 ; n < N; n++) {
        if(n != 0 ) printf("\n");
        adj_list.clear();
        vector<string> dictionary;
        map<string, int> index;
        for (int u = 0;; u++) {
            string s;
            cin >> s;
            if (s.compare("*") == 0)
                break;

            dictionary.push_back(s);
            index[s] = u;

            adj_list.push_back(vi());
            for (int v = 0; v < u; v++) {
                if (has_one_letter_difference(dictionary[u], dictionary[v]))
                    add_edge(u, v);
            }
        }
        cin.ignore();
        string line, start, end;

        while (getline(cin, line)) {
            if (line.compare("") == 0)
                break;

            stringstream ss(line);
            ss >> start >> end;
            int s = index[start], e = index[end];

            vi distance;
            distance.assign(dictionary.size(), INF);
            distance[s] = 0;
            queue<int> q;
            q.push(s);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj_list[u]) {
                    if (distance[v] == INF) {
                        distance[v] = distance[u] + 1;
                        q.push(v);
                    }
                }
            }
            printf("%s %s %d\n", start.c_str(), end.c_str(), distance[e]);
        }
    }

    return 0;
}
