#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Customer.hpp"
#include "Line.hpp"

class Register
{
private:
    unsigned int checkoutDuration;
    Line * line;
    unsigned int registerNumber;
    void clearLine();


public:
    Register( unsigned int tm, Line * l, unsigned int rn, bool many_lines );
    ~Register();
    void getInLine( Customer * customer );
    Customer * customer;
    bool isOccupied();
    bool checkoutIsComplete( unsigned int master_tm );
    Customer * exitCustomer( unsigned int master_tm );
    void checkAndShiftLine( unsigned int master_tm );
    void enterRegister( Customer * newCustomer, unsigned int master_tm);
    unsigned int lineSize();
    bool lineIsFull();
    void deleteLine();
    

private:
    bool manyLines;
};

Register::Register(unsigned int tm, Line * l, unsigned int rn, bool many_lines ): checkoutDuration( tm ), line( l ), registerNumber( rn ), 
    customer( nullptr ), manyLines( many_lines )
{
}

Register::~Register()
{
    /* Line inherits Queue's destructor, which inherits DoublyLinkedList's destructor, (which I wrote!)
    So I don't think I have to manually delete all the Customers in Line. Queue should take care of that. */

    if ( manyLines )
    {
        deleteLine();
    }
    
    delete customer;

}


void Register::getInLine( Customer * customer )
{
    line->enqueue( customer );
    std::cout << customer -> getArrivalTime() << " entered line " << line -> lineNumber << " length " << line -> size() << std::endl;
}


bool Register::isOccupied()
{
    return ( customer != nullptr );
}


bool Register::checkoutIsComplete( unsigned int master_tm )
{
    if ( ! isOccupied() )
    {
        return false;
    }
    return ( customer -> checkoutIsCompleteTime == master_tm );
}


Customer * Register::exitCustomer( unsigned int master_tm )
{
    /* Exiting a customer consists of two tasks. 1-- empty this register. return the finished 
    customer so that they can be added to finishedCustomers. 3. Log this exit in the format 
    <master time> exited register < register number > */
    Customer * finishedCustomer = customer;
    customer = nullptr;
    std::cout << master_tm << " exited register " << registerNumber << std::endl;

    return finishedCustomer;
}


void Register::checkAndShiftLine( unsigned int master_tm )
{
    if ( ! line -> isEmpty() )
    {
        /* remove frome line: */
        Customer * newCustomer = line -> front();
        newCustomer -> setExitedLineTime( master_tm );
        line->dequeue();
        std::cout << master_tm << " exited line " << line -> lineNumber <<  " length " << line -> size() <<  " wait time " << newCustomer -> lineWaitTime << std::endl;

        enterRegister( newCustomer, master_tm );

    }

}


void Register::enterRegister( Customer * newCustomer, unsigned int master_tm )
{
    customer = newCustomer;  /* add the customer to this register */
    customer -> checkoutIsCompleteTime = master_tm + checkoutDuration;  /* set the customer's checkoutIsCompleteTime */
    std::cout << master_tm << " entered register " << registerNumber << std::endl;


}


unsigned int Register::lineSize()
{
    return line->size();
}


bool Register::lineIsFull()
{
    return line->isFull();
}


void Register::deleteLine()
{
    clearLine();
    delete line;
}


void Register::clearLine()
{
    while ( ! line -> isEmpty() )
    {
        delete line -> front();
        line -> dequeue();   
    }
}

#endif

