#include <iostream>
#include <omp.h>
#include <math.h>
#include <time.h>

using namespace std;

#define NUM_THREADS 4

int main() {
    int N = 100000;
    bool* isPrime = (bool*)malloc((N + 1) * sizeof(bool));

    // -------Initialize all numbers as prime-------
    for (int i = 0; i <= N; ++i) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;

    // ------Timing start-------
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    omp_set_num_threads(NUM_THREADS);

    int sqrtN = (int)sqrt(N);

    // -------Parallel sieve using OpenMP------
    #pragma omp parallel for schedule(dynamic)
    for (int i = 2; i <= sqrtN; ++i) {
        if (isPrime[i]) {
            int tid = omp_get_thread_num();
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // -----Timing end-----
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // ----Count primes----
    int prime_count = 0;
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i]) prime_count++;
    }

    printf("Number of primes up to %d: %d\n", N, prime_count);
    printf("Execution time with %d threads: %.3f seconds\n", NUM_THREADS, elapsed);

    free(isPrime);
    return 0;
}
