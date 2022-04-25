// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.


#include "DoublyLinkedList.hpp"
#include <iostream>

int main()
{
    DoublyLinkedList<int> list;

    list.addToStart( 6 );
    list.addToStart( 5 );
    list.addToEnd( 7 );
    DoublyLinkedList<int>::Iterator it = list.iterator();
    
    it.insertBefore( 1 );

    return 0;
}

