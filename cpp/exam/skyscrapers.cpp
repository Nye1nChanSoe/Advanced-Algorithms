#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_N = 50;
const int MAX_SUM = 350;

// reachable[i][a][b] = after considering first i parts,
// can we make tower1 height a and tower2 height b?
bool reachable[MAX_N + 1][MAX_SUM + 1][MAX_SUM + 1];

// for reconstruction:
// action[i][a][b]:
// 0 = part i-1 unused
// 1 = part i-1 used in first tower
// 2 = part i-1 used in second tower
char action_taken[MAX_N + 1][MAX_SUM + 1][MAX_SUM + 1];

int main()
{
    // N: number of parts of pillars 0 < N <= 50
    int N;
    std::cin >> N;

    std::vector<int> h(N);
    int total_sum = 0;

    for (int i = 0; i < N; i++)
    {
        std::cin >> h[i];
        total_sum += h[i];
    }

    reachable[0][0][0] = true;

    // process each part 1 by 1
    for (int i = 1; i <= N; i++)
    {
        int height = h[i - 1];

        for (int a = 0; a <= total_sum; a++)
        {
            for (int b = 0; b <= total_sum; b++)
            {
                if (!reachable[i - 1][a][b])
                    continue;

                // option 1: do not use this part
                if (!reachable[i][a][b])
                {
                    reachable[i][a][b] = true;
                    action_taken[i][a][b] = 0;
                }

                // option 2: put this part into first tower
                if (a + height <= total_sum && !reachable[i][a + height][b])
                {
                    reachable[i][a + height][b] = true;
                    action_taken[i][a + height][b] = 1;
                }

                // option 3: put this part into second tower
                if (b + height <= total_sum && !reachable[i][a][b + height])
                {
                    reachable[i][a][b + height] = true;
                    action_taken[i][a][b + height] = 2;
                }
            }
        }
    }

    // find the best equal height
    // Only check diagonal cells
    int best_height = 0;

    for (int height = 1; height <= total_sum; height++)
    {
        // update best_height to reachable diagonal cell
        if (reachable[N][height][height])
            best_height = height;
    }

    // Reconstruction part:
    std::vector<int> first_tower;
    std::vector<int> second_tower;

    int a = best_height;
    int b = best_height;

    // Walk backward to find which indices created it
    for (int i = N; i >= 1; i--)
    {
        char action = action_taken[i][a][b];

        if (action == 1)
        {
            first_tower.push_back(i - 1);
            a -= h[i - 1];
        }
        else if (action == 2)
        {
            second_tower.push_back(i - 1);
            b -= h[i - 1];
        }
    }

    std::cout << best_height << '\n';

    std::cout << first_tower.size() << '\n';
    for (int index : first_tower)
        std::cout << index << ' ';
    std::cout << '\n';

    std::cout << second_tower.size() << '\n';
    for (int index : second_tower)
        std::cout << index << ' ';
    std::cout << '\n';

    return 0;
}