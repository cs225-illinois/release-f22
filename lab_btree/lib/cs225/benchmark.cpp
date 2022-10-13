#include "benchmark.h"
Benchmark::Benchmark(const std::string &name) : name(name)
{
}

size_t Benchmark::add_point(unsigned int n)
{
    auto min = std::chrono::high_resolution_clock::time_point::min();
    results.emplace_back(n, min, min);
    return results.size() - 1;
}

void Benchmark::start(size_t idx)
{
    results[idx].start_time = std::chrono::high_resolution_clock::now();
}

void Benchmark::end(size_t idx)
{
    results[idx].end_time = std::chrono::high_resolution_clock::now();
}

void Benchmark::write_to_file(std::string out_dir)
{
    std::cout << "writing to file!" << std::endl;
    using namespace std::chrono;
    std::string outname = out_dir + "/" + name + ".csv";
    std::ofstream out(outname);
    out << "n,elapsed_time (ms)" << std::endl;
    for (auto &result : results)
    {
        auto diff = result.end_time - result.start_time;
        out << result.n << ","
            << duration_cast<milliseconds>(diff).count()
            << std::endl;
    }
}