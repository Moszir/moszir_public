#include "moszir_lib/string_vector.hpp"

#include "gtest/gtest.h"


namespace moszir
{

TEST(stringVector, defaultConstructor)
{
    StringVector sv;
    EXPECT_TRUE(sv.empty());
    EXPECT_EQ(0u, sv.size());
}

/**
 * @test
 * Tests the string vector's constructor with 1 delimiter.
 */
TEST(stringVector, constructorOneDelimiter)
{
    StringVector sv(";;Apple;;;banana;;lemon;", ";");
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ("Apple", sv[0]);
    EXPECT_EQ("banana", sv[1]);
    EXPECT_EQ("lemon", sv[2]);
}

/**
 * @test
 * Tests the string vector's constructor with multiple delimiters.
 */
TEST(stringVector, constructorMultipleDelimiters)
{
    StringVector sv(",;Apple.;,banana.,lemon;", ";.,");
    EXPECT_EQ(3u, sv.size());
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));
}

/**
 * @test
 * Tests building a string vector from a stream.
 */
TEST(stringVector, fromStream)
{
    std::ofstream out("string_vector_from_stream.txt");
    out <<
        ";;Apple;;;banana;;lemon;\n"
        ",;Apple.;,banana.,lemon;\n";
    out.close();

    std::ifstream in("string_vector_from_stream.txt");
    StringVector sv(in, ";");
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));
    sv = StringVector(in, ";.,");
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));

    // The file has an empty line at its end.
    // While it is possible to get an infinite amount of empty string vectors out of it,
    // we shall only get one by checking `in.good()`.
    int counter = 0;
    while (in.good() && (++counter < 10))
    {
        sv = StringVector(in, ";,.");
        EXPECT_TRUE(sv.empty());
    }
    EXPECT_EQ(counter, 1);
}

/**
 * @test
 * Tests the `addTokens` function.
 */
TEST(stringVector, addTokens)
{
    StringVector sv{};
    sv.addTokens("Apple;banana;lemon", ';');
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon"}));
    sv.addTokens("coconut,grapefruit;cinnamon,carrot", ",;");
    EXPECT_EQ(sv, std::vector<std::string>({"Apple", "banana", "lemon", "coconut", "grapefruit", "cinnamon", "carrot"}));
}

/**
 * @test
 * Tests the `findIndex` function.
 */
TEST(stringVector, findIndex)
{
    StringVector sv("apple banana lemon", " ");
    EXPECT_EQ(1, sv.findIndex("banana"));
}

/**
 * @test
 * Tests the `findIndex` function with a start index.
 */
TEST(stringVector, findIndexWithStart)
{
    StringVector sv("apple banana lemon melon banana", " ");
    EXPECT_EQ(4, sv.findIndex("banana", 2)); // skips the banana at index 1.
}

/**
 * @test
 * Tests the `findIndex` function when the token is not part of the vector.
 */
TEST(stringVector, findIndexNotFound)
{
    StringVector sv("apple banana lemon melon banana", " ");
    EXPECT_EQ(-1, sv.findIndex("pomegranate"));
}

/**
 * @test
 * Tests the `findIndex` function when the token is only found before the start index.
 */
TEST(stringVector, findIndexWithStartNotFound)
{
    StringVector sv("apple banana lemon melon banana", " ");
    EXPECT_EQ(-1, sv.findIndex("apple", 1)); // skips the apple at index 0.
}

} // namespace moszir
