import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class DoublyLinkedListTest
{
    @Test
    @DisplayName("Member function `iterator()`.")
    void testIterator()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(8);
        final var iterator = list.iterator();
        assertNotNull(iterator.currentNode);
        assertEquals(8, iterator.currentNode.data);
    }

    @Test
    @DisplayName("Member function `empty()` for empty list.")
    void testEmptyTrue()
    {
        final var list = new DoublyLinkedList<Integer>();
        assertTrue(list.empty());
    }

    @Test
    @DisplayName("Member function `empty()` for non-empty list.")
    void testEmptyFalse()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(7);
        assertFalse(list.empty());
    }

    @Test
    @DisplayName("Member function `add()`.")
    void testAdd()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);
        assertNotNull(list.head);
        assertNotNull(list.tail);
        assertEquals(list.head, list.tail);
        assertEquals(1, list.head.data);
        assertNull(list.head.next);
        assertNull(list.head.previous);

        list.append(2);
        assertNotNull(list.head);
        assertNotNull(list.tail);

        assertEquals(1, list.head.data);
        assertNull(list.head.previous);
        assertNotNull(list.head.next);
        assertEquals(list.head.next, list.tail);

        assertEquals(2, list.tail.data);
        assertNotNull(list.tail.previous);
        assertEquals(list.tail.previous, list.head);
        assertNull(list.tail.next);
    }

    @Test
    @DisplayName("Member function `prepend()`.")
    void testPrepend()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.prepend(2);
        assertNotNull(list.head);
        assertNotNull(list.tail);
        assertEquals(list.head, list.tail);
        assertEquals(2, list.head.data);
        assertNull(list.head.next);
        assertNull(list.head.previous);

        list.prepend(1);
        assertNotNull(list.head);
        assertNotNull(list.tail);

        assertEquals(1, list.head.data);
        assertNull(list.head.previous);
        assertNotNull(list.head.next);
        assertEquals(list.head.next, list.tail);

        assertEquals(2, list.tail.data);
        assertNotNull(list.tail.previous);
        assertEquals(list.tail.previous, list.head);
        assertNull(list.tail.next);
    }

    @Test
    @DisplayName("For each loop")
    void testForEachLoop()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);
        list.append(2);
        list.append(3);

        var expectedValue = 1;
        for (var data : list)
        {
            assertEquals(expectedValue++, data);
        }
    }
}
