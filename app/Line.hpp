#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>
#include "Queue.hpp"
#include "Customer.hpp"

class Line 
{
private:
    unsigned int maxLength;
    unsigned int line_no;
    Queue< Customer * > q;
public:

    Line( unsigned int maxLen, int ln ) : maxLength ( maxLen ), line_no ( ln )
    {
    }

    int add ( Customer * c );
    int length();
    Customer * remove ();

};


int Line::add( Customer * c )
{
    if ( length() == maxLength )
        {
            return 0;   
        }
        q.enqueue( c );
        std::cout << c->time() << " entered line " << line_no << " length " << length() << std::endl;

        return 1;
}


int Line::length()
{
    return q.size();
}

#endif
