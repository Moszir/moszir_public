/**
 * @brief
 * You are given an array nums of n positive integers.
 * You can perform two types of operations on any element of the array any number of times:
 * - If the element is even, divide it by 2.
 *   - For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
 * - If the element is odd, multiply it by 2.
 *   - For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
 *
 * The deviation of the array is the maximum difference between any two elements in the array.
 * Return the minimum deviation the array can have after performing some number of operations.
 *
 * Examples:
 * [1,2,3,4] -> 1
 * Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
 *
 * [4,1,5,20,3] -> 3:
 * Explanation: You can transform the array after two operations to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.
 *
 * [2,10,8] -> 3: [2, 5, 4]
 *
 * Constraints:
 * - 2 <= nums.length <= 10^5
 * - 1 <= nums[i] <= 10^9
 */
#include "gtest/gtest.h"
#include <algorithm>
#include <set>
#include <vector>


class Solution {
public:
    int minimumDeviation(std::vector<int>& nums) // NOLINT(readability-convert-member-functions-to-static)
    {
        return solution2(nums);
    }

    /**
     * @brief
     * The key observation for solving the problem is that the second step (odd numbers can be multiplied by 2)
     * is a one-time operation.
     * The solution does not change, if we start by multiplying every odd number by 2,
     * and only using the first operation from then on.
     *
     * The solution then is clear.
     * The deviation of the array is the difference between the max element, and the min element.
     * A better deviation is possible only if the maximum element can be halved.
     * The deviation might actually increase, even if eventually a better solution can be reached:
     * [14, 16] -> [8, 14] -> [7, 8].
     * Therefore, this step should be repeated until the max element is no longer even,
     * and not until the step did not lower the objective.
     *
     * This first solution tracks the min/max element by using `std::set`.
     * Insertion and erasure is O(log n), usually implemented as a red-black tree.
     * Constructing the set is O(n * log n).
     * A halving step takes O(log n), and might be repeated log k times for a number `k`.
     * Overall the algorithm is thus O(n * log n * log M), where M is the largest element.
     */
    static int solution1(const std::vector<int>& nums)
    {
        // Shovel the numbers into a set, double the odd ones.
        std::set<int> numbers;
        for (const auto n : nums)
        {
            numbers.insert(n % 2 == 1 ? 2*n : n);
        }

        // For some reason, std::set does not have `front()`, and `back()`.
        auto bestDeviation = *numbers.rbegin() - *numbers.begin();

        // Try dividing the highest number by 2, the deviation may get better.
        while (*numbers.rbegin() % 2 == 0)
        {
            const auto back = *numbers.rbegin();
            numbers.erase(back);
            numbers.insert(back / 2);
            bestDeviation = std::min(bestDeviation, *numbers.rbegin() - *numbers.begin());
        }

        return bestDeviation;
    }

    /**
     * @brief
     * The previous solution can be implemented slightly faster by using the heap operations of the `algorithm` library.
     * The theoretical complexity is the same, but everything is done in place.
     *
     * @note
     * The heap operations have a somewhat weird syntax.
     * The `priority_queue` structure from `<queue>` could do the same, with nicer syntax,
     * but that has the same drawback as the `std::set` solution: we would first have to copy our data
     * into a new structure.
     */
    static int solution2(std::vector<int>& numbers)
    {
        int minElement = std::numeric_limits<int>::max();
        for (auto& number : numbers)
        {
            if (number % 2 == 1)
            {
                number *= 2;
            }
            minElement = std::min(minElement, number);
        }

        std::make_heap(numbers.begin(), numbers.end());
        auto bestDeviation = numbers.front() - minElement;

        // Try dividing the highest number by 2, the deviation may get better.
        while (numbers.front() % 2 == 0)
        {
            const auto newElement = numbers.front() / 2;

            // The `std` heap operations are a bit weird...
            std::pop_heap(numbers.begin(), numbers.end()); // actually puts the top element to the last place
            numbers.back() = newElement;
            std::push_heap(numbers.begin(), numbers.end()); // bubbles up the last element.

            minElement = std::min(minElement, newElement);
            bestDeviation = std::min(bestDeviation, numbers.front() - minElement);
        }

        return bestDeviation;
    }
};

TEST(minimizeDeviation, basic) // NOLINT
{
    Solution solution;
    std::vector<int> v{1, 2, 3, 4};
    EXPECT_EQ(solution.minimumDeviation(v), 1); // [2, 2, 3, 2]

    v = {4, 1, 5, 20, 3};
    EXPECT_EQ(solution.minimumDeviation(v), 3); // [4, 2, 5, 5, 3]

    v = {2, 10, 8};
    EXPECT_EQ(solution.minimumDeviation(v), 3); // [2, 5, 4]

    v = {7, 7, 13};
    EXPECT_EQ(solution.minimumDeviation(v), 1); // [14, 14, 13]

    v = {14, 16};
    EXPECT_EQ(solution.minimumDeviation(v), 1); // [7, 8]
}
