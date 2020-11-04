#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
#define INF 1000000000

int r, c;

vector<ii> adjacent(ii u)
{
    vector<ii> adj_list;

    if (u.first != 0)
        adj_list.push_back(ii(u.first - 1, u.second));
    if (u.first != r - 1)
        adj_list.push_back(ii(u.first + 1, u.second));
    if (u.second != 0)
        adj_list.push_back(ii(u.first, u.second - 1));
    if (u.second != c - 1)
        adj_list.push_back(ii(u.first, u.second + 1));

    return adj_list;
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    while (scanf("%d %d", &r, &c), r != 0 || c != 0) {
        vector<vi> visited;
        visited.assign(r, vi());
        for (int i = 0; i < r; i++) {
            visited[i].assign(c, -1);
        }

        int rows_with_bombs;
        scanf("%d", &rows_with_bombs);
        while (rows_with_bombs--) {
            int row, bombs_in_the_row;
            scanf("%d %d", &row, &bombs_in_the_row);
            while (bombs_in_the_row--) {
                int column;
                scanf("%d", &column);
                visited[row][column] = 0; //mark bombs location as visited
            }
        }
        ii source, destination;
        scanf("%d %d", &source.first, &source.second);
        scanf("%d %d", &destination.first, &destination.second);

        queue<ii> q;
        q.push(source);
        visited[source.first][source.second] = 0;
        while (!q.empty()) {
            ii u = q.front();
            q.pop();

            for (ii v : adjacent(u)) {
                if (visited[v.first][v.second] == -1) {
                    visited[v.first][v.second] = visited[u.first][u.second] + 1;
                    if (v == destination)
                        break;
                    q.push(v);
                }
            }
        }
        printf("%d\n", visited[destination.first][destination.second]);
    }

    return 0;
}
