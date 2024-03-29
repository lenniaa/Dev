#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/** 퇴사 백준_14501 (https://www.acmicpc.net/problem/14501)
 *  * 아주 간단한 점화식 문제, 계산해야 하는 값이 작으므로 dfs로도 풀 수 있다고 함
 *  REVIEW
 *  NOTE
 */

int dp[17];

int max(int a, int b)
{
    return a > b ? a : b;
}

int solution(int n, int *T, int *P)
{

    for (int i = 1; i <= n; i++)
    {
            // 오늘 상담을 하는 경우
            dp[i + T[i]] = max(dp[i + T[i]], dp[i] + P[i]);
            // 오늘 상담을 안하는 경우
            dp[i + 1] = max(dp[i + 1], dp[i]);
        cout << dp[i] << "  ";
    }

    return dp[n+1]; //NOTE why?
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);
    // string str = "7 3 10 5 20 1 10 1 20 2 15 4 40 2 200";                 //45
    // string str2 = "10 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 10";          //55
    // string str3 = "10 5 10 5 9 5 8 5 7 5 6 5 10 5 9 5 8 5 7 5 6";         //20
    // string str4 = "10 5 50 4 40 3 30 2 20 1 10 1 10 2 20 3 30 4 40 5 50"; //90
    // stringstream ss;
    // ss.str(str2);

    ifstream fs("input.txt");

    int N, C;
    fs >> C;
    for (int i = 0; i < C; i++)
    {
        fs >> N;
        int *T = new int[N + 1];
        int *P = new int[N + 1];

        for (int j = 1; j <= N; j++)
        {
            fs >> T[j];
            fs >> P[j];
        }
        cout << solution(N, T, P) << endl;
    }
    return 0;
}