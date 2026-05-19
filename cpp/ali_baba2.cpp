#include <iostream>
#include <vector>
#include <algorithm>

// 0 <= N <= 100,000 golden sand
// 0 <= W <= 10^9    grams (his bag can hold)

// Input Format (Divided by space character)
// 0 <= N <= 10^5       and    0 <= W <= 10^9
// 0 <= c_i <= 10^9     and    0 <= w_i <= 10^9        (cost and weight)

struct Sand
{
    long long cost;
    long long weight;
};

int main()
{
    int N;
    long long W;

    std::cin >> N >> W;

    std::vector<Sand> sands(N);

    for (int i = 0; i < N; i++)
    {
        // c_i and w_i
        std::cin >> sands[i].cost >> sands[i].weight;
    }

    // Sort by value per gram descending
    sort(sands.begin(), sands.end(), [](Sand a, Sand b)
         { return a.cost * b.weight > b.cost * a.weight; });

    long long answer = 0;

    for (auto s : sands)
    {

        if (W == 0)
            break;

        // Take whole bunch
        if (s.weight <= W)
        {
            answer += s.cost;
            W -= s.weight;
        }
        else
        {
            // Take partial bunch
            answer += (s.cost * W) / s.weight;
            W = 0;
        }
    }

    std::cout << answer << std::endl;

    return 0;
}