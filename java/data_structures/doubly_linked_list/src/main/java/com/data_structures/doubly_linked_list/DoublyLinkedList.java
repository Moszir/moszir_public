package com.data_structures.doubly_linked_list;

/**
 * The textbook doubly-linked list whose main application domain is interviews.
 * @param <DataType> The type of data held at the nodes of this container.
 */
public class DoublyLinkedList<DataType> implements Iterable<DataType>
{
// region Members
    /**
     * The first node in the list.
     */
    DoublyLinkedListNode<DataType> head;

    /**
     * The last node in the list.
     */
    DoublyLinkedListNode<DataType> tail;
// endregion Members

    /**
     * Implements the `iterator` function, making the class iterable.
     * @return Iterator pointing to the head of the list.
     */
    @Override
    public DoublyLinkedListIterator<DataType> iterator()
    {
        return new DoublyLinkedListIterator<>(this);
    }

    /**
     * Returns whether the list is empty.
     * @return Whether the list is empty.
     */
    boolean empty()
    {
        return this.head == null;
    }

    /**
     * Adds a new node to the end of the list.
     * @param data The data to be in the new node.
     */
    void append(DataType data)
    {
        var node = new DoublyLinkedListNode<>(data);
        if (this.empty())
        {
            this.head = node;
            // node.previous, and node.next are null.
        }
        else
        {
            this.tail.next = node;
            node.previous = this.tail;
        }
        this.tail = node;
    }

    /**
     * Adds a new node to the start of the list.
     * @param data The data to be in the new node.
     */
    void prepend(DataType data)
    {
        var node = new DoublyLinkedListNode<>(data);
        if (this.empty())
        {
            this.head = node;
            this.tail = node;
        }
        else
        {
            this.head.previous = node;
            node.next = this.head;
            this.head = node;
        }
    }
}
