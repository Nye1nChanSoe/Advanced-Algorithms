#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // n: length of cake
    int n;
    std::cin >> n;

    std::vector<int> icing_heights(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> icing_heights[i];
    }

    std::vector<int> icing_heights_leveled_max(n);
    int i = 1;

    long long prefix_sum = 0;
    int best_height = 1e9;

    for (int i = 0; i < n; i++)
    {
        prefix_sum += icing_heights[i];

        // i+1 position averages to level the icing
        int current_average = prefix_sum / (i + 1);
        best_height = std::min(best_height, current_average);

        icing_heights_leveled_max[i] = best_height;
    }

    for (auto x : icing_heights_leveled_max)
    {
        std::cout << x << " ";
    }

    return 0;
}