#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

struct Point
{
    double x;
    double y;
    double z;
};

double distance_between(const Point &a, const Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double max_distance_from_base(const Point &base, const std::vector<Point> &planets)
{
    double max_distance = 0.0;

    for (const Point &planet : planets)
    {
        max_distance = std::max(max_distance, distance_between(base, planet));
    }

    return max_distance;
}

int main()
{
    // n: number of planets
    // 1 <= n <= 100
    int n;
    std::cin >> n;

    std::vector<Point> planets(n);

    for (int i = 0; i < n; i++)
    {
        // xi, yi, zi: coordinate of i-th planet in 3D space
        // -10000 <= xi, yi, zi <= 10000
        std::cin >> planets[i].x >> planets[i].y >> planets[i].z;
    }

    // Start at centroid of all planets as initial guess
    Point answer{0.0, 0.0, 0.0};
    for (const Point &p : planets)
    {
        answer.x += p.x;
        answer.y += p.y;
        answer.z += p.z;
    }
    answer.x /= n;
    answer.y /= n;
    answer.z /= n;

    // Iterative search: start with large step, shrink gradually.
    double step = 20000.0;

    while (step > 1e-9)
    {
        // Find the farthest planet from current base
        Point farthest = planets[0];
        double best_dist = distance_between(answer, planets[0]);

        for (const Point &planet : planets)
        {
            double d = distance_between(answer, planet);
            if (d > best_dist)
            {
                best_dist = d;
                farthest = planet;
            }
        }

        // Move one step toward the farthest planet
        Point candidate;
        candidate.x = answer.x + step * (farthest.x - answer.x) / best_dist;
        candidate.y = answer.y + step * (farthest.y - answer.y) / best_dist;
        candidate.z = answer.z + step * (farthest.z - answer.z) / best_dist;

        // Accept if it improves the objective
        if (max_distance_from_base(candidate, planets) < max_distance_from_base(answer, planets))
        {
            answer = candidate;
        }
        else
        {
            // Shrink step size
            step *= 0.5;
        }
    }

    std::cout << std::fixed << std::setprecision(10);
    std::cout << answer.x << ' ' << answer.y << ' ' << answer.z << '\n';

    return 0;
}