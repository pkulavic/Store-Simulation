#include <gtest/gtest.h>
#include "DoublyLinkedList.hpp"

TEST( parkertest, addToEndEmptyList )
{
    DoublyLinkedList< int > l1;
    l1.addToEnd( 5 );
    EXPECT_EQ(5, l1.first() );
    EXPECT_EQ(5, l1.last() );
}


TEST(parkertest, copyConstructor)
{
    DoublyLinkedList<int> l1;
    for ( int i = 0; i < 10; ++i )
    {
        l1.addToStart( i );
    }
    DoublyLinkedList<int> l2 ( l1 );
    EXPECT_EQ( l1.size(), l2.size() );
    EXPECT_EQ( 10, l1.size() );
    EXPECT_EQ( l1.last(), l2.last() );

}
TEST(parkertest, copyAssign )
{
    DoublyLinkedList<int> l1;
    for ( int i = 0; i < 5; ++ i )
    {
        l1.addToEnd( i );
    }
    DoublyLinkedList l2 = l1;
    EXPECT_EQ( l1.first(), l2.first() );
}

TEST( parkertest, iteratorValueWhenEmpty )
{
    DoublyLinkedList<int> l1;
    DoublyLinkedList<int>::Iterator it = l1.iterator();
    EXPECT_THROW( it.value(), IteratorException );

}


TEST( parkertest, removingWhileEmptyThrowsException )
{
    DoublyLinkedList<int> l1;
    DoublyLinkedList<int>::Iterator it = l1.iterator();
    EXPECT_THROW( it.remove(), IteratorException );
}

TEST( parkertest, canRemoveFromFront )
{
    DoublyLinkedList<int> l1;
    l1.addToEnd( 5 );
    l1.addToEnd( 4 );
    DoublyLinkedList<int>::Iterator it = l1.iterator();
    it.remove();
    EXPECT_EQ( 4, l1.first() );
    EXPECT_EQ( 1, l1.size() );

}

TEST( parkertest, canRemoveFromEnd )
{
    DoublyLinkedList<int> l1;
    l1.addToEnd( 5 );
    l1.addToEnd( 4 );
    DoublyLinkedList<int>::Iterator it = l1.iterator();
    it.moveToNext();
    it.remove();
    EXPECT_EQ( 5, l1.first() );
    EXPECT_EQ( 1, l1.size() );
    
}

TEST( parkertest, removeIntenalNode )
{
    DoublyLinkedList<int> l1;
    l1.addToEnd( 5 );
    l1.addToEnd( 4 );
    l1.addToEnd( 3 );
    DoublyLinkedList<int>::Iterator it = l1.iterator();
    it.moveToNext();
    it.remove();
    EXPECT_EQ( 5, l1.first() );
    EXPECT_EQ( 3, l1.last() );
}

TEST( parkertest, moveToNextAfterward )
{
    DoublyLinkedList<int> l1;
    l1.addToEnd( 5 );
    l1.addToEnd( 4 );
    l1.addToEnd( 3 );
    l1.addToEnd( 2 );
    DoublyLinkedList<int>::Iterator it = l1.iterator();
    it.moveToNext();
    it.remove(  );
    EXPECT_EQ( 3, it.value() ); // testing that moveToNextAfterward defaults to true

    it.remove( false ); // Should move to previous after deleting
    EXPECT_EQ( 5, it.value() );
}

TEST( parkertest, moveToNextAfterwardWhenRemovingFromFront )
{
}

