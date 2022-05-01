/**
 * Hackerrank Java practice course
 * Java Strings Introduction
 */
import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

import java.util.Scanner;

public class Solution
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        final String word1 = scanner.next();
        final String word2 = scanner.next();

        String[] results = processWords(word1, word2);
        System.out.println(results[0]);
        System.out.println(results[1]);
        System.out.println(results[2]);

        scanner.close();
    }

    @Contract("_, _ -> new")
    static String @NotNull [] processWords(String word1, String word2)
    {
        return new String[]{
                String.valueOf(sumOfLengths(word1, word2)),
                isLexicographicallyBigger(word1, word2),
                capitalize(word1) + ' ' + capitalize(word2)};
    }

    public static int sumOfLengths(String word1, String word2)
    {
        return word1.length() + word2.length();
    }

    public static String isLexicographicallyBigger(String word1, String word2)
    {
        if (word2 == null)
        {
            return "Yes";
        }
        if (word1 == null)
        {
            return "No";
        }
        return word1.compareTo(word2) > 0 ? "Yes" : "No";
    }

    public static String capitalize(String word)
    {
        if (word == null)
        {
            return null;
        }
        return word.substring(0, 1).toUpperCase() + word.substring(1).toLowerCase();
    }
}
