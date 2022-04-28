#include <iostream>
#include <iomanip>
#include <vector>
#include "InputException.hpp"
#include "Register.hpp"
#include "Line.hpp"

class Simulation
{
private:
    unsigned int master_tm;
    unsigned int dur;
    unsigned int reg_num;
    unsigned int maxLine;
    bool manyLines;
    std::vector<Register *> registers;
    
    /* A vector for holding customers that have completed the simulation (exited a register) */
    std::vector< Customer * > finishedCustomers;

    unsigned int numberOfCustomersLost;

public:
    Simulation();
    ~Simulation();
    void run();

private:
    void setUp();
    void getMode();
    void setUpRegisters();
    Register * findMinLine();
    void getInLine( unsigned int num_cust, unsigned int tm );
    void checkAndUpdateRegisters();

    /* statistics functions */
    void printStatistics();
    unsigned int howManyEnteredLined();
    unsigned int howManyExitedLine();
    unsigned int howManyExitedRegister();
    double averageWaitTime();
    unsigned int howManyLeftInLine();
    unsigned int howManyLeftInRegister();
    unsigned int howManyLost();

    /* deleters */
    void cleanUpFinishedCustomers();
    void cleanUpRegisters();
};

Simulation::Simulation() : master_tm( 0 ), numberOfCustomersLost { 0 }
{
    setUp();
}


Simulation::~Simulation() 
{
    cleanUpRegisters();
    cleanUpFinishedCustomers();
}


void Simulation::setUp()
{
    std::cin >> dur;
    std::cin >> reg_num;
    std::cin >> maxLine;
    getMode();
    setUpRegisters();
    /* should now have a vector of registers, each with its own line
    either the same line or individual lines. 
    actually, the registers need to know their times */
    
    

}


void Simulation::getMode()
{
    char mode;
    std::cin >> mode;
    if ( mode == 'M')
    {
        manyLines = true;
    }
    else if ( mode == 'S' )
    {
        manyLines = false;
    }
    else /* what if user enters something else? */
    {
        throw InputException {};
    }
}

void Simulation::setUpRegisters()
{
    /* each register has a line. 
    If manyLines, each has its own line.
    If not many lines, each has the same line. */
    if ( ! manyLines )
    {
        /* How can I ensure that each register is sharing the same 
        Line? Is giving them each the same pointer to Line enough? */
        Line * line = new Line{ maxLine, 1 };
        for ( unsigned int i = 0; i < reg_num; ++ i )
        {
            unsigned int tm;
            std::cin >> tm;
            registers.push_back( new Register { tm, line, i + 1, manyLines });   
        }
    }
    else if ( manyLines )
    {
        for ( unsigned int i = 0; i < reg_num; ++i )
        {
            unsigned int tm;
            std::cin >> tm;
            registers.push_back( new Register { tm, new Line { maxLine, i + 1 }, i + 1, manyLines } );
        }
        /* cleanup: for each in registers, delete */
    }
}


Register * Simulation::findMinLine()
{
    Register * min = registers[0];
    for ( Register * r : registers )
    {
        if ( r->lineSize() < min->lineSize() )
        {
            min = r;
        }
    }
    if ( min->lineSize() == maxLine ) /* if there are no available lines, 
    min should still refer to registers[0] which will have length maxLine */
    {
        return nullptr;
    }
    else
    {
        return min;
    }
}


void Simulation::run()
{
    std::cout << "LOG" << std::endl << "0 start" << std::endl;

    std::string a;
    std::string b;
 
    // get user input 
    std::cin >> a >> b;

    int num_cust = std::stoi( a ); /* Number of customers arrived. Hopefuly an integer */
    int tm = std::stoi( b );
    // end get user input

    

    for ( ; master_tm < dur * 60; ++master_tm )
    {
        if ( master_tm == tm ) // It's time to load the customers
        {
            getInLine( num_cust, tm );
        }
        checkAndUpdateRegisters(); // Next, see if any customers are done and need to leave the regiser
                            // If so, exit the customer from the register and move a customer from 
                            // the line to the register. Also, check if any registers are empty and 
                            // have a non-zero line. In that case, move the customer from the line to 
                            // the register.
        
        if ( master_tm == tm )
        {
            std::cin >> a;
            if ( a == "END" ) {}
            else
            { 
                std::cin >> b;
                num_cust = std::stoi( a ); 
                tm = std::stoi( b ); 
            }
        }

    }
    std::cout << dur * 60 << " end" << std::endl << std::endl;
    printStatistics();
}


void Simulation::getInLine( unsigned int num_cust, unsigned int tm )
{
    if ( manyLines )
    {
        for ( int i = 0; i < num_cust; ++i )
        {
            Register * r = findMinLine();
            if ( r == nullptr ) 
            {
                std::cout << tm << " lost" << std::endl;
                /* add customer to lost */
                numberOfCustomersLost += 1;
            }
            else
            {
                /* there is a viable line that a customer can join */
                r->getInLine( new Customer { tm } );   
            }
        }
    }
    else /* one line */
    /* main difference is that we don't need to find the smallest line. And every register points to the same line */
    {
        for ( int i = 0; i < num_cust; ++i )
        {
            if ( registers[0] -> lineIsFull() )
            {
                std::cout << tm << " lost " << std::endl;
                numberOfCustomersLost += 1;
            }
            else 
            {
                registers[0] -> getInLine( new Customer { tm });
            }
        }
    }
}


void Simulation::checkAndUpdateRegisters()
{
    for ( Register * r : registers )
    {
        if ( r -> checkoutIsComplete( master_tm ) )
        {
            
            finishedCustomers.push_back( r -> exitCustomer( master_tm ) ); /* exit the customer from the register
            add the customer to finishedCustomers. */
            /* If there is at least one customer in line, they should immediately exit the line and enter the register */

            r -> checkAndShiftLine( master_tm );
        }
        else if ( ! r-> isOccupied() && r -> lineSize() > 0 )
        {
            r -> checkAndShiftLine( master_tm );
        }
    }
}



unsigned int Simulation::howManyEnteredLined()
{
    /* The number of customers that entered a line is equal to the number 
    of customers that exited the store ( finishedCustomers.size() ) plus
    the number of customers left in the register, plus the number of customers
    left in line. */

    return howManyExitedRegister() + howManyLeftInRegister() + howManyLeftInLine();
}


unsigned int Simulation::howManyExitedLine()
{
    /* equal to the number left in registers plus the number 
    that have finished. */
    return howManyExitedRegister() + howManyLeftInRegister();

}


unsigned int Simulation::howManyExitedRegister()
{
    /* count the number of customers in finishedCustomers */
    return finishedCustomers.size();
}


unsigned int Simulation::howManyLeftInRegister()
{
    unsigned int leftInRegister = 0;
    for ( Register * r : registers )
    {
        if ( r -> isOccupied() )
            ++ leftInRegister;
    }
    return leftInRegister;
}


unsigned int Simulation::howManyLeftInLine()
{
    /* Count the sizes of each line. In the case of one line, count the size of 
    the line. */
    if ( manyLines )
    {
        unsigned int leftInLine = 0;
        for ( Register * r : registers )
        {
            leftInLine += r -> lineSize();
        }
        return leftInLine;
    }
    else 
    {
        return registers[0] -> lineSize();
    }
}


double Simulation::averageWaitTime()
{
    /* The average time spent waiting in line is equal to 
    The sum of the waiting times of finsihedCustomers, plus
    the sum of the waiting times of customers left in 
    registers, divided by the number of people that exited 
    the store plus the number of people left in registers. */
    
    unsigned int totalForFinishedCustomers = 0;

    for ( Customer * c : finishedCustomers )
    {
        totalForFinishedCustomers += c -> lineWaitTime;
    }

    unsigned int totalForLeftInRegister = 0;
    for ( Register * r : registers )
    {
        if ( r -> isOccupied() )
            totalForLeftInRegister += r -> customer -> lineWaitTime;
    }

    return static_cast<double>( totalForLeftInRegister + totalForFinishedCustomers ) 
        / ( howManyLeftInRegister() + howManyExitedRegister() );
}


unsigned int Simulation::howManyLost()
{
    return numberOfCustomersLost;
}


void Simulation::printStatistics()
{
    std::cout << "STATS" << std::endl;
    std::cout << "Entered Line    : " << howManyEnteredLined() << std::endl;
    std::cout << "Exited Line     : " << howManyExitedLine() << std::endl;
    std::cout << "Exited Register : " << howManyExitedRegister() << std::endl;
    std::cout << "Avg Wait Time   : " << std::setprecision( 4 ) << averageWaitTime() << std::endl;
    std::cout << "Left In Line    : " << howManyLeftInLine() << std::endl;
    std::cout << "Left In Register: " << howManyLeftInRegister() << std::endl;
    std::cout << "Lost            : " << howManyLost() << std::endl;
}


void Simulation::cleanUpFinishedCustomers()
{
    for ( Customer * c : finishedCustomers )
    {
        delete c;
    }
}


void Simulation::cleanUpRegisters()
{
    if ( ! manyLines )
    {
        // In this case, we only want the line to be deleted once. 
        registers[0] -> deleteLine();
        // Register's destructor will know not to delete it.
    }

    for ( Register * r : registers )
    {
        // If there are many lines, each register's destructor will delete each unique line.
        delete r;
    }
}

