#include <gtest/gtest.h>
#include "DoublyLinkedList.hpp"

TEST( parkertest, addToEndEmptyList )
{
    DoublyLinkedList< int > l1;
    l1.addToEnd( 5 );
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