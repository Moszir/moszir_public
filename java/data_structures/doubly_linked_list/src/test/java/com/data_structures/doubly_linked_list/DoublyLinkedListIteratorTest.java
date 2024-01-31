package com.data_structures.doubly_linked_list;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class DoublyLinkedListIteratorTest
{
    @Test
    @DisplayName("Constructing an iterator on an empty list.")
    void testConstructorOnEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        final var iterator = new DoublyLinkedListIterator<>(list);
        assertNull(iterator.currentNode);
    }

    @Test
    @DisplayName("Constructing an iterator on a non-empty list.")
    void testConstructorOnNonEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);

        final var iterator = new DoublyLinkedListIterator<>(list);
        // The iterator should point to the head, containing 1.
        assertNotNull(iterator.currentNode);
        assertEquals(1, iterator.currentNode.data);
    }

    @Test
    @DisplayName("Checking if an iterator points to a node.")
    void testHasNext()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);

        final var iterator = new DoublyLinkedListIterator<>(list);
        assertTrue(iterator.hasNext());
    }

    @Test
    @DisplayName("Checking that the iterator has no next node with an empty list.")
    void testHasNextEmpty()
    {
        final var list = new DoublyLinkedList<Integer>();
        final var iterator = new DoublyLinkedListIterator<>(list);
        assertFalse(iterator.hasNext());
    }

    @Test
    @DisplayName("Checking the `next()` method.")
    void testNext()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);
        list.append(2);

        final var iterator = new DoublyLinkedListIterator<>(list);
        assertEquals(1, iterator.next());
        assertEquals(2, iterator.next());
        assertNull(iterator.next());
    }

    // This is a bit of an integration test of a common use case.
    @Test
    @DisplayName("Iterating over a list with `while (it.hasNext())`.")
    void testWhileIteration()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);
        list.append(2);
        list.append(3);

        final var iterator = new DoublyLinkedListIterator<>(list);
        var expected = 1;
        while (iterator.hasNext())
        {
            assertEquals(expected++, iterator.next());
        }
    }
}
