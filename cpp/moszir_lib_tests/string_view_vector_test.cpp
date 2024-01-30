#include "moszir_lib/string_view_vector.hpp"

#include "gtest/gtest.h"


namespace moszir
{

TEST(stringViewVector, defaultConstructor)
{
    StringViewVector sv;
    EXPECT_TRUE(sv.empty());
    EXPECT_EQ(0u, sv.size());
}

/**
 * @test
 * Tests the string vector's constructor with 1 delimiter.
 */
TEST(stringViewVector, constructorOneDelimiter)
{
    const std::string src = ";;Apple;;;banana;;lemon;";
    StringViewVector sv(src, ";");
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ("Apple", sv[0]);
    EXPECT_EQ("banana", sv[1]);
    EXPECT_EQ("lemon", sv[2]);
}

/**
 * @test
 * Tests the string vector's constructor with multiple delimiters.
 */
TEST(stringViewVector, constructorMultipleDelimiters)
{
    const std::string src = ",;Apple.;,banana.,lemon;";
    StringViewVector sv(src, ";.,");
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string_view>({"Apple", "banana", "lemon"}));
}

/**
 * @test
 * Tests the `addTokens` function.
 */
TEST(stringViewVector, addTokens)
{
    StringViewVector sv{};
    const std::string src1 = "Apple;banana;lemon";
    sv.addTokens(src1, ';');
    EXPECT_EQ(sv, std::vector<std::string_view>({"Apple", "banana", "lemon"}));
    const std::string src2 = "coconut,grapefruit;cinnamon,carrot";
    sv.addTokens(src2, ",;");
    EXPECT_EQ(sv, std::vector<std::string_view>({"Apple", "banana", "lemon", "coconut", "grapefruit", "cinnamon", "carrot"}));
}

/**
 * @test
 * Tests the `findIndex` function.
 */
TEST(stringViewVector, findIndex)
{
    const std::string src = "apple banana lemon";
    StringViewVector sv(src, " ");
    EXPECT_EQ(1, sv.findIndex("banana"));
}

/**
 * @test
 * Tests the `findIndex` function with a start index.
 */
TEST(stringViewVector, findIndexWithStart)
{
    const std::string src = "apple banana lemon melon banana";
    StringViewVector sv(src, " ");
    EXPECT_EQ(4, sv.findIndex("banana", 2)); // skips the banana at index 1.
}

/**
 * @test
 * Tests the `findIndex` function when the token is not part of the vector.
 */
TEST(stringViewVector, findIndexNotFound)
{
    const std::string src = "apple banana lemon melon banana";
    StringViewVector sv(src, " ");
    EXPECT_EQ(-1, sv.findIndex("pomegranate"));
}

/**
 * @test
 * Tests the `findIndex` function when the token is only found before the start index.
 */
TEST(stringViewVector, findIndexWithStartNotFound)
{
    const std::string src = "apple banana lemon melon banana";
    StringViewVector sv(src, " ");
    EXPECT_EQ(-1, sv.findIndex("apple", 1)); // skips the apple at index 0.
}

} // namespace moszir
