
#include <gtest/gtest.h>
#include "Line.hpp"
#include "Register.hpp"

TEST( simulation, lineSanityChecke)
{
    unsigned int maxlen = 5;
    unsigned int line_number = 1;
    Line l { maxlen, line_number };
    EXPECT_EQ( l.size(), 0 );
    EXPECT_EQ( l.isEmpty(), true );
    l.enqueue( new Customer { 12 });
    EXPECT_EQ( l.front() -> getarrvtm(), 12 );
    l.front() -> setExitedLineTime( 14 );



}


TEST( simulation, registerGetInLineIncreasesLineSize )
{
    Line * l = new Line { 5, 1 };
    Register r { 30, l, 1 };
    Customer * c = new Customer { 10 };
    r.getInLine( c );
    EXPECT_EQ( 1, r.lineSize() );


}