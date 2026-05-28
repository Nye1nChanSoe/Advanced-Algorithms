// substring = sequence must be continuous
// subsequence = can skip characters: order must be same

// unlike substrings, subsequences are not required to
// occupy consecutive positions within the original sequences.

// Find the Longest Common Subsequence

// order preserved
// no necessarily contiguous

#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string A = "ABCBDAB";
    std::string B = "BDCAB";

    int n = A.size();
    int m = B.size();

    // 2D table: rows = A | cols = B
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {

            // Characters match
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }

            // Characters don't match
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    std::cout << "LCS Length = " << dp[n][m] << std::endl;
}