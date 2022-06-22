import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

// TODO This should be a two-way iterator, if such a thing exists in Java.
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
    public DoublyLinkedListIterator(@NotNull DoublyLinkedList<DataType> list)
    {
        currentNode = list.head;
    }

    /**
     * Returns whether the iterator points to an existing node.
     * Mandatory overload to implement the `Iterator` interface.
     *
     * @return Whether the iterator points to a node.
     *
     * Warning: coming from C++, the naming is pretty silly.
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

    // TODO Add `insert` method.
    // TODO Add `remove` method.
}
