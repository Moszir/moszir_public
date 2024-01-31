package com.data_structures.doubly_linked_list;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class DoublyLinkedListNodeTest
{
    @Test
    @DisplayName("Constructor")
    void testConstructor()
    {
        final var node = new DoublyLinkedListNode<>(5);
        assertEquals(node.data, 5);
        assertNull(node.next);
        assertNull(node.previous);
    }
}
