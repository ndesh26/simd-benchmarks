#include <benchmark/benchmark.h>
#include <immintrin.h>

static float f(float a) { return a * a; }
static auto f(__m512 a) { return _mm512_mul_ps(a, a); }
static float numericalIntegrationAvx(float a, float b, int n) {
    auto dx = (b - a) / n;
    auto integral = f(a) / 2 + f(b) / 2;
    constexpr __m512 seq = {1.f, 2.f,  3.f,  4.f,  5.f,  6.f,  7.f,  8.f,
                            9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f};

    auto integralSum = _mm512_setzero_ps();
    auto v = seq * _mm512_set1_ps(dx);
    v = v + _mm512_set1_ps(a);
    auto incr = _mm512_set1_ps(16 * dx);

    for (int k = 1; k < n; k += 16) {
        integralSum = _mm512_add_ps(integralSum, f(v));
        v = _mm512_add_ps(v, incr);
    }

    integral += _mm512_reduce_add_ps(integralSum);
    integral *= dx;

    return integral;
}

static void vectorized(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        benchmark::DoNotOptimize(numericalIntegrationAvx(0, 1, 20000));
    }
}
// Register the function as a benchmark
BENCHMARK(vectorized);
