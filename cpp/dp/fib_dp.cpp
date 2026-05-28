#include <iostream>
#include <algorithm>
#include <chrono>

int memo[1001];

int fib(int n)
{
    if (n < 2)
        return n;

    if (memo[n] != -1)
        return memo[n];

    memo[n] = fib(n - 1) + fib(n - 2);
    return memo[n];
}

int main()
{
    std::cout << "Fib with dp approach" << "\n";
    std::fill(memo, memo + 1001, -1);

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Result: " << fib(40) << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << "ms" << std::endl;

    return 0;
}