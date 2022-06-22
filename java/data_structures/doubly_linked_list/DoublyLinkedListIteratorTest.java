import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class DoublyLinkedListIteratorTest
{
    @Test
    @DisplayName("Iterator on empty list.")
    void testEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        final var iterator = new DoublyLinkedListIterator<>(list);
        assertNull(iterator.currentNode);
        assertFalse(iterator.hasNext());
        assertNull(iterator.next());
    }

    @Test
    @DisplayName("Iterator on non-empty list.")
    void testNonEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);

        final var iterator = new DoublyLinkedListIterator<>(list);
        assertNotNull(iterator.currentNode);
        assertTrue(iterator.hasNext());
        assertEquals(1, iterator.next());
        assertFalse(iterator.hasNext());
        assertNull(iterator.next());
    }
}
