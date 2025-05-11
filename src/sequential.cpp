#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// Sequential Sieve of Eratosthenes
void sieveOfEratosthenes(int N, vector<bool>& isPrime) {
    isPrime.assign(N + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= N; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
        }
    }
}

int main() {
    int N = 10000000;  
    vector<bool> isPrime;

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    sieveOfEratosthenes(N, isPrime);

    // End timing
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    // Count and print number of primes
    int count = 0;
    for (int i = 2; i <= N; ++i)
        if (isPrime[i]) count++;

    cout << "Number of primes up to " << N << ": " << count << endl;
    cout << "Execution Time (sequential): " << duration << " ms" << endl;

    return 0;
}
