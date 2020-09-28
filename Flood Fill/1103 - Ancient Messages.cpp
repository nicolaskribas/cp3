#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#define GLYPH_HOLE '0'
#define GLYPH '1'
#define BACKGROUND '2'

using namespace std;

string hex_char_to_bin_string(char hex_char)
{
    switch (hex_char) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'a': return "1010";
    case 'b': return "1011";
    case 'c': return "1100";
    case 'd': return "1101";
    case 'e': return "1110";
    case 'f': return "1111";
    }
    return "0000";
}

int H, W;
char grid[201][201];
                   //N, S, W, E...
const int xd[8] = { 1, -1, 0, 0, 1, -1, -1, 1 };
const int yd[8] = { 0, 0, -1, 1, 1, 1, -1, -1 };

const char glyphs[6] = {'W', 'A', 'K', 'J', 'S', 'D'};

void flood(int i, int j, char from, char to)
{
    if (i < 0 || i >= H)
        return;
    if (j < 0 || j >= W)
        return;
    if (grid[i][j] != from)
        return;

    grid[i][j] = to;

    for (int d = 0; d < 8; d++)
        flood(i + xd[d], j + yd[d], from, to);
}

int count_holes_and_erase_glyph (int i, int j){
    if (i < 0 || i >= H)
        return 0;
    if (j < 0 || j >= W)
        return 0;

    if(grid[i][j] == BACKGROUND) return 0;

    if(grid[i][j] == GLYPH_HOLE){
        flood(i, j, GLYPH_HOLE, BACKGROUND); // flood the hole with background to prevent counting the hole twice
        return 1;
    }

    grid[i][j] = BACKGROUND;

    int ans = 0;

    for(int d = 0; d < 4; d++) ans += count_holes_and_erase_glyph(i + xd[d], j + yd[d]);
    
    return ans;
}

int main(int argc, char const* argv[])
{
    // freopen("../in.txt", "r", stdin);
    // freopen("../out.txt", "w", stdout);

    vector<char> ans;
    char hex_char, glyph_char;
    int n_holes;


    for (int test_case = 1;; test_case++) {
        cin >> H >> W;
        if (!H || !W)
            break;

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> hex_char;
                memcpy(&grid[i][j * 4], hex_char_to_bin_string(hex_char).c_str(), 4 * sizeof(char));
            }
        }

        W *= 4;

        // flood from the left and right border to create the background
        for (int i = 0; i < H; i++) {
            flood(i, 0, GLYPH_HOLE, BACKGROUND);
            flood(i, W - 1, GLYPH_HOLE, BACKGROUND);
        }

        // flood from the top and bottom border to create the background
        for (int j = 0; j < W; j++) {
            flood(0, j, GLYPH_HOLE, BACKGROUND);
            flood(H - 1, j, GLYPH_HOLE, BACKGROUND);
        }

        ans.clear();
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) if (grid[i][j] == GLYPH) {
            n_holes = count_holes_and_erase_glyph(i, j);
            glyph_char = glyphs[n_holes];
            ans.push_back(glyph_char);
        }

        sort(ans.begin(), ans.end());

        cout << "Case " << test_case << ": ";
        for(char glyph_char: ans) cout << glyph_char;
        cout << '\n';

    }
    return 0;
}
