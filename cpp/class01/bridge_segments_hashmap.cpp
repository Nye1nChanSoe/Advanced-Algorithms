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
#include <unordered_map>

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

    // O(1) lookups
    std::unordered_map<long long, int> b;

    for (int i = 0; i < n; i++)
    {
        int tmp;
        std::cin >> tmp;
        b[tmp] = i + 1;
    }

    for (int i = 0; i < n; i++)
    {
        long long length_needed = s - a[i];

        // check if a key exists in the container
        if (b.count(length_needed))
        {
            std::cout << i + 1 << " " << b[length_needed] << std::endl;
            return 0;
        }
    }

    std::cout << "0 0" << std::endl;

    return 0;
}