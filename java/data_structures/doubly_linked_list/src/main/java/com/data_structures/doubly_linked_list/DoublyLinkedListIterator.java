package com.data_structures.doubly_linked_list;

import java.util.Iterator;

/**
 * Implements the `Iterator` interface for the `DoublyLinkedList` class.
 * @param <DataType> The type of data held at the nodes of this container.
 */
public class DoublyLinkedListIterator<DataType> implements Iterator<DataType>
{
    /**
     * The node the iterator is pointing to.
     * Can be (and is by default) `null`.
     */
    DoublyLinkedListNode<DataType> currentNode;

    /**
     * Creates an iterator pointing to the given list's head.
     * @param list The list to iterate over.
     */
    public DoublyLinkedListIterator(DoublyLinkedList<DataType> list)
    {
        currentNode = list.head;
    }

    /**
     * Returns whether the iterator points to an existing node.
     * Mandatory overload to implement the `Iterator` interface.
     *
     * @return Whether the iterator points to a node.
     *
     * @warning: coming from C++, the naming is pretty silly.
     * One would expect it to return `currentNode.nextNode != null`.
     */
    @Override
    public boolean hasNext()
    {
        return currentNode != null;
    }

    /**
     * Returns the current node's data, and increments the iterator.
     * Mandatory overload to implement the `Iterator` interface.
     *
     * @return The current node's data, if it exists. `null` otherwise.
     *
     * In C++ this would correspond to something like `*it++`.
     */
    @Override
    public DataType next()
    {
        if (hasNext())
        {
            var data = currentNode.data;
            currentNode = currentNode.next;
            return data;
        }
        return null;
    }
}
