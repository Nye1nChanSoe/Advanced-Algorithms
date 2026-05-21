// Sophia loves to create shorts

// ideas for shorts on the flight = M
// For each short - she knows which episodes are needed to make it
// Since there will be no internet on the flight, she must download the required episodes in advance
// her hard drive can hold (episodes) = K

// she will download exactly `K consecutive episodes`
// and will only make shorts from these episodes

// we need to maximize the number of shorts she can make on the flight

// Input Format
// First line N, M where 1 <= N <= 10^9 and 1 <= M <= 10^5
// N = total number of GOT episodes
// M = the number of short ideas

// M lines
// l_i where 1 <= li <= 10^5  =  the number of episodes required for the short
// next to l_i on the same line there's a_ij where 1 <= a_ij <= N  =  the episode numbers
// * The sum of l_i does not exceed 10^5
// last line contains single integer K where 1 <= K <= N  =  the number of episodes sophia wants to download

// Output Format
// first line = maximum number of shorts she can make
// second line = segment of episodes (L and R)
// where 1 <= L <= R <= N;    R - L + 1 = K

// seems like interval | scanline problem - cause episodes have overlaps for shorts ;)

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

int main()
{
    // Total number of game of throne episodes
    long long N;
    // the number of short ideas
    int M;

    std::cin >> N >> M;

    // number of episodes required for the each short idea M
    // inner vector represent the episode number for each short
    std::vector<std::vector<int>> shorts(M, std::vector<int>(2));

    for (int i = 0; i < M; i++)
    {
        int num_episode_per_shot;
        std::cin >> num_episode_per_shot;

        // [min, max]
        int min_episode = std::numeric_limits<int>::max();
        int max_episode = std::numeric_limits<int>::min();

        for (int j = 0; j < num_episode_per_shot; j++)
        {
            // we will only store [min, max] episode interval here which are needed to make each short
            int episode;
            std::cin >> episode;

            min_episode = std::min(min_episode, episode);
            max_episode = std::max(max_episode, episode);
        }
        shorts[i][0] = min_episode;
        shorts[i][1] = max_episode;
    }

    // number of episodes sophia wants to download "consective"
    long long K;
    std::cin >> K;

    // max number of shorts sophia can make
    int max_shorts = 0;

    // possible download windows [L ... R]
    // where R = L + K - 1
    long long max_start = N - K + 1;

    std::vector<std::vector<long long>> events;

    for (auto vec : shorts)
    {
        long long min_episode = vec[0];
        long long max_episode = vec[1];

        if (max_episode - min_episode + 1 > K)
        {
            continue;
        }

        long long left = max_episode - K + 1;
        long long right = min_episode;

        left = std::max(left, 1LL);
        right = std::min(right, max_start);

        if (left <= right)
        {
            events.push_back({left, 1});
            events.push_back({right + 1, -1});
        }
    }

    std::sort(events.begin(), events.end());

    int active = 0;
    long long best_left = 1;

    for (auto event : events)
    {
        active += event[1];

        if (active > max_shorts && event[0] <= max_start)
        {
            max_shorts = active;
            best_left = event[0];
        }
    }

    std::cout << max_shorts << "\n";
    std::cout << best_left << " " << best_left + K - 1 << "\n";

    return 0;
}