package com.data_structures.doubly_linked_list;

public class Main
{
    public static void main(String[] args)
    {
        DoublyLinkedList<Integer> list = new DoublyLinkedList<>();
        list.append(7);
        list.append(8);
        System.out.println("Hello world!" + list.head.data + list.tail.data);
    }
}
