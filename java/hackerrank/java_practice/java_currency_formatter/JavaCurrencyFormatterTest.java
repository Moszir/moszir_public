import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;

class JavaCurrencyFormatterTest
{
    @Test
    @DisplayName("The sample input from HackerRank")
    void testHackerRankSampleInput0()
    {
        final var results = JavaCurrencyFormatter.getFormattedCurrencies(12324.134);
        // Note that the HackerRank judge only works for Java 7, as the currency sign is different.
        assertArrayEquals(
            new String[]{"$12,324.13", "₹12,324.13", "¥12,324.13", "12 324,13 €"},
            results);
    }
}