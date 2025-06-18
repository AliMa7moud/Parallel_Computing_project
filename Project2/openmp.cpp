#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <omp.h>

// ------ Parallel Sieve Function ------
int parallelSieve(int n, bool print_primes = false) {
    // ------ Handle edge case ------
    if (n < 2) return 0;

    // ------ Initialize prime flags ------
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    int sqrt_n = static_cast<int>(std::sqrt(n));

    // ------ Step 1: Sieve base primes up to sqrt(n) sequentially ------
    for (int p = 2; p * p <= sqrt_n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= sqrt_n; i += p) {
                is_prime[i] = false;
            }
        }
    }

    // ------ Step 2: Mark non-primes in parallel using base primes ------
    #pragma omp parallel for schedule(dynamic)
    for (int p = 2; p <= sqrt_n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }

    // ------ Step 3: Count primes in parallel ------
    int count = 0;
    #pragma omp parallel for reduction(+:count)
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            count++;
            if (print_primes) {
                #pragma omp critical
                std::cout << i << " ";
            }
        }
    }

    if (print_primes) std::cout << "\n";
    return count;
}

// ------ Main Function ------
int main(int argc, char* argv[]) {
    int n = 1000000;

    // ------ Read command-line argument if available ------
    if (argc > 1) {
        n = std::atoi(argv[1]);
    }

    // ------ Handle invalid input ------
    if (n < 2) {
        std::cout << "Please enter a number greater than or equal to 2..\n";
        return 1;
    }

    std::cout << "Parallel Sieve for n = " << n << "\n";

    // ------ Start timing ------
    auto start = std::chrono::high_resolution_clock::now();
    int prime_count = parallelSieve(n);
    auto end = std::chrono::high_resolution_clock::now();

    // ------ Calculate and display time ------
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Found " << prime_count << " primes.\n";
    std::cout << "Execution time: " << duration.count() << " ms\n";

    return 0;
}
