// The problem
// For every mathematician i, we have:

// a_i = attack skill
// b_i = defense skill

// Real thrill
// (a_i + b_j) (a_j + b_i)

// Public expected thrill
// (a_i + b_i)^2 + (a_j + b_j)^2  /  2

// Find two different people i and j such that:
// ∣real thrill−expected thrill∣ is as small as possible

// Input format
// N (2 <= N <= 200,000)
// The next N lines describe the candidates
// Each line contains two integer numbers: a_i and b_i (characteristics of i-th candidate)
// 1 <= ai, bi <= 10^9

// Output Format
// Print two different integer numbers: the number of competitors in any one optimal match
// The candidates are numbered starting from 1 according to their order in the input
// The numbers of competitors can be printed in any order

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <limits>

struct Point
{
    long long x, y;
    int id;
};

long long dist2(const Point &a, const Point &b)
{
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main()
{
    int N;
    std::cin >> N;

    std::vector<Point> points(N);

    for (int i = 0; i < N; i++)
    {
        std::cin >> points[i].x >> points[i].y;
        points[i].id = i + 1;
    }

    std::sort(points.begin(), points.end(), [](const Point &a, const Point &b)
              {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y; });

    long long best = dist2(points[0], points[1]);
    int ans1 = points[0].id;
    int ans2 = points[1].id;

    std::set<std::pair<long long, int>> active;
    // stores {y, index in sorted points}

    active.insert({points[0].y, 0});

    int left = 0;

    for (int i = 1; i < N; i++)
    {
        Point current = points[i];

        while (left < i)
        {
            long long dx = current.x - points[left].x;

            if (dx * dx < best)
                break;

            active.erase({points[left].y, left});
            left++;
        }

        long long limit = std::sqrt((long double)best) + 1;

        auto lower = active.lower_bound({current.y - limit, -1});

        for (auto it = lower; it != active.end(); ++it)
        {
            long long y = it->first;

            if (y > current.y + limit)
                break;

            int idx = it->second;
            long long d = dist2(current, points[idx]);

            if (d < best)
            {
                best = d;
                ans1 = current.id;
                ans2 = points[idx].id;
            }
        }

        active.insert({current.y, i});
    }

    std::cout << ans1 << " " << ans2 << '\n';

    return 0;
}