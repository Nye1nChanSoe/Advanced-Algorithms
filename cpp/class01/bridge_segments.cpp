// supplier 'A' pre-cut beams length -> a1, a2, ... , an
// supplier 'B' pre-cut beams length -> b1, b2, ... , bn

// required total span of bridge -> s

// MUST select one beam from `first supplier` and one beam from `second supplier`

// a_i + b_j = s
// if multiple pair exists you may output any one of them.
// if no pair exists output 0 0

// Input Format
// n - the number of beams in each supplier list
// s - the required total length
// a1, a2, ... , an - lengths from the first supplier
// b1, b2, ... , bn - lengths from the second supplier

// Output Format
// print two integers i and j (1-based indices)

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // the number of beams in each supplier list
    int n;
    // the required total length
    long long s;

    std::cin >> n >> s;

    std::vector<long long> a(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    // pair to remember index positions
    std::vector<std::pair<long long, int>> b(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> b[i].first;
        b[i].second = i + 1;
    }

    // b needs to be sorted for b-search
    std::sort(b.begin(), b.end());

    // binary search
    for (int i = 0; i < n; i++)
    {
        long long length_needed = s - a[i];

        int left = 0;
        int right = n - 1;

        while (left <= right)
        {
            int mid = (left + right) / 2;

            // found the right beam
            if (b[mid].first == length_needed)
            {
                // 1-based indices
                std::cout << i + 1 << " " << b[mid].second << std::endl;
                return 0;
            }

            // if lower search space is right
            if (b[mid].first < length_needed)
            {
                left = mid + 1;
            }
            // if higher search space is left
            else
            {
                right = mid - 1;
            }
        }
    }

    std::cout << "0 0" << std::endl;

    return 0;
}