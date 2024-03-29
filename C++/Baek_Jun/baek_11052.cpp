#include <iostream>
#include <sstream>

using namespace std;

/** 카드 구매하기 백준_11052 (https://www.acmicpc.net/problem/11052)
 *  * 풀었다..
 *  * n개가 든 카드팩 보다 적게든 카드팩으로 n개를 맞춰야함
 *  * dp(n) = n개를 만들수 있는 가짓수중 최댓 값
 *  * ==> n개를 만들려면 어떻게 해야할까?
 *  *한가지를 n번 반복 => n개
 */

int dp[10001];

int max(int a, int b)
{
    return a > b ? a : b;
}

int solution(int *arr, int n)
{

    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            //  REVIEW
            // 정답이긴 한데 어떻게 된 점화식인지 이해가 필요할 듯
            dp[i] = max(arr[i / j] * j, dp[i]);
            dp[i] = max(dp[i], arr[i - j] + dp[j]);
        }
    }
    return dp[n];
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(false);

    string str = "4 1 5 6 7";                        //10
    string str2 = "5 10 9 8 7 6";                    //50
    string str3 = "10 1 1 2 3 5 8 13 21 34 55";      //55
    string str4 = "10 5 10 11 12 13 30 35 40 45 47"; //50
    string str5 = "10 1 100 160 1 1 1 1 1 1 1";      //520  - 2, 2, 3, 3
    stringstream ss;
    ss.str(str5);

    int N;
    ss >> N;

    int *arr = new int[N + 1];
    for (int i = 1; i <= N; i++)
    {
        int tmp;
        ss >> tmp;
        arr[i] = tmp;
    }
    dp[1] = arr[1];
    cout << solution(arr, N) << endl;

    return 0;
}