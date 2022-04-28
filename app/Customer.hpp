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

    void setExitedLineTime( unsigned int tm );
    unsigned int lineWaitTime;

public:
    Customer( unsigned int arrv ) : simArrivalTime { arrv }, tm{ 0 } 
    {

    };

    unsigned int getArrivalTime();


    unsigned int time()
    {
        return tm;
    }


    void augment( unsigned int t )
    {
        tm += t;
    }



};


void Customer::setExitedLineTime( unsigned int tm )
{
    exitedLineTime = tm;
    lineWaitTime = tm - simArrivalTime;
}

unsigned int Customer::getArrivalTime()
{
    return simArrivalTime;
}


#endif
