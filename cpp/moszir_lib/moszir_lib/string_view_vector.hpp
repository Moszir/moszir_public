#pragma once

#include <cstring>
#include <string>
#include <vector>


namespace moszir
{

/**
 * A vector of string views with added parsing capabilities.
 *
 * @warning String views are non-owning references, their target should outlive them!
 *
 * @note It can be significantly faster than a `StringVector` due to not copying strings.
 */
class StringViewVector : public std::vector<std::string_view>
{
public:
    /**
     * @brief Creates an empty string view vector.
     */
    StringViewVector() = default;

    /**
     * @brief Creates a string view vector by chopping up the given string with the given delimiters.
     *
     * @param sourceString The given string
     * @param delimiters The delimiters
     */
    StringViewVector(const std::string& sourceString, const std::string& delimiters)
    {
        reserve(4);
        addTokens(sourceString, delimiters);
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
                push_back(std::string_view(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
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
                push_back(std::string_view(sourcePos, static_cast<int>(delimiterPos - sourcePos)));
            }
            if (!*delimiterPos)
            {
                break;
            }
            sourcePos = delimiterPos + 1;
        }
    }
};

}// namespace moszir
