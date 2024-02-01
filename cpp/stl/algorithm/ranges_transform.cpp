/**
 * With C++20, there is now a new version of `std::transform` that works with ranges.
 *
 * Advantages:
 * - It is more convenient to just pass the whole range instead of the begin and end iterators.
 *   - It is also less error prone, and more readable.
 * - There is an optional projection parameter.
 *   - Whether that is more readable than a lambda is debatable.
 *
 * Disadvantages:
 * - If you don't want to use the whole range, then you have to use basically the same syntax as before.
 * - No option to use parallel execution.
 */

#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>


template<int y>
int times(int x) { return x*y; }

const std::vector<int> oneToFive{1, 2, 3, 4, 5};


#pragma region std::ranges::transform (1)

/**
 * The first version of `std::ranges::transform` with a possible implementation.
 * [Source](https://en.cppreference.com/w/cpp/algorithm/ranges/transform).
 *
 * Requires C++20.
 */
template<
    std::input_iterator I,
    std::sentinel_for<I> S,
    std::weakly_incrementable O,
    std::copy_constructible F,
    class Proj = std::identity>
requires std::indirectly_writable<O, std::indirect_result_t<F&, std::projected<I, Proj>>>
constexpr std::ranges::unary_transform_result<I, O> mockTransform1(
    I first1,
    S last1,
    O result,
    F op,
    Proj proj = {})
{
    for (; first1 != last1; ++first1, (void)++result)
    {
        *result = std::invoke(op, std::invoke(proj, *first1));
    }
    return {first1, result};
}

TEST(RangesTransform1, Mock1)
{
    std::vector<int> result(5);
    auto [it, end] = mockTransform1(oneToFive.begin(), oneToFive.end(), result.begin(), times<2>);
    EXPECT_EQ(it, oneToFive.end());
    EXPECT_EQ(end, result.end());
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}

/**
 * @test A simple example for the first version of `std::ranges::transform`.
 */
TEST(RangesTransform1, Example)
{
    std::vector<int> result(5);
    auto [it, end] = std::ranges::transform(oneToFive.begin(), oneToFive.end(), result.begin(), times<2>);
    EXPECT_EQ(it, oneToFive.end());
    EXPECT_EQ(end, result.end());
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}


/**
 * @test Show that `std::ranges::transform` has the same behavior as `std::transform`
 * if the output container is not large enough.
 */
TEST(RangesTransform1, memoryOverwrite)
{
    const auto& input = oneToFive;
    std::vector<int> output{};
    EXPECT_DEATH(
        {
            std::ranges::transform(input.begin(), input.end(), output.begin(), times<2>);
        },
        "");
}

/**
 * @test Show that using `std::back_inserter` as output iterator works.
 * Although it is probably not too performant.
 */
TEST(RangesTransform1, backInserter)
{
    const auto& input = oneToFive;
    std::vector<int> output{};
    std::ranges::transform(input.begin(), input.end(), std::back_inserter(output), times<2>);
    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10}));
}

/**
 * @test An example showing the usage of `std::ranges::transform` with a projection.
 */
TEST(RangesTransform1, projection)
{
    struct Person
    {
        std::string name;
        int age;
    };
    const std::vector<Person> people{{"Alice", 20}, {"Bob", 30}, {"Charlie", 40}};

    std::vector<int> output{};
    std::ranges::transform(
        people.begin(),
        people.end(),
        std::back_inserter(output),
        times<2>,
        &Person::age);
    EXPECT_EQ(output, std::vector<int>({40, 60, 80}));

    // Note that the same behavior can be achieved with a bit more complicated lambda:
    output.clear();
    std::ranges::transform(
        people.begin(),
        people.end(),
        std::back_inserter(output),
        [](const Person& p) { return times<2>(p.age); });
    EXPECT_EQ(output, std::vector<int>({40, 60, 80}));
}

/**
 * @test An example for reusing the return values of `std::ranges::transform`.
 */
TEST(RangesTransform1, returnValues)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> output{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    auto [inputIt, outputIt] =
        std::ranges::transform(
            input.begin() + 2,
            input.begin() + 5,
            output.begin() + 2,
            times<2>);
    EXPECT_EQ(inputIt, input.begin() + 5);
    EXPECT_EQ(outputIt, output.begin() + 5);
    EXPECT_EQ(output, std::vector<int>({10, 20, 6, 8, 10, 60, 70, 80, 90, 100}));

    // Now we can continue from where we left off with triple the values:
    auto [inputIt2, outputIt2] = // It would be nice if we could rebind the original iterators
        std::ranges::transform(
            inputIt,
            input.end(),
            outputIt,
            times<3>);
    EXPECT_EQ(inputIt2, input.end());
    EXPECT_EQ(outputIt2, output.end());
    EXPECT_EQ(output, std::vector<int>({10, 20, 6, 8, 10, 18, 21, 24, 27, 30}));
}

#pragma endregion std::ranges::transform (1)


#pragma region std::ranges::transform (2)

/**
 * The second version of `std::ranges::transform` with a possible implementation.
 * [Source](https://en.cppreference.com/w/cpp/algorithm/ranges/transform).
 *
 * Requires C++20.
 *
 * It is really just a wrapper around calling the first version with `begin()` and `end()` of the input range.
 */
template<
    std::ranges::input_range R,
    std::weakly_incrementable O,
    std::copy_constructible F,
    class Proj = std::identity>
requires std::indirectly_writable<O, std::indirect_result_t<F&, std::projected<std::ranges::iterator_t<R>, Proj>>>
constexpr std::ranges::unary_transform_result<std::ranges::borrowed_iterator_t<R>, O>
mockTransform2(
    R&& r,
    O result,
    F op,
    Proj proj = {})
{
    return std::ranges::transform(std::ranges::begin(r), std::ranges::end(r), result, std::ref(op), std::ref(proj));
}

TEST(RangesTransform2, Mock)
{
    std::vector<int> result(5);
    auto [it, end] = mockTransform2(oneToFive, result.begin(), times<2>);
    EXPECT_EQ(it, oneToFive.end());
    EXPECT_EQ(end, result.end());
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}

/**
 * @test A simple example for the second version of `std::ranges::transform`.
 */
TEST(RangesTransform2, Example)
{
    std::vector<int> result(5);
    auto [it, end] = std::ranges::transform(oneToFive, result.begin(), times<2>);
    EXPECT_EQ(it, oneToFive.end());
    EXPECT_EQ(end, result.end());
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}

TEST(RangesTransform2, SelfModification)
{
    std::vector<int> oneToThree{1, 2, 3};
    auto [it, end] = std::ranges::transform(oneToThree, oneToThree.begin(), times<2>);
    EXPECT_EQ(it, oneToThree.end());
    EXPECT_EQ(end, oneToThree.end());
    EXPECT_EQ(oneToThree, std::vector<int>({2, 4, 6}));
}

#pragma endregion std::ranges::transform (2)


#pragma region std::ranges::transform (3)

/**
 * The third version of `std::ranges::transform` with a possible implementation.
 * [Source](https://en.cppreference.com/w/cpp/algorithm/ranges/transform).
 *
 * Requires C++20.
 *
 * It takes two input ranges and applies the given binary operation to the elements of the two ranges.
 */
template<
    std::input_iterator I1,
    std::sentinel_for<I1> S1,
    std::input_iterator I2,
    std::sentinel_for<I2> S2,
    std::weakly_incrementable O,
    std::copy_constructible F,
    class Proj1 = std::identity,
    class Proj2 = std::identity>
requires std::indirectly_writable<
    O,
    std::indirect_result_t<
        F&,
        std::projected<I1, Proj1>,
        std::projected<I2, Proj2>>> // Requires *o = f(proj1(*i1), proj2(*i2)) to be valid
constexpr std::ranges::binary_transform_result<I1, I2, O> mockTransform3(
    I1 first1,
    S1 last1,
    I2 first2,
    S2 last2,
    O result,
    F op,
    Proj1 proj1 = {},
    Proj2 proj2 = {})
{
    for (; first1 != last1 && first2 != last2; ++first1, (void)++first2, (void)++result)
    {
        *result = std::invoke(op, std::invoke(proj1, *first1), std::invoke(proj2, *first2));
    }
    return {first1, first2, result};
}

TEST(RangesTransform3, Mock)
{
    std::vector<int> result(5);
    auto [it1, it2, end] = mockTransform3(oneToFive.begin(), oneToFive.end(), oneToFive.begin(), oneToFive.end(), result.begin(), std::plus<>{});
    EXPECT_EQ(it1, oneToFive.end());
    EXPECT_EQ(it2, oneToFive.end());
    EXPECT_EQ(end, result.end());
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}

/**
 * @test A simple example for the third version of `std::ranges::transform`.
 */
TEST(RangesTransform3, Example)
{
    std::vector<int> result(5);
    auto [it1, it2, end] = std::ranges::transform(oneToFive.begin(), oneToFive.end(), oneToFive.begin(), oneToFive.end(), result.begin(), std::plus<>{});
    EXPECT_EQ(it1, oneToFive.end());
    EXPECT_EQ(it2, oneToFive.end());
    EXPECT_EQ(end, result.end());
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}

#pragma endregion std::ranges::transform (3)


#pragma region std::ranges::transform (4)

/**
 * The fourth version of `std::ranges::transform` is the same as the third version,
 * but with ranges as both input.
 */

TEST(RangesTransform4, Example)
{
    std::vector<int> result{};
    auto [it1, it2, end] = std::ranges::transform(oneToFive, oneToFive, std::back_inserter(result), std::plus<>{});
    EXPECT_EQ(it1, oneToFive.end());
    EXPECT_EQ(it2, oneToFive.end());
    // EXPECT_EQ(end, result.end()); // end is an std::back_insert_iterator, so it does not have an `operator==`
    EXPECT_EQ(result, std::vector<int>({2, 4, 6, 8, 10}));
}

#pragma endregion std::ranges::transform (4)
