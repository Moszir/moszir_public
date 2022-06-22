import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import java.util.Objects;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

class JavaStringIntroductionTest
{
    @Test
    @DisplayName("The sample input from HackerRank")
    void testHackerRankSampleInput0()
    {
        final var results = JavaStringIntroduction.processWords("hello", "java");
        assertEquals("9", results[0]);
        assertEquals("No", results[1]);
        assertEquals("Hello Java", results[2]);
    }

    @Test
    @DisplayName("A custom input")
    void testCustomInput()
    {
        final var results = JavaStringIntroduction.processWords("Array", "calculations");
        assertEquals("17", results[0]);
        assertEquals("No", results[1]);
        assertEquals("Array Calculations", results[2]);
    }

    void strictlyBigger(final String lhs, final String rhs)
    {
        assertEquals("Yes", JavaStringIntroduction.isLexicographicallyBigger(lhs, rhs));
        assertEquals("No", JavaStringIntroduction.isLexicographicallyBigger(rhs, lhs));
    }

    void same(final String lhs, final String rhs)
    {
        assertEquals(lhs, rhs);
        assertEquals("No", JavaStringIntroduction.isLexicographicallyBigger(rhs, lhs));
    }

    @Test
    @DisplayName("Lexicographical comparison")
    void testLexicographicalComparison()
    {
        same(null, null);
        strictlyBigger("", null);
        strictlyBigger("anything", null);
        same("", "");
        strictlyBigger("a", "");
        same("a", "a");
        strictlyBigger("a", "A"); // lower-case letters are "bigger".
        strictlyBigger("a", "B");
        strictlyBigger("small", "big");
    }

    @Test
    @DisplayName("Capitalize")
    void testCapitalize()
    {
        assertNull(JavaStringIntroduction.capitalize(null));
        Assertions.assertEquals("", JavaStringIntroduction.capitalize(""));
        Assertions.assertEquals("C", JavaStringIntroduction.capitalize("c"));
        Assertions.assertEquals("Capital", JavaStringIntroduction.capitalize("capital"));
    }
}