/**
 * Hackerrank Java practice course
 * Java -> Introduction -> Java Currency Formatter
 *
 * Given a double-precision number (`payment`) denoting an amount of money, use the NumberFormat class' getCurrencyInstance method to convert
 * into the US, Indian, Chinese, and French currency formats. Then print the formatted values as follows:
 *
 * US: formattedPayment
 * India: formattedPayment
 * China: formattedPayment
 * France: formattedPayment
 *
 * where `formattedPayment` is formatted according to the appropriate Locale's currency.
 * Note: India does not have a built-in Locale, so you must construct one where the language is en (i.e., English).
 *
 * ## Input
 *
 * A single double-precision number denoting `payment`.
 * `0 <= payment <= 10^9`.
 *
 * ## Output
 *
 * On the first line, print `US: u` where `u` is `payment` formatted for US currency.
 * On the second line, print `India: i` where `i` is `payment` formatted for Indian currency.
 * On the third line, print `China: c` where `c` is `payment` formatted for Chinese currency.
 * On the fourth line, print `France: f`, where `f` is `payment` formatted for French currency.
 *
 * Sample Input
 *
 * 12324.134
 *
 * Sample Output
 *
 * US: $12,324.13
 * India: Rs.12,324.13
 * China: ￥12,324.13
 * France: 12 324,13 €
 *
 * @warning
 * The expected output is only valid for Java 7.
 * The other two options, Java 8, and 15 use '₹' for rupees, and '¥' for yen.
 */

import java.text.NumberFormat;
import java.util.Locale;
import java.util.Scanner;

public class JavaCurrencyFormatter
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        final var payment = scanner.nextDouble();
        scanner.close();

        // Write your code here.
        final var formattedCurrencies = getFormattedCurrencies(payment);

        System.out.println("US: " + formattedCurrencies[0]);
        System.out.println("India: " + formattedCurrencies[1]);
        System.out.println("China: " + formattedCurrencies[2]);
        System.out.println("France: " + formattedCurrencies[3]);
    }

    /**
     * Utility function for getting the formatted currency strings the problem asks to print out.
     * The class can thus be tested on this function.
     *
     * @param payment The numerical amount to be formatted.
     * @return The currency formatted in the specified locales (in an array).
     */
    public static String[] getFormattedCurrencies(final double payment)
    {
        return new String[]{
            formatCurrency(Locale.US, payment),
            formatCurrency(new Locale("en", "in"), payment),
            formatCurrency(Locale.CHINA, payment),
            formatCurrency(Locale.FRANCE, payment),
        };
    }

    /**
     * Formats the given numerical amount in the given locale's currency as a string.
     *
     * @param locale The locale.
     * @param payment The amount of money.
     * @return The formatted string.
     */
    private static String formatCurrency(final Locale locale, final double payment)
    {
        return NumberFormat.getCurrencyInstance(locale).format(payment);
    }
}
