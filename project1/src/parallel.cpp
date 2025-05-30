#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <pthread.h>

     
struct ThreadData {
    int id;
    int num_threads;
    int n;
    std::vector<bool>* is_prime;
};


void* sieveWorker(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->n;
    int id = data->id;
    int num_threads = data->num_threads;
    std::vector<bool>& is_prime = *(data->is_prime);
    int sqrt_n = static_cast<int>(sqrt(n));

    int block_size = (n - 1) / num_threads;
    int start = 2 + id * block_size;
    int end = (id == num_threads - 1) ? n : start + block_size - 1;

    for (int p = 2; p <= sqrt_n; ++p) {
        if (is_prime[p]) {
            int first = (start / p) * p;
            if (first < start) first += p;
            if (first < p * p) first = p * p;

            for (int i = first; i <= end; i += p) {
                is_prime[i] = false;
            }
        }
    }

    pthread_exit(NULL);
}


int parallelSieve(int n, int num_threads) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    int sqrt_n = static_cast<int>(sqrt(n));

  
    for (int p = 2; p <= sqrt_n; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime[i] = false;
            }
        }
    }

    pthread_t threads[num_threads];
    ThreadData data[num_threads];

   
    for (int i = 0; i < num_threads; ++i) {
        data[i] = {i, num_threads, n, &is_prime};
        pthread_create(&threads[i], NULL, sieveWorker, (void*)&data[i]);
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    
    int count = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) count++;
    }

    return count;
}

int main(int argc, char* argv[]) {
    int n = 1000000;
    int threads = 4;

    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) threads = atoi(argv[2]);

    std::cout << "Running parallel sieve for n = " << n << " using " << threads << " threads.\n";

    auto start = std::chrono::high_resolution_clock::now();
    int count = parallelSieve(n, threads);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Found " << count << " prime numbers.\n";
    std::cout << "Execution time: " << duration.count() << " ms\n";

    return 0;
}
