/**
 * Hackerrank Java practice course
 * Java Strings Introduction
 */
import org.jetbrains.annotations.NotNull;

public class JavaStringIntroduction
{
    static String @NotNull [] processWords(final String word1, final String word2)
    {
        return new String[]{
            String.valueOf(sumOfLengths(word1, word2)),
            isLexicographicallyBigger(word1, word2),
            capitalize(word1) + ' ' + capitalize(word2)};
    }

    public static int sumOfLengths(final String word1, final String word2)
    {
        return (word1 != null ? word1.length() : 0) + (word2 != null ? word2.length() : 0);
    }

    public static @NotNull String isLexicographicallyBigger(final String word1, final String word2)
    {
        if (word1 == null)
        {
            return "No";
        }
        if (word2 == null)
        {
            return "Yes";
        }
        return word1.compareTo(word2) > 0 ? "Yes" : "No";
    }

    public static String capitalize(final String word)
    {
        if (word == null)
        {
            return null;
        }
        if (word.length() == 0)
        {
            return "";
        }
        return word.substring(0, 1).toUpperCase() + word.substring(1).toLowerCase();
    }
}
