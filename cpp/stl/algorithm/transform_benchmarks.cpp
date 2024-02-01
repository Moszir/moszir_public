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

static void transformBackInserter(benchmark::State& state)
{
    std::vector<int> results{};
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), std::back_inserter(results), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(transformBackInserter);

static void rangesTransformBackInserter(benchmark::State& state)
{
    std::vector<int> results{};
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::transform(lotOfNumbers, std::back_inserter(results), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesTransformBackInserter);

static void transformBackInserterReserve(benchmark::State& state)
{
    std::vector<int> results{};
    results.reserve(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), std::back_inserter(results), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(transformBackInserterReserve);

static void rangesTransformBackInserterReserve(benchmark::State& state)
{
    std::vector<int> results{};
    results.reserve(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::transform(lotOfNumbers, std::back_inserter(results), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesTransformBackInserterReserve);

static void transformResize(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), results.begin(), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(transformResize);

static void rangesTransformResize(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::transform(lotOfNumbers, results.begin(), doubleIt);
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesTransformResize);

static void transformResizeLambda(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::transform(lotOfNumbers.begin(), lotOfNumbers.end(), results.begin(),
            [](const int x) { return x + x; });
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(transformResizeLambda);

static void rangesTransformResizeLambda(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::transform(lotOfNumbers, results.begin(), [](const int x) { return x + x; });
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesTransformResizeLambda);

// Note: parallel execution is only possible by resizing, and using a regular iterator,
// because `std::back_inserter` is not thread-safe.
static void transformParallel(benchmark::State& state)
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
BENCHMARK(transformParallel);

static void transformParallelLambda(benchmark::State& state)
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
BENCHMARK(transformParallelLambda);

static void forEachPushBack(benchmark::State& state)
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
BENCHMARK(forEachPushBack);

static void forEachIndex(benchmark::State& state)
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
BENCHMARK(forEachIndex);

static void rangeForPushBack(benchmark::State& state)
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
BENCHMARK(rangeForPushBack);

static void rangeForIndex(benchmark::State& state)
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
BENCHMARK(rangeForIndex);

static void indexForResize(benchmark::State& state)
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
BENCHMARK(indexForResize);

static void binaryTransform(benchmark::State& state)
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
BENCHMARK(binaryTransform);

static void rangesBinaryTransform(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::transform(lotOfNumbers, lotOfNumbers, results.begin(), std::plus<>{});
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesBinaryTransform);

template<
    std::input_iterator I1, std::sentinel_for<I1> S1,
    std::input_iterator I2, std::sentinel_for<I2> S2,
    std::weakly_incrementable O,
    std::copy_constructible F,
    class Proj1 = std::identity, class Proj2 = std::identity>
requires std::indirectly_writable<O,
    std::indirect_result_t<
        F&,
        std::projected<I1, Proj1>,
        std::projected<I2, Proj2>>>
constexpr std::ranges::binary_transform_result<I1, I2, O>
referenceBinaryTransform(
    I1 first1, S1 last1, I2 first2, S2 last2, O result, F binary_op, Proj1 proj1 = {}, Proj2 proj2 = {})
{
    for (; first1 != last1 && first2 != last2; ++first1, (void)++first2, (void)++result)
        *result = std::invoke(binary_op, std::invoke(proj1, *first1), std::invoke(proj2, *first2));
    return {first1, first2, result};
}

static void bmReferenceBinaryTransform(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        referenceBinaryTransform(lotOfNumbers.begin(), lotOfNumbers.end(), lotOfNumbers.begin(), lotOfNumbers.end(), results.begin(), std::plus<>{});
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(bmReferenceBinaryTransform);

static void optimizedReferenceBinaryTransform(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        auto it1 = lotOfNumbers.begin();
        auto it3 = results.begin();
        const auto endIt1 = lotOfNumbers.end();
        for (; it1 != endIt1; ++it1, (void)++it3)
        {
            *it3 = *it1 + *it1;
        }
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(optimizedReferenceBinaryTransform);

static void binaryTransformParallel(benchmark::State& state)
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
BENCHMARK(binaryTransformParallel);

static void binaryTransformUnsequencedParallel(benchmark::State& state)
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
BENCHMARK(binaryTransformUnsequencedParallel);


static void rangesCopyViewTransformLambda(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::copy(lotOfNumbers | std::views::transform([](const int x) { return x + x; }), results.begin());
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesCopyViewTransformLambda);

static void rangesCopyViewTransformLambda2(benchmark::State& state)
{
    std::vector<int> results(lotOfNumbers.size());
    for ([[maybe_unused]] auto _: state)
    {
        std::ranges::copy(std::views::transform(lotOfNumbers, [](const int x) { return x + x; }), results.begin());
        benchmark::DoNotOptimize(results);
    }
}
BENCHMARK(rangesCopyViewTransformLambda2);



BENCHMARK_MAIN();

/* Benchmark results

Run on (24 X 2496 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1280 KiB (x12)
  L3 Unified 30720 KiB (x1)
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
transformBackInserter                 3135262 ns      2913136 ns          236
rangesTransformBackInserter           2730526 ns      2644231 ns          195
transformBackInserterReserve          3092345 ns      3080986 ns          213
rangesTransformBackInserterReserve    3170661 ns      3140319 ns          204
transformResize                        215905 ns       219727 ns         3200
rangesTransformResize                  208130 ns       213109 ns         3446
transformResizeLambda                  128853 ns       128348 ns         5600
rangesTransformResizeLambda            128412 ns       128691 ns         4978
transformParallel                      146560 ns       134969 ns         4978
transformParallelLambda                 68830 ns         2188 ns       100000
forEachPushBack                       3043236 ns      3069196 ns          224
forEachIndex                           282146 ns       282493 ns         2489
rangeForPushBack                      2936235 ns      2979343 ns          236
rangeForIndex                          269554 ns       265067 ns         2240
indexForResize                         417077 ns       417150 ns         1723
binaryTransform                        127076 ns       128348 ns         5600
rangesBinaryTransform                  206672 ns       205078 ns         3200
binaryTransformParallel                 70498 ns         1406 ns       100000
binaryTransformUnsequencedParallel      69277 ns         3594 ns       100000
rangesCopyViewTransformLambda          254656 ns       251105 ns         2489
rangesCopyViewTransformLambda2         263303 ns       266841 ns         2635

Conclusions:
- Resizing is much faster than using `push_back`-based approaches, including `std::back_inserter`.
- Using a lambda is faster than using a local function's "function pointer" (which should be inlined, but who knows).
- `std::transform` is indeed faster than `std::for_each`, range-based for loops, and index-based for loops.
  Note that the range-based for loop  resize was the fastest for loop.
  Unary `std::transform` was around twice as fast than that.
- Parallel execution does speed up the process, but only if you have enough idle cores.
- Unary `std::ranges::transform` is the same speed as `std::transform`.
- Binary `std::ranges::transform` is slower than the `std::transform`,
  because it checks the sentinel of the second range too.
  (The non-ranges version does not do that, which makes it a bit unsafe, but also more performant.)
- The view transform versions with `std::ranges::copy` are slower.
*/
