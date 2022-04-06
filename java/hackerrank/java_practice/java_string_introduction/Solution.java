/**
 * Hackerrank Java practice course
 * Java Strings Introduction
 */
import java.util.Scanner;

public class Solution
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        final String word1 = scanner.next();
        final String word2 = scanner.next();

        System.out.println(sumOfLengths(word1, word2));
        System.out.println(isLexicographicallyBigger(word1, word2));
        System.out.println(capitalize(word1) + ' ' + capitalize(word2));

        scanner.close();
    }

    public static int sumOfLengths(String word1, String word2)
    {
        return word1.length() + word2.length();
    }

    public static String isLexicographicallyBigger(String word1, String word2)
    {
        return word1.compareTo(word2) > 0 ? "Yes" : "No";
    }

    public static String capitalize(String word)
    {
        return word.substring(0, 1).toUpperCase() + word.substring(1).toLowerCase();
    }
}
