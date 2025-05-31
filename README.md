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
Sequential:
./sequential

Parallel:
./parallel

### Default values (n = 1000000, threads = 4):
./parallel

### Custom input: (e.g., n = 10000000, 8 threads):
 ./parallel 10000000 8

 ### Repository Structure

```
Parallel_Computing_project_1/
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
└── README.md                # This file
```
