#include <iostream>
#include <pthread.h>
#include <math.h>
#include <time.h>

using namespace std;
#define NUM_THREADS 4

// Global variables
int N;
bool* isPrime;

// Struct to pass arguments to threads
typedef struct {
    int start;
    int end;
} ThreadArgs;

// Thread function
void* sieve_segment(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int start = args->start;
    int end = args->end;

    for (int i = 2; i * i <= N; ++i) {
        if (isPrime[i]) {
            int j = ((start + i - 1) / i) * i;
            if (j < i * i) j = i * i;

            for (; j <= end; j += i) {
                isPrime[j] = false;
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    N = 100000;
    isPrime = (bool*)malloc((N + 1) * sizeof(bool));

    // Initialize all numbers as prime
    for (int i = 0; i <= N; ++i) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;

    // Timing start
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];

    int segment_size = (N + NUM_THREADS - 1) / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i].start = i * segment_size;
        thread_args[i].end = (i + 1) * segment_size - 1;
        if (thread_args[i].end > N) thread_args[i].end = N;

        pthread_create(&threads[i], NULL, sieve_segment, &thread_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Timing end
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // Count primes
    int prime_count = 0;
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i]) prime_count++;
    }

    printf("Number of primes up to %d: %d\n", N, prime_count);
    printf("Execution time with %d threads: %.3f seconds\n", NUM_THREADS, elapsed);

    free(isPrime);
    return 0;
}
