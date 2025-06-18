# Parallel_Computing_project

## PROJECT #1 
This project implements and compares sequential and parallel versions of the Sieve of Eratosthenes algorithm for finding prime numbers up to a given integer N.
The parallel version uses the Pthreads library and employs a block decomposition strategy.

### Compile the Code:
For the sequential version:
g++ -o sequential sequential.cpp 

For the parallel version:
g++ -o parallel parallel.cpp -pthread

### Run the Programs:
####Sequential:
./sequential

####Parallel:
./parallel

### Default values (n = 1000000, threads = 4):
./parallel

### Custom input: (e.g., n = 10000000, 8 threads):
 ./parallel 10000000 8

## PROJECT #2 – OpenMP-Based Parallel Sieve of Eratosthenes
This project extends the work of Project #1 by implementing a parallel version of the Sieve of Eratosthenes using OpenMP for shared-memory parallelism.
###  Parallelization Approach
The parallel version first generates all base primes up to √n sequentially. Then, it uses OpenMP to parallelize the marking of non-prime numbers across threads. Finally, it parallelizes the counting of prime numbers using reduction.
-  Base sieving (up to √n): sequential.
-  Marking multiples: parallelized with #pragma omp parallel for.
-  Counting primes: parallelized using reduction(+:count).
This approach avoids race conditions and achieves speedup by assigning disjoint work chunks to each thread.

### Compile and Run Instructions
#### Compile: 
g++ -fopenmp -o openmp openmp.cpp

#### Run with default n:
./openmp

### Performance Results
#### Hardware Used
##### CPU Model: Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz   2.00 GHz
##### Cores: 4
##### Threads: 8 
##### RAM: 8 GB
##### OS: Kali Linux/Windows 11 Pro 

####  Tested Input Sizes
| n          | Threads | Sequential Time (ms) | OpenMP Time (ms) | Speedup |
| ---------- | ------- | -------------------- | ---------------- | ------- |
| 100,000    | 4       | 12.4                 | 5.2              | 2.38×   |
| 1,000,000  | 4       | 96.8                 | 28.3             | 3.42×   |
| 10,000,000 | 4       | 932.5                | 267.9            | 3.48×   |

 Note: Results may vary slightly depending on background processes.
 
 #### Graphs
 Time vs input size: 
 ![time_vs_input_size](https://github.com/user-attachments/assets/5ddb151f-b0f7-499b-bf60-06608eb00f7f)

 Speed up vs input size: 
 ![speedup_vs_input_size](https://github.com/user-attachments/assets/3734caf3-168c-4c1e-baae-2295e18b45b9)

### Any Challenges Faced and How You Overcame Them
- ####Race Conditions with vector<bool>
  Switched to std::vector<char>, which offers byte-level storage and thread-safe access when each thread writes to separate indices.
- ####Uneven Work Distribution Across Threads
  Used #pragma omp parallel for schedule(dynamic) to allow OpenMP to dynamically assign loop chunks to threads, improving workload balance.
- ####Correctness Validation
  Extensively tested both versions on multiple input sizes (e.g., 1e5, 1e6, 1e7) and compared counts and printed primes to verify correctness.
- ####Safe Output in Parallel Regions
  Wrapped std::cout inside #pragma omp critical to ensure only one thread prints at a time.
  

 


 ### Repository Structure

```
Parallel_Computing_project_/
├── src/                     # Source code files
│   ├── sequential.cpp       # Sequential implementation
│   └── parallel.cpp         # Parallel (Pthreads) implementation
├── docs/                    # Documentation and graphs
│   ├── report.pdf           # Detailed project report
│   └── graphs/              # Performance graphs
│       ├── time_vs_threads_N100000.png
│       ├── speedup_vs_threads_N100000.png
│       ├── time_vs_threads_N1000000.png
│       ├── speedup_vs_threads_N1000000.png
│       ├── time_vs_threads_N10000000.png
│       └── speedup_vs_threads_N10000000.png
├── results/                 # Raw results 
│   └── timing_data.csv      # Raw benchmark timing data
│
├── Project2
│   └── openmp.cpp
└── README.md                # This file
```
