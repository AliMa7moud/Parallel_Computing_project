#include <iostream>
#include <vector>
#include <chrono>


int sequentialSieve(int n, bool print_primes = false) {
    if (n < 2) return 0;

    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }

    int count = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            count++;
            if (print_primes) std::cout << i << " ";
        }
    }

    if (print_primes) std::cout << "\n";
    return count;
}

int main(int argc, char* argv[]) {
    int n = 1000000;

    if (argc > 1) {
        n = std::atoi(argv[1]);
    }

    if (n < 2) {
        std::cout << "Please enter a number greater than or equal to 2..\n";
        return 1;
    }

    std::cout << "Sequential Sieve for n = " << n << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    int prime_count = sequentialSieve(n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Found " << prime_count << " primes.\n";
    std::cout << "Execution time: " << duration.count() << " ms\n";

    return 0;
}
