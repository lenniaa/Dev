#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, t, res;
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vector<vector<bool>> visit(100, vector<bool>(100, false));
vector<int> tasty(100, 0);

int max(int &a, int &b) { return a > b ? a : b; }
int min(int &a, int &b) { return a < b ? a : b; }

// calculate a block of cheese
int calc(vector<vector<int>> &cheese, int taste)
{
    int ret = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // bfs start
            if (cheese[i][j] > taste && !visit[i][j])
            {
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                visit[i][j] = true;

                while (!q.empty())
                {
                    int cury = q.front().first, curx = q.front().second;

                    for (int k = 0; k < 4; k++)
                    {
                        int ny = dir[k][0] + cury;
                        int nx = dir[k][1] + curx;

                        if (ny >= 0 && nx >= 0 && ny < n && nx < n)
                        {
                            if (cheese[ny][nx] > taste && !visit[ny][nx])
                            {
                                q.push(make_pair(ny, nx));
                                visit[ny][nx] = true;
                            }
                        }
                    }
                    q.pop();
                }
                // bfs가 끝날때 마다 1씩 증가해 덩어리수 확인
                ret++;
            } // end of bfs
        }
    }

    return ret;
}

void dfs(vector<vector<int>> &cheese, int cury, int curx, int taste)
{
    for (int i = 0; i < 4; i++)
    {
        int ny = dir[i][0] + cury;
        int nx = dir[i][1] + curx;

        if (ny >= 0 && nx >= 0 && ny < n && nx < n)
        {
            if (cheese[ny][nx] > taste && !visit[ny][nx])
            {
                visit[ny][nx] = true;
                dfs(cheese, ny, nx, taste);
            }
        }
    }
    res++;
}

int solution(vector<vector<int>> &cheese)
{
    int ans = 0;
    // the range of taste of cheese
    for (int i = 0; i < 100; i++)
    {
        if (tasty[i] != 0)
            ans = max(ans, calc(cheese, i));
    }

    return ans;
}

int main(int argc, char const *argv[])
{
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        chrono::system_clock::time_point start = chrono::system_clock::now();

        cin >> n;

        vector<vector<int>> cheese(n, vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int tmp;
                cin >> tmp;
                cheese[i][j] = tmp;

                if (tasty[tmp] != 0)
                    tasty[tmp]++;
            }
        }

        // remve duplicated elements
        // sort(tasty.begin(), tasty.end());
        // tasty.erase(unique(tasty.begin(), tasty.end()), tasty.end());

        std::cout << "#" << tc << " " << solution(cheese) << endl;

        std::cout << chrono::duration<double>(chrono::system_clock::now() - start).count() << " sec" << endl;

        tasty.assign(100, 0);
        for (vector<bool> vec : visit)
            vec.assign(100, false);
    }

    return 0;
}