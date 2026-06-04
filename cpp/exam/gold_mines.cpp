#include <iostream>
#include <vector>

int main()
{
    // gold mine produce K unit of gold per turn
    // building new mine takes T time and cost S gold
    // game ends after N turns
    long long k, T, S, N;
    std::cin >> k >> T >> S >> N;

    // gold and gold mine i have at the beginning
    long long gold = 0;
    long long active_mines = 1;

    // index = turns needed to build
    // value = number of gold mines
    std::vector<long long> building_queue(T, 0);

    for (long long turn = 1; turn <= N; turn++)
    {
        active_mines += building_queue[0];

        // shift gold mine construction building_queue
        for (long long i = 0; i < T - 1; i++)
        {
            building_queue[i] = building_queue[i + 1];
        }
        building_queue[T - 1] = 0;

        long long remaining_turns = N - (turn + T) + 1;

        // as long as the remaining turns * k (gold mine production) exceeds it's cost
        // we will build new gold mines
        if (remaining_turns > 0 && remaining_turns * k > S)
        {
            long long max_build = gold / S;

            gold -= max_build * S;

            building_queue[T - 1] += max_build;
        }

        gold += active_mines * k;
    }

    std::cout << gold << std::endl;

    return 0;
}