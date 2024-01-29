#pragma once

#include <cstring> // strchr, strpbrk
#include <fstream>
#include <string>
#include <vector>


namespace moszir
{

/**
 * @brief Utility class for chopping up a string, given a list of delimiters.
 * @example
 * ```cpp
 * StringVector sv("Hello apple, banana; lemon", " ,;");
 * // Gives a vector with 4 elements: "Hello", "apple", "banana", "lemon".
 * ```
 */
class StringVector : public std::vector<std::string>
{
public:
    /**
     * @brief Creates an empty string vector.
     */
    StringVector() = default;

    /**
     * @brief Creates a string vector by chopping up the given string with the given delimiters.
     *
     * @param sourceString The given string
     * @param delimiters The delimiters
     */
    StringVector(const std::string& sourceString, const std::string& delimiters)
    {
        reserve(4);
        addTokens(sourceString, delimiters);
    }

    /**
     * @brief Creates a string vector by reading a line from the stream, and chopping it up with the given delimiters.
     *
     * @param stream The stream to read from
     * @param delimiters The delimiters
     */
    StringVector(std::istream& stream, const std::string& delimiters)
    {
        reserve(4);
        std::string s;
        std::getline(stream, s);
        addTokens(s, delimiters);
    }

    /**
     * Returns the index of the first occurrence of the given token. Returns -1 if not found.
     * @param token The token to find.
     * @param from The starting index to look from (default 0).
     */
    [[nodiscard]] int findIndex(const std::string& token, int from = 0) const
    {
        auto it = std::find(begin() + from, end(), token);
        return it == end() ? -1 : static_cast<int>(std::distance(begin(), it));
    }

    /**
     * Add the tokens from the source string to this vector.
     * @param sourceString The source string.
     * @param delimiter The delimiter character.
     */
    void addTokens(const std::string& sourceString, const char delimiter)
    {
        const char* sourcePos = sourceString.c_str();
        while (true)
        {
            const char* delimiterPos = std::strchr(sourcePos, delimiter);
            if (!delimiterPos)
            {
                delimiterPos = sourceString.c_str() + sourceString.length();
            }
            if (delimiterPos - sourcePos > 0)
            {
                push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }

    /**
     * Add the tokens from the source string to this vector.
     * @param sourceString The source string.
     * @param delimiters The delimiter characters.
     */
    void addTokens(const std::string& sourceString, const std::string& delimiters)
    {
        addTokens(sourceString, delimiters.c_str());
    }

    /**
     * Add the tokens from the source string to this vector.
     * @param sourceString The source string.
     * @param delimiters The delimiters.
     */
    void addTokens(const std::string& sourceString, const char* delimiters)
    {
        const char* sourcePos = sourceString.c_str();
        while (true)
        {
            const char* delimiterPos = std::strpbrk(sourcePos, delimiters);
            if (!delimiterPos)
            {
                delimiterPos = sourceString.c_str() + sourceString.length();
            }
            if (delimiterPos - sourcePos > 0)
            {
                push_back(std::string(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }
};

} // namespace moszir
