#include "gtest/gtest.h"

#include <algorithm>
#include <execution>


template<int y>
int times(int x) { return x*y; }

const std::vector<int> oneToFive{1, 2, 3, 4, 5};

// region std::transform (1)

/**
 * The first version of `std::transform`:
 * ```cpp
 * OutputIterator transform(
 *     InputIterator first,
 *     InputIterator last,
 *     OutputIterator result,
 *     UnaryOperation op);
 * ```
 *
 * - [first, last) is the input range.
 * - result is the output iterator.
 * - op is the unary operation to apply to each element.
 *
 * _Return value_: an iterator to the element past the last element written in the output range
 * In other words: where the next element would go, if we continued writing to the output range.
 *
 * _Complexity_: exactly `last - first` applications of `op`.
 *
 * @warning The output container must be large enough to hold all the elements,
 * or a special iterator must be used (see below).
 *
 * @warning `std::transform` does not guarantee that the operation is applied in order.
 */


/**
 * @test If the output container is not large enough, `std::transform` will cause a segmentation fault.
 *
 * `std::transform` takes an output iterator, it does not resize the container.
 * If the output container is not large enough, it might write to memory that it does not own.
 */
TEST(Transform1, memoryOverwrite)
{
    const auto& input = oneToFive;
    std::vector<int> output{};

    EXPECT_DEATH(
        {
            std::transform(input.begin(), input.end(), output.begin(), times<2>);
        },
        "");
}

/**
 * @test `std::transform` works if we resize the empty container first.
 */
TEST(Transform1, resizeFirst)
{
    const auto& input = oneToFive;
    std::vector<int> output{};
    output.resize(input.size());

    const auto returnValue = std::transform(input.begin(), input.end(), output.begin(), times<2>);

    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10}));
    EXPECT_EQ(returnValue, output.end());
}

/**
 * @test `std::transform` works if we use `std::back_inserter`.
 *
 * This is another way to work around the problem of the output container not being large enough.
 * Note however, that it presents other problems:
 * - It uses `push_back` on the output container one element at a time.
 * - If the output container reaches its capacity, it will reallocate and invalidate the iterators.
 * - The reallocation will cause a copy of the entire container, which might be expensive.
 * - But also, the invalidation of the iterators can cause undefined behavior,
 *   if the input container is the same.
 *
 * The invalidation problem can be avoided by using `reserve` beforehand.
 */
TEST(Transform1, backInserter)
{
    const auto& input = oneToFive;
    std::vector<int> output{};
    auto returnValue = std::transform(input.begin(), input.end(), std::back_inserter(output), times<2>);

    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10}));

    // `returnValue` is a `std::back_insert_iterator`, which cannot really be checked with `operator==`.
    // Instead, we can check that it can be used for further push_backs.
    returnValue = 12;
    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10, 12}));
}

/**
 * @test `std::transform` with `std::back_inserter` can cause undefined behavior.
 * The `std::back_inserter` calls `push_back` which reallocates the container,
 * invalidating the input iterators.
 *
 * @note The test can still succeed, as the undefined behavior can behave as expected.
 */
TEST(Transform1, backInserterUndefinedBehavior)
{
    std::vector<int> v{1, 2, 3, 4};
    v.shrink_to_fit(); // make sure that the capacity is the same as the size

    std::transform(v.begin(), v.end(), std::back_inserter(v), times<2>);

    if (v != std::vector<int>({1, 2, 3, 4, 2, 4, 6, 8}))
    {
        std::cout << "Indeed something weird happened:" << std::endl;
        for (const auto a: v) { std::cout << a << ", "; }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "The undefined behavior behaved quite expectedly." << std::endl;
    }
}

/// @test An example for using the return value of `std::transform`.
TEST(Transform1, usingTheReturnValue)
{
    const std::vector<int> input{1, 2, 3};
    std::vector<int> output{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    std::transform(
        input.begin(),
        input.end(),
        std::transform(
            input.begin(),
            input.end(),
            output.begin() + 2,
            times<2>
        ), // changes {13, 14, 15} to {2, 4, 6}, returns output.begin() + 5
        times<3>); // changes {16, 17, 18} to {3, 6, 9}

    EXPECT_EQ(output, std::vector<int>({11, 12, 2, 4, 6, 3, 6, 9, 19, 20}));
}
// endregion std::transform (1)


// region std::transform (2)

/**
 * The second version of `std::transform`:
 * ```cpp
 * template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryOperation>
 * ForwardIt2 transform(
 *     ExecutionPolicy&& policy,
 *     ForwardIt1 first1,
 *     ForwardIt1 last1,
 *     ForwardIt2 d_first,
 *     UnaryOperation unary_op );
 * ```
 *
 * This is the same as the first version,
 * except that it takes an execution policy as the first argument.
 *
 * @note
 * Using `std::back_inserter` with the parallel version of `std::transform` is not possible.
 * A static assertion will fail:
 * 'Non-ranges algorithms require that mutable iterators be Cpp17ForwardIterators or stronger.'
 */
TEST(Transform2, parallel)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<int> output{};
    output.resize(input.size());

    const auto returnValue = std::transform(
        std::execution::par,
        input.begin(), input.end(), output.begin(), times<2>);

    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10, 12, 14, 16, 18, 20}));
    EXPECT_EQ(returnValue, output.end());
}
// endregion std::transform (2)


// region std::transform (3)

/**
 * The third version of `std::transform`:
 * ```cpp
 * template<class InputIt1, class InputIt2, class OutputIt, class BinaryOperation>
 * constexpr OutputIt transform(
 *     InputIt1 first1,
 *     InputIt1 last1,
 *     InputIt2 first2,
 *     OutputIt d_first,
 *     BinaryOperation binary_op);
 * ```
 *
 * - [first1, last1) is the first input range
 * - [first2, first2 + (last1 - first1)) is the second input range
 * - d_first is the output iterator
 * - binary_op is the binary operation to apply to each pair of elements
 *
 * _Return value_: an iterator to the element past the last element written in the output range
 *
 * _Complexity_: exactly `last1 - first1` applications of `binary_op`
 *
 * @note The same considerations apply to the output iterator as in the first version.
 *
 * @note
 * An additional consideration is that the second input range is specified only by its first element.
 * The last element is calculated from the first element and the size of the first input range.
 * Therefore, it is an easy way for the user to make a mistake there too.
 *
 * Both problems are handled much better by the ranges version of `std::transform`.
 */

TEST(Transform3, memoryOverwrite)
{
    const auto& input = oneToFive;
    std::vector<int> output{};

    EXPECT_DEATH(
        {
            std::transform(input.begin(), input.end(), input.begin(), output.begin(), std::plus<>{});
        },
        "");
}

TEST(Transform3, resizeFirst)
{
    const auto& input = oneToFive;
    std::vector<int> output{};
    output.resize(input.size());

    const auto returnValue = std::transform(input.begin(), input.end(), input.begin(), output.begin(), std::plus<>{});

    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10}));
    EXPECT_EQ(returnValue, output.end());
}

TEST(Transform3, backInserter)
{
    const auto& input = oneToFive;
    std::vector<int> output{};
    auto returnValue = std::transform(input.begin(), input.end(), input.begin(), std::back_inserter(output), std::plus<>{});

    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10}));

    // `returnValue` is a `std::back_insert_iterator`, which cannot really be checked with `operator==`.
    // Instead, we can check that it can be used for further push_backs.
    returnValue = 12;
    EXPECT_EQ(output, std::vector<int>({2, 4, 6, 8, 10, 12}));
}
// endregion std::transform (3)


// region std::transform (4)

/**
 * The fourth version of `std::transform`:
 *
 * ```cpp
 * template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class ForwardIt3, class BinaryOperation>
 * ForwardIt3 transform(
 *     ExecutionPolicy&& policy,
 *     ForwardIt1 first1,
 *     ForwardIt1 last1,
 *     ForwardIt2 first2,
 *     ForwardIt3 d_first,
 *     BinaryOperation binary_op);
 * ```
 *
 * This is the same as the third version,
 * except that it takes an execution policy as the first argument.
 */

TEST(Transform4, parallel)
{
    const std::vector<int> input1{1, 2, 3, 4, 5};
    const std::vector<int> input2{10, 20, 30, 40, 50};

    std::vector<int> output{};
    output.resize(input1.size());

    const auto returnValue = std::transform(
        std::execution::par,
        input1.begin(), input1.end(), input2.begin(), output.begin(), std::plus<>{});

    EXPECT_EQ(output, std::vector<int>({11, 22, 33, 44, 55}));
    EXPECT_EQ(returnValue, output.end());
}
// endregion std::transform (4)
