#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "Customer.hpp"
#include "Line.hpp"

class Register
{
private:
    unsigned int checkoutDuration;
    Line * line;
    unsigned int reg_no;
    /* data */
public:
    Register( unsigned int tm, Line * l, int rn);
    ~Register();
    void checkout( Customer & customer );
    int line_length();
    void getInLine( Customer * customer );
    Customer * customer;
    bool isOccupied();
    bool checkoutIsComplete( unsigned int master_tm );
    Customer * exitCustomer();
};

Register::Register(unsigned int tm, Line * l, int rn ): checkoutDuration( tm ), line( l ), reg_no( rn ), customer( nullptr )
{
}

Register::~Register()
{
    /* delete line */
}

void Register::checkout( Customer & customer )
{
    /* Increase the customer's time by dur */   
}


int Register::line_length()
{
    return line->length();
}


void Register::getInLine( Customer * customer )
{
    line->add( customer );
}


bool Register::isOccupied()
{
    return ( customer != nullptr );
}


bool Register::checkoutIsComplete( unsigned int master_tm )
{
    return ( customer -> checkoutIsCompleteTime == master_tm );
}


Customer * Register::exitCustomer()
{
    return customer;
}

#endif

