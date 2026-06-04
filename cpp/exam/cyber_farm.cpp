#include <iostream>
#include <utility>
#include <vector>

int main()
{
    // N number of cucumber pots
    // M number of rains
    // K number of queries
    int N, M, K;
    std::cin >> N >> M >> K;

    // 0 <= li <= ri < N
    std::vector<std::pair<int, int>> m_rains;
    // 0 <= qli <= qri < N
    std::vector<std::pair<int, int>> k_queries;

    for (int i = 0; i < M; i++)
    {
        std::pair<int, int> i_rain;
        std::cin >> i_rain.first >> i_rain.second;
        m_rains.push_back(i_rain);
    }

    for (int i = 0; i < K; i++)
    {
        std::pair<int, int> i_query;
        std::cin >> i_query.first >> i_query.second;
        k_queries.push_back(i_query);
    }

    // build total amount of rain water collected by pots
    // 1 rain = 1 mm
    // [l, r)
    std::vector<int> scanline(N + 1, 0);
    for (int i = 0; i < M; i++)
    {
        int l = m_rains[i].first;
        int r = m_rains[i].second;

        scanline[l] += 1;
        scanline[r] -= 1;
    }

    // sweep
    std::vector<int> collected_rain_in_pots(N);
    int active_rains = 0;

    for (int i = 0; i < N; i++)
    {
        active_rains += scanline[i];
        collected_rain_in_pots[i] = active_rains;
    }

    // prefix sum array for queries
    std::vector<long long> prefix_array(N, 0);
    prefix_array[0] = collected_rain_in_pots[0];
    for (int i = 1; i < N; i++)
    {
        prefix_array[i] = collected_rain_in_pots[i] + prefix_array[i - 1];
    }

    std::vector<long long> answers(K);
    for (int i = 0; i < K; i++)
    {
        int left = k_queries[i].first;
        int right = k_queries[i].second;

        if (left == right)
        {
            answers[i] = 0;
        }
        else if (left == 0)
        {
            answers[i] = prefix_array[right - 1];
        }
        else
        {
            answers[i] = prefix_array[right - 1] - prefix_array[left - 1];
        }
    }

    for (long long ans : answers)
    {
        std::cout << ans << "\n";
    }

    return 0;
}