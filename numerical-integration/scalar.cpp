#include <benchmark/benchmark.h>

static float f(float a) { return a * a; }

static float numericalIntegration(float a, float b, int n) {
    auto dx = (b - a) / n;
    auto integral = f(a) / 2 + f(b) / 2;

    for (int k = 1; k < n; k++) {
        integral += f(a + k * dx);
    }

    integral *= dx;
    return integral;
}

static void BM_numericalIntegration(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        benchmark::DoNotOptimize(numericalIntegration(0, 1, 20000));
    }
}
// Register the function as a benchmark
BENCHMARK(BM_numericalIntegration);
