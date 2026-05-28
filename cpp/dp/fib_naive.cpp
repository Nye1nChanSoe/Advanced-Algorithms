#include <iostream>
#include <chrono>

int fib(int n)
{
    if (n < 2)
        return n;

    return fib(n - 1) + fib(n - 2);
}

int main()
{
    std::cout << "Fib with naive approach" << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Result: " << fib(40) << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << "ms" << std::endl;

    return 0;
}