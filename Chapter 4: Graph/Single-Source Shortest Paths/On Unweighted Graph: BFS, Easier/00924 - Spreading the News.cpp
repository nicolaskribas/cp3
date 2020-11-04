#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
#define INF 1000000000

vector<vi> adj_list;

int main(int argc, char const* argv[])
{
    // freopen("../../../in.txt", "r", stdin);
    // freopen("../../../out.txt", "w", stdout);

    int e;
    scanf("%d", &e);
    adj_list.resize(e);
    for (int i = 0; i < e; i++) {
        int n;
        scanf("%d", &n);
        adj_list[i].resize(n);
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj_list[i][j]);
        }
    }

    int t;
    scanf("%d", &t);
    while (t--) {
        int employee;
        scanf("%d", &employee);

        if (adj_list[employee].size() == 0) {
            printf("0\n");
            continue;
        }
        vi visited;
        visited.assign(e, -1); 
        visited[employee] = 0;

        vi day_size;
        day_size.assign(e, 0);

        queue<int> q; q.push(employee);
        
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v: adj_list[u]){
                if(visited[v] == -1){
                    visited[v] = visited[u] + 1;
                    day_size[visited[v]]++;

                    q.push(v);
                }
            }
        }
        ii ans = ii(0,0);
        for(int i = 0; i < day_size.size(); i++){
            if(day_size[i] > ans.first){
                ans.first = day_size[i];
                ans.second = i;
            }
        }
        printf("%d %d\n", ans.first, ans.second);
    }
}
