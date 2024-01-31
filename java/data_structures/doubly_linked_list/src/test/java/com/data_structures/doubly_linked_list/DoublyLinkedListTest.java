package com.data_structures.doubly_linked_list;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class DoublyLinkedListTest
{
    @Test
    @DisplayName("Constructor creates an empty list.")
    void testConstructor()
    {
        final var list = new DoublyLinkedList<Integer>();
        assertNull(list.head);
        assertNull(list.tail);
    }

    @Test
    @DisplayName("Tests that the `iterator()` points to the head.")
    void testIterator()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(8);
        list.append(9);
        list.append(10);

        final var iterator = list.iterator();
        assertNotNull(iterator.currentNode);
        assertEquals(8, iterator.currentNode.data);
    }

    @Test
    @DisplayName("Tests that the `iterator()` points to `Null` when the list is empty.")
    void testIteratorOnEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        final var iterator = list.iterator();
        assertNull(iterator.currentNode);
    }

    @Test
    @DisplayName("Tests `empty()` for empty list.")
    void testEmptyTrue()
    {
        final var list = new DoublyLinkedList<Integer>();
        assertTrue(list.empty());
    }

    @Test
    @DisplayName("Tests `empty()` for non-empty list.")
    void testEmptyFalse()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(7);
        assertFalse(list.empty());
    }

    @Test
    @DisplayName("Tests appending to an empty list.")
    void testAppendToEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);

        // Check that the head and tail are both set to the new node.
        assertNotNull(list.head);
        assertEquals(list.head, list.tail);
        assertEquals(1, list.head.data);
        assertNull(list.head.next);
        assertNull(list.head.previous);
    }

    @Test
    @DisplayName("Tests appending to a non-empty list.")
    void testAppendToNonEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.append(1);
        list.append(2);

        assertNotNull(list.head);
        assertEquals(1, list.head.data);
        assertNull(list.head.previous);
        assertNotNull(list.head.next);
        assertEquals(list.head.next, list.tail);

        assertNotNull(list.tail);
        assertEquals(2, list.tail.data);
        assertNotNull(list.tail.previous);
        assertEquals(list.tail.previous, list.head);
        assertNull(list.tail.next);
    }

    @Test
    @DisplayName("Tests prepending to an empty list.")
    void testPrependToEmptyList()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.prepend(1);

        assertNotNull(list.head);
        assertEquals(list.head, list.tail);
        assertEquals(1, list.head.data);
        assertNull(list.head.next);
        assertNull(list.head.previous);
    }

    @Test
    @DisplayName("Tests prepending to a non-empty list.")
    void testPrepend()
    {
        final var list = new DoublyLinkedList<Integer>();
        list.prepend(2);
        list.prepend(1);

        assertNotNull(list.head);
        assertEquals(1, list.head.data);
        assertEquals(list.head.next, list.tail);
        assertNull(list.head.previous);

        assertNotNull(list.tail);
        assertEquals(2, list.tail.data);
        assertNull(list.tail.next);
        assertEquals(list.tail.previous, list.head);
    }

    @Test
    @DisplayName("Tests that the list is iterable.")
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
