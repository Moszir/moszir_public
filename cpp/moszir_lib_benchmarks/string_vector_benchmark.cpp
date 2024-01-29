#include "moszir_lib/string_vector.hpp"

#include "benchmark/benchmark.h"


namespace moszir
{

// Input with a single delimiter (comma).
static const auto singleDelimiterInput = []()
{
    std::string s{};
    for (int i = 0; i < 100'000; ++i)
    {
        s += std::to_string(i);
        s += ',';
    }
    return s;
}();

// Input with multiple delimiters (",;.").
static const auto multiDelimiterInput = []()
{
    std::string s{};
    for (int i = 0; i < 100'000; ++i)
    {
        s += std::to_string(i);
        s += (i % 3 == 0 ? ',' : i % 3 == 1 ? ';' : '.');
    }
    return s;
}();

static void benchmarkStringVector(benchmark::State& state)
{
    ::moszir::StringVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(singleDelimiterInput, ",");
    }
}
BENCHMARK(benchmarkStringVector);

// Reference implementation with `std::find_first_of`.
std::vector<std::string> split(const std::string& str, const std::string& delimiters)
{
    std::vector<std::string> output;

    auto first = std::cbegin(str);
    while (first != std::cend(str))
    {
        const auto second = std::find_first_of(
            first,
            std::cend(str),
            std::cbegin(delimiters),
            std::cend(delimiters));

        if (first != second)
        {
            output.emplace_back(first, second);
        }

        if (second == std::cend(str))
        {
            break;
        }

        first = std::next(second);
    }
    return output;
}

static void benchmarkSplit(benchmark::State& state)
{
    std::vector<std::string> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = split(singleDelimiterInput, ",");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplit);

static void benchmarkStringVectorMulti(benchmark::State& state)
{
    ::moszir::StringVector sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv.clear();
        sv.addTokens(multiDelimiterInput, ",;.");
    }
}
BENCHMARK(benchmarkStringVectorMulti);


static void benchmarkSplitMulti(benchmark::State& state)
{
    std::vector<std::string> sv{};
    for ([[maybe_unused]] auto _: state)
    {
        sv = split(multiDelimiterInput, ",;.");
        benchmark::DoNotOptimize(sv);
    }
}
BENCHMARK(benchmarkSplitMulti);

} // namespace moszir

BENCHMARK_MAIN();

/*
The C-library implementation with `std::strchr` and `std::strpbrk` is
around 3 times faster than the `std::find_first_of` implementation:

Run on (24 X 2496 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1280 KiB (x12)
  L3 Unified 30720 KiB (x1)
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
benchmarkStringVector         1075801 ns      1060268 ns          560
benchmarkSplit                3244403 ns      3285256 ns          195
benchmarkStringVectorMulti    1053274 ns      1045850 ns          747
benchmarkSplitMulti           3242915 ns      3317039 ns          179
*/
