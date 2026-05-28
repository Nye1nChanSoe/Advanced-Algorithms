#include <iostream>
#include <vector>

int fib(int n)
{
    if (n <= 1)
        return n;

    std::vector<int> dp(n + 1);

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main()
{
    std::cout << "Fib(40)=" << fib(40) << std::endl;
    return 0;
}