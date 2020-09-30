#include <iostream>

using namespace std;

int N;
char grid[105][105];

bool inGrid(int i, int j)
{
    return (i >= 0 && i < N && j >= 0 && j < N);
}

int flood(int i, int j)
{
    if (!inGrid(i, j)) return 0;
    if (grid[i][j] == '.') return 0;

    int ret = 0;
    if (grid[i][j] == 'x') ret = 1;

    grid[i][j] = '.';

    ret |= flood(i + 1, j);
    ret |= flood(i - 1, j);
    ret |= flood(i, j + 1);
    ret |= flood(i, j - 1);

    return ret;
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int T, ans;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> grid[i][j];

        ans = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                ans += flood(i, j);

        printf("Case %d: %d\n", t, ans);
    }
    return 0;
}
