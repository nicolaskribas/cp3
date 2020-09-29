#include <iostream>

using namespace std;

int M, N, X, Y;
char land, water;
char grid[20][20];

bool inGrid(int i, int j){
    return (i >= 0 && i < M && j >= 0 && j < N);
}

int wrap(int n){
    return ((n % N) + N) % N;
}

int flood(int i, int j)
{

    if (!inGrid(i, j))
        return 0;
    if (grid[i][j] != land)
        return 0;

    grid[i][j] = water;

    int ans;

    if (i == X && j == Y)
        ans = -400;
    else
        ans = 1;

    ans += flood(i + 1, j);
    ans += flood(i - 1, j);
    ans += flood(i, wrap(j + 1));
    ans += flood(i, wrap(j - 1));

    return ans;
}

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int ans;
    while (cin >> M >> N) {
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                cin >> grid[i][j];
        cin >> X >> Y;

        land = grid[X][Y];
        water = land == 'a' ? 'b' : 'a';

        ans = 0;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                ans = max(ans, flood(i, j));

        cout << ans << '\n';
    }

    return 0;
}
