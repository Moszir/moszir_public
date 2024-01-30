#include "moszir_lib/string_view_vector.hpp"

#include "benchmark/benchmark.h"


static const auto bmInputSingle = []()
{
    std::string s{};
    for (int i = 0; i < 100'000; ++i)
    {
        s += std::to_string(i);
        s += ',';
    }
    return s;
}();

static const auto bmInputMulti = []()
{
    std::string s{};
    for (int i = 0; i < 100'000; ++i)
    {
        s += std::to_string(i);
        s += (i % 3 == 0 ? ',' : i % 3 == 1 ? ';' : '.');
    }
    return s;
}();

using ResultType = std::vector<std::string_view>;

/// @brief Reference implementation using `std::string_view::find_first_of`.
auto split(std::string_view view, std::string_view delimiters)
{
    ResultType output;
    size_t first = 0;
    while (first < view.size())
    {
        const auto second = view.find_first_of(delimiters, first);
        if (first != second)
        {
            output.emplace_back(view.substr(first, second-first));
        }

        if (second == std::string_view::npos)
        {
            break;
        }

        first = second + 1;
    }
    return output;
}

static void benchmarkSplit(benchmark::State& state)
{
    ResultType sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = split(bmInputSingle, ",");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplit);

/// @brief Reference implementation with `std::string_view::find_first_of` using pointers.
auto splitWithPointers(std::string_view view, std::string_view delimiters)
{
    ResultType output;
    for (auto first = view.data(), second = view.data(), last = first + view.size();
        second != last && first != last;
        first = second + 1)
    {
        second = std::find_first_of(first, last, std::cbegin(delimiters), std::cend(delimiters));
        if (first != second)
        {
            output.emplace_back(first, second - first);
        }
    }
    return output;
}

static void benchmarkSplitWithPointers(benchmark::State& state)
{
    ResultType sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = splitWithPointers(bmInputSingle, ",");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitWithPointers);

// Benchmark with `moszir::StringViewVector`.
static void benchmarkStringViewVector(benchmark::State& state)
{
    ::moszir::StringViewVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(bmInputSingle, ",");
    }
}
BENCHMARK(benchmarkStringViewVector);


// region Benchmark with multiple delimiters

static void benchmarkSplitMulti(benchmark::State& state)
{
    ResultType sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = split(bmInputMulti, ",;.");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitMulti);

static void benchmarkSplitWithPointersMulti(benchmark::State& state)
{
    ResultType sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = splitWithPointers(bmInputMulti, ",;.");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitWithPointersMulti);

static void benchmarkStringViewVectorMulti(benchmark::State& state)
{
    ::moszir::StringViewVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(bmInputMulti, ",;.");
    }
}
BENCHMARK(benchmarkStringViewVectorMulti);

// endregion Benchmark with multiple delimiters

BENCHMARK_MAIN();

/*
Run on (24 X 2496 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1280 KiB (x12)
  L3 Unified 30720 KiB (x1)
--------------------------------------------------------------------------
Benchmark                                Time             CPU   Iterations
--------------------------------------------------------------------------
benchmarkSplit                     2023371 ns      2001953 ns          320
benchmarkSplitWithPointers         1358715 ns      1380522 ns          498
benchmarkStringViewVector           594094 ns       585938 ns         1120
benchmarkSplitMulti                1819848 ns      1843164 ns          373
benchmarkSplitWithPointersMulti    1913406 ns      1926944 ns          373
benchmarkStringViewVectorMulti      609619 ns       599888 ns         1120

Conclusion:
The `moszir::StringViewVector` implementation using `strchr` is around 2 times faster
than the pointer version of the `std::string_view::find_first_of` implementation
for splititng strings with a single delimiter.

Its implementation for multiple delimiters using `strpbrk` is around 3 times faster than the
`std::string_view::find_first_of` implementation.

Note: the difference between the `std::string_view::find_first_of` implementations
is not significant with multiple delimiters.

Also note: splitting into a vector of `string_view`s instead of `std::string`s is faster
both with our vector implementation and with the `std::string_view::find_first_of` implementations.
It is to be expected, as we don't need to copy the strings.
On the other hand, special care must be taken to ensure that the string_views do not outlive
the original string.
*/
