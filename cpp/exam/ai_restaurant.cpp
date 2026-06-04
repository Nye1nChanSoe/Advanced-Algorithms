#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    // n = number of guests
    // x = number of tables
    // s = seats per table
    int n, x, s;
    std::cin >> n >> x >> s;

    std::string guests;
    std::cin >> guests;

    const int INF = 1e9;

    // dp[used_tables] = minimum available seats in used tables
    // INF means this used_tables count is not reachable
    std::vector<int> dp(x + 1, INF);

    // initially:
    // 0 used tables
    // 0 available seats in used tables
    dp[0] = 0;

    for (char guest : guests)
    {
        // copy = reject this guest
        std::vector<int> next = dp;

        for (int used_tables = 0; used_tables <= x; used_tables++)
        {
            if (dp[used_tables] == INF)
                continue;

            int available_seats = dp[used_tables];

            // Introvert: must use a new unused table
            if ((guest == 'I' || guest == 'A') && used_tables < x)
            {
                int new_used_tables = used_tables + 1;
                int new_available_seats = available_seats + (s - 1);

                next[new_used_tables] =
                    std::min(next[new_used_tables], new_available_seats);
            }

            // Extrovert: must use one available seat in used tables
            if ((guest == 'E' || guest == 'A') && available_seats > 0)
            {
                int new_used_tables = used_tables;
                int new_available_seats = available_seats - 1;

                next[new_used_tables] =
                    std::min(next[new_used_tables], new_available_seats);
            }
        }

        dp = next;
    }

    int answer = 0;

    for (int used_tables = 0; used_tables <= x; used_tables++)
    {
        if (dp[used_tables] == INF)
            continue;

        int available_seats = dp[used_tables];

        int seated_guests =
            used_tables * s - available_seats;

        answer = std::max(answer, seated_guests);
    }

    std::cout << answer << '\n';

    return 0;
}