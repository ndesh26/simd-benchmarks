#include <benchmark/benchmark.h>
// Run the benchmark
int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }
    ::benchmark::AddCustomContext("Benchmark: ", "Numerical Integration");
    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
}
