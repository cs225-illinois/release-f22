/**
 * @file benchmark.h
 * Class for easy runtime benchmarks that can output to simple two column
 * csv files.
 */
#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>

/**
 * Class which contains a collection of benchmark results.
 */
class Benchmark
{
  private:
    /**
     * Contains the actual results / benchmark parameter, uses std::chrono.
     */
    struct BenchmarkResult {
        unsigned int n;
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point end_time;
        BenchmarkResult(unsigned int n,
                        std::chrono::high_resolution_clock::time_point s,
                        std::chrono::high_resolution_clock::time_point e)
            : n(n), start_time(s), end_time(e)
        {
        }
    };

    std::vector<BenchmarkResult> results;
    std::string name;

  public:
    Benchmark(const std::string& name);

    size_t add_point(unsigned int n);

    void start(size_t idx);

    void end(size_t idx);

    void write_to_file(std::string out_dir = "results");
};
