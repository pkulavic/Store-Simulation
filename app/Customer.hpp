#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "Queue.hpp"

class Customer
{
private:
    unsigned int simArrivalTime;
    unsigned int exitedLineTime;
    
    unsigned int tm;
public: 
    unsigned int checkoutIsCompleteTime;

public:
    Customer( unsigned int arrv ) : simArrivalTime { arrv }, tm{ 0 } 
    {

    };


    unsigned int time()
    {
        return tm;
    }


    void augment( unsigned int t )
    {
        tm += t;
    }



};

#endif
