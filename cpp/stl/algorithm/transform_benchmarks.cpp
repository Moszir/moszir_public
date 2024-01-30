#include "benchmark/benchmark.h"

#include <algorithm>
#include <execution>
#include <iterator> // std::back_inserter
#include <numeric> // std::iota
#include <vector>


constexpr int doubleIt(const int x)
{
    return x + x;
}

auto generateNumbers(const int size)
{
    std::vector<int> a(size, 0);
    std::iota(a.begin(), a.end(), 1);
    return a;
}

static const auto lotOfNumbers = generateNumbers(1'000'000);

static void benchmarkTransformBackInserter(benchmark::State& state)
{
    std::vector<int> results{};
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), std::back_inserter(results), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkTransformBackInserter);

static void benchmarkTransformBackInserterWithReserve(benchmark::State& state)
{
    std::vector<int> results{};
    results.reserve(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), std::back_inserter(results), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkTransformBackInserterWithReserve);

static void benchmarkTransformWithResize(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), results.begin(), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkTransformWithResize);

static void benchmarkTransformWithResizeWithLambda(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), results.begin(),
            [](const int x) { return x + x; });
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkTransformWithResizeWithLambda);

// Note: parallel execution is only possible by resizing, and using a regular iterator,
// because `std::back_inserter` is not thread-safe.
static void benchmarkTransformParallel(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(
            std::execution::par,
            lotOfNumbers.begin(),
            lotOfNumbers.end(),
            results.begin(),
            doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkTransformParallel);

static void benchmarkTransformParallelWithLambda(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(
            std::execution::par,
            lotOfNumbers.begin(),
            lotOfNumbers.end(),
            results.begin(),
            [](const int x) { return x + x; });
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkTransformParallelWithLambda);

static void benchmarkForEachPushBack(benchmark::State& state)
{
    std::vector<int> results{};
    results.reserve(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::for_each(
            lotOfNumbers.begin(),
            lotOfNumbers.end(),
            [&results](const int x) { results.push_back(x + x); });
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkForEachPushBack);

static void benchmarkForEachWithIndex(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::size_t i = 0;
        std::for_each(
            lotOfNumbers.begin(),
            lotOfNumbers.end(),
            [&results, &i](const int x) { results[i++] = x + x; });
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkForEachWithIndex);

static void benchmarkRangeForPushBack(benchmark::State& state)
{
    std::vector<int> results{};
    results.reserve(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        for (const auto x: lotOfNumbers)
        {
            results.push_back(x + x);
        }
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkRangeForPushBack);

static void benchmarkRangeForWithIndex(benchmark::State& state)
{
    std::vector<int> results{};
    results.resize(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::size_t i = 0;
        for (const auto x: lotOfNumbers)
        {
            results[i++] = x + x;
        }
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkRangeForWithIndex);

static void benchmarkIndexForWithResize(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        for (std::size_t i = 0; i < lotOfNumbers.size(); ++i)
        {
            results[i] = lotOfNumbers[i] + lotOfNumbers[i];
        }
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkIndexForWithResize);

static void benchmarkBinaryTransform(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(
            lotOfNumbers.begin(), lotOfNumbers.end(),
            lotOfNumbers.begin(),
            results.begin(), std::plus<>{});
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkBinaryTransform);

static void benchmarkBinaryTransformParallel(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(
            std::execution::par,
            lotOfNumbers.begin(), lotOfNumbers.end(),
            lotOfNumbers.begin(),
            results.begin(), std::plus<>{});
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkBinaryTransformParallel);

static void benchmarkBinaryTransformUnsequencedParallel(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(
            std::execution::par_unseq,
            lotOfNumbers.begin(), lotOfNumbers.end(),
            lotOfNumbers.begin(),
            results.begin(), std::plus<>{});
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(benchmarkBinaryTransformUnsequencedParallel);


BENCHMARK_MAIN();

/** Benchmark results

Run on (24 X 2496 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1280 KiB (x12)
  L3 Unified 30720 KiB (x1)
--------------------------------------------------------------------------------------
Benchmark                                            Time             CPU   Iterations
--------------------------------------------------------------------------------------
benchmarkTransformBackInserter                 3153095 ns      3045551 ns          236
benchmarkTransformBackInserterWithReserve      3345767 ns      3365385 ns          195
benchmarkTransformWithResize                    213882 ns       213109 ns         3446
benchmarkTransformWithResizeWithLambda          127169 ns       125552 ns         4978
benchmarkTransformParallel                      162805 ns       127302 ns         8960
benchmarkTransformParallelWithLambda             69864 ns         1619 ns       125440
benchmarkForEachPushBack                       3114008 ns      3154343 ns          213
benchmarkForEachWithIndex                       297847 ns       299944 ns         2240
benchmarkRangeForPushBack                      3096230 ns      3080986 ns          213
benchmarkRangeForWithIndex                      272455 ns       272770 ns         2635
benchmarkIndexForWithResize                     396357 ns       401088 ns         1792
benchmarkBinaryTransform                        128373 ns       128691 ns         4978
benchmarkBinaryTransformParallel                 68867 ns         1814 ns       112000
benchmarkBinaryTransformUnsequencedParallel      68795 ns         1562 ns       100000

Conclusions:
- Resizing is much faster than using `push_back`-based approaches, including `std::back_inserter`.
- Using a lambda is faster than using a local function's "function pointer" (which should be inlined, but who knows).
- `std::transform` is indeed faster than `std::for_each`, range-based for loops, and index-based for loops.
  Note that the range-based for loop with resize was the fastest for loop.
  Unary `std::transform` was around twice as fast than that.
- Parallel execution does speed up the process, but only if you have enough idle cores.

*/
