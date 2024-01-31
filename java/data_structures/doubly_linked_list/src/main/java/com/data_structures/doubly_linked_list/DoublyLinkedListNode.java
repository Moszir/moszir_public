package com.data_structures.doubly_linked_list;

/**
 * A node of the doubly linked list.
 * @param <DataType> The type of the data.
 */
public class DoublyLinkedListNode<DataType>
{
// region Members
    /**
     * The data this node wraps.
     */
    DataType data;

    /**
     * The next node in the list.
     */
    DoublyLinkedListNode<DataType> next;

    /**
     * The previous node in the list.
     */
    DoublyLinkedListNode<DataType> previous;
// endregion Members

// region Constructors
    public DoublyLinkedListNode(DataType data)
    {
        this.data = data;
        this.next = null;
        this.previous = null;
    }
// endregion Constructors
}
