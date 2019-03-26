#include <algorithm>
#include <iostream>
#include <vector>

/** 프린터 큐 백준_1966 ( https://www.acmicpc.net/problem/1966 )
 *
 */

using namespace std;

vector<pair<int, int>> arr;

int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m, ans = 0, chk; // n : 문서의 수, m : 궁금한 문서의 현재 큐의 위치
        scanf("%d %d", &n, &m);
        arr.assign(n, make_pair(0, 0));
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        arr[m].second = 1;

        if (n == 1)
        {
            ans = 1;
        }
        else
        {
            // main routine
            while (!arr.empty())
            {
                chk = arr.front().first;
                auto itr = find_if(arr.begin(), arr.end(), [&chk](pair<int, int> a) { return chk < a.first ? true : false; });
                if (arr.end() != itr)
                {
                    arr.push_back(arr.front());
                    arr.erase(arr.begin());
                }
                else
                {
                    if (arr.front().second != 1)
                    {
                        arr.erase(arr.begin());
                        ans++;
                    }
                    else
                    {
                        ans++;
                        break;
                    }
                }
            }
        }
        printf("%d\n", ans);
        arr.clear();
    }
    return 0;
}