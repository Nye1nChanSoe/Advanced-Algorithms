// N gears are connected one-by-one
// 0th moves 1st, 1st move 2nd

// You have counted number of teeth on the gears
// Now you want to return gears to the same position as they were in the beginning

// To do that you want to calculate number of rotations of the first gear after
// which EVERY gear will return to the same position as they were before rotating.

// Input Format
// 2 <= N <= 10 : number of gears
// Next line contains N integer numbers 1 <= a_i <= 10^9 : number of teeth on i-th gear

// Output Format
// minimum number of rotates of the first gear after which all gears will return to the same position.

// 3 -> 3 gears
// 10 20 30 -> i-th gears teeth and gears with more teeth move slower

#include <iostream>
#include <vector>
#include <numeric>

long long lcm(long long a, long long b)
{
    return a / std::gcd(a, b) * b;
}

int main()
{
    int N;
    std::cin >> N;

    std::vector<long long> a(N);

    for (int i = 0; i < N; i++)
    {
        std::cin >> a[i];
    }

    long long answer = 1;

    for (int i = 1; i < N; i++)
    {
        // rotations needed for gear i to complete full cycles
        long long need = a[i] / std::gcd(a[0], a[i]);

        // combine all cycle requirements
        answer = lcm(answer, need);
    }

    std::cout << answer << std::endl;

    return 0;
}