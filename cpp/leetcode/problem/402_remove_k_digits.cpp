/**
 * @brief
 * Given string num representing a non-negative integer num, and an integer k,
 * return the smallest possible integer after removing k digits from num.
 *
 * Example 1: num = "1432219", k = 3 -> "1219"
 * Example 2: num = "10200", k = 1 -> "200"
 * Example 3: num = "10", k = 2 -> "0"
 *
 * Constraints:
 * - 1 <= k <= num.length <= 10^5
 * - num consists of only digits.
 * - num does not have any leading zeros except for the zero itself.
 */
#include "gtest/gtest.h"
#include <string>

/**
 * @brief The solution class to the problem used by LeetCode.
 */
class Solution
{
public:
    /**
     * @brief The function that will be used by the LeetCode server.
     *
     * @note Which is why it takes the string by value.
     */
    std::string removeKdigits(std::string num, int k) // NOLINT(performance-unnecessary-value-param,readability-convert-member-functions-to-static)
    {
        return removeLeadingZeroes(solution3(num, k));
    }

    static std::string removeLeadingZeroes(const std::string& number)
    {
        const auto firstNonZero = number.find_first_not_of('0');
        return
            firstNonZero == std::string::npos ? "0" : // number is just a lot of zeroes
            number.substr(firstNonZero);
    }

// region Solution 1
    /**
     * @brief
     * This solution uses dynamic programming.
     * The solution either removes the last character, or not.
     * - If it does, the solution reduces to the same problem with `number[:-1], k-1`
     * - If it does not, then the best we can do is solve `number[:-1], k`, and reattach the last character.
     * The smaller of these two is the solution.
     *
     * Unfortunately, this method is exponential.
     */
    static std::string solution1(const std::string& number, int k) // NOLINT(misc-no-recursion)
    {
        if (k == 0)
        {
            return number;
        }
        if (number.size() == k)
        {
            return {};
        }

        const auto cut = number.substr(0, number.size() - 1U);

        // either take off the last digit, or don't:
        const auto one = solution1(cut, k-1);
        const auto other = ((cut.size() == k) ? "" : solution1(cut, k)) + number[number.size() - 1U];

        return compare(one, other) < 0 ? one : other;
    }

    /// @brief Slightly modified `std::string::compare`
    static int compare(const std::string& lhs, const std::string& rhs)
    {
        return
            lhs.size() < rhs.size() ? -1 :
            lhs.size() > rhs.size() ?  1 :
            lhs.compare(rhs);
    }
// endregion Solution 1

// region Solution 2
    /**
     * @brief
     * The solution uses the following observation.
     * Any way we remove `k` digits, the remaining `n-k` digits will be the lowest possible only if
     * its first digit is the lowest possible (including a leading zero).
     *
     * Therefore, this solution checks for the smallest reachable starting digit, keeps it,
     * and reduces the problem to the remaining string.
     *
     * Worst case, the string is sorted (e.g. "11112233344..."), in which case the lookaheads take O(n * k) steps,
     * where `n` is the length of the string.
     * This is not ideal, but actually passes all the tests on the server within the time limits.
     */
    static std::string solution2(const std::string& num, const int k) // NOLINT(misc-no-recursion)
    {
        if (k == 0U)
        {
            return num;
        }
        if (num.size() == k)
        {
            return "";
        }

        char smallestReachableStart = '9' + 1;
        uint32_t smallestIndex = 0U;
        for (uint32_t i = 0U; i <= k; ++i)
        {
            if (num[i] < smallestReachableStart)
            {
                smallestReachableStart = num[i];
                smallestIndex = i;
            }
        }

        if (smallestIndex == k)
        {
            // chop off the first k characters
            return num.substr(smallestIndex);
        }
        else
        {
            // chop off the first `smallestIndex` characters, keep the first, and recurse.
            return smallestReachableStart
                + solution2(
                    num.substr(smallestIndex + uint32_t{1U}),
                    static_cast<int>(k - smallestIndex));
        }
    }
// endregion Solution 2

// region Solution 3
    /**
     * @brief
     * A realization from the 2nd solution is that the starting part of the solution has to be monotonically increasing
     * up to the last removed digit.
     * Assume otherwise:
     * let p1 ... pk be the indices of the removed positions, and let pi < pj < pk be consecutive non-removed positions
     * with num[pi] > num[pj].
     * Removing position pi instead of pk decreases the digit from num[pi] to num[pj], which
     * decreases the remaining number whatever may come next.
     *
     * This can be done in linear time, with basically a stack.
     * Each character can be put on the stack only once, can be removed only once.
     * The number of comparisons is also linear, as after every comparison we either remove a character from
     * the stack, or add a character to the stack.
     *
     * @note Some further improvements can be achieved by stopping when `k` reaches 0,
     * and copying the remaining digits together.
     */
    static std::string solution3(const std::string& num, int k)
    {
        std::string solution{};
        solution.reserve(num.size());

        for (const auto c : num)
        {
            while (!solution.empty() && solution.back() > c && k > 0)
            {
                solution.pop_back();
                --k;
            }
            solution += c;
        }

        // If we still have characters left to be removed (e.g. "112"), then remove them from the back.
        while (k-- > 0)
        {
            solution.pop_back();
        }

        return solution;
    }
// endregion Solution 3
};

TEST(removeKDigits, basic) // NOLINT
{
    Solution solution;
    EXPECT_EQ(solution.removeKdigits("1432219", 3), "1219");
    EXPECT_EQ(solution.removeKdigits("10200", 1), "200");
    EXPECT_EQ(solution.removeKdigits("10", 2), "0");
    EXPECT_EQ(solution.removeKdigits("112", 1), "11");
}
