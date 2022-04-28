#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>
#include "Queue.hpp"
#include "Customer.hpp"

class Line : public Queue< Customer * >
{
private:
    unsigned int maxLength;
    
public:
    unsigned int lineNumber;

    Line( unsigned int maxLen, unsigned int ln );
    bool isFull();
};


Line::Line( unsigned int maxLen, unsigned int ln ) : Queue<Customer *> {},  maxLength ( maxLen ), lineNumber ( ln )
{

}


bool Line::isFull()
{
    return ( size() == maxLength );
}

#endif
