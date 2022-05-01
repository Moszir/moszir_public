import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class SolutionTest
{
    @Test
    @DisplayName("The sample input from HackerRank")
    void testHackerRankSampleInput0()
    {
        final var results = Solution.processWords("hello", "java");
        assertEquals("9", results[0]);
        assertEquals("No", results[1]);
        assertEquals("Hello Java", results[2]);
    }
}