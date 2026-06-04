#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // number of friends Harry invite to party
    int n;
    std::cin >> n;

    // initial positions of friends
    std::vector<long long> friends(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> friends[i];
    }

    std::sort(friends.begin(), friends.end());

    int min_messages = n;
    int x = 0;

    while (x < n)
    {
        int first_index_of_x = x;

        // go to the last index of the same val
        while (x < n && friends[x] == friends[first_index_of_x])
            ++x;

        int last_index_of_x = x - 1;

        // values less than target
        int left = first_index_of_x;

        // values equal to target
        int middle = last_index_of_x - first_index_of_x + 1;

        // values greater than target
        int right = n - left - middle;

        int cost = std::max(left, right);

        min_messages = std::min(min_messages, cost);
    }

    std::cout << min_messages << std::endl;

    return 0;
}