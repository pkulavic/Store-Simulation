#include <iostream>
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
    std::vector<Line *> lines;
public:
    Simulation();
    ~Simulation();
    void run();

private:
    void elapse( unsigned int tm );
    void setUp();
    void getMode();
    void setUpRegisters();
    Register * findMinLine();
    void getInLine( unsigned int num_cust, unsigned int tm );
};

Simulation::Simulation() : master_tm( 0 )
{
    // setUp();

}


Simulation::~Simulation() 
{

}

void Simulation::elapse( unsigned int tm )
{
    /* edge cases? */
    master_tm += tm;
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
        for ( int i = 0; i < reg_num; ++ i )
        {
            unsigned int tm;
            std::cin >> tm;
            registers.push_back( new Register { tm, line, i + 1 });   
        }
    }
    else if ( manyLines )
    {
        for ( int i = 0; i < reg_num; ++i )
        {
            unsigned int tm;
            std::cin >> tm;
            registers.push_back( new Register { tm, new Line { maxLine, i + 1 }, i + 1});
        }
        /* cleanup: for each in registers, delete */
    }
}


Register * Simulation::findMinLine()
{
    Register * min = registers[0];
    for ( Register * r : registers )
    {
        if ( r->line_length() < min->line_length() )
        {
            min = r;
        }
    }
    if ( min->line_length() == maxLine ) /* if there are no available lines, 
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
 
    std::cin >> a;
    while ( a != "END" )
    {
        std::cin >> b;

        int num_cust = std::stoi( a ); /* Number of customers arrived. Hopefuly and integer */
        int tm = std::stoi( b );  /* What time they all arrived (also hopefully an integer) */
        /* update the simulation time with the new moment */
        elapse( tm );

        getInLine( num_cust, tm );



        // std::cout << input << std::endl;

        // std::string a = input.substr( 0, sp_pos );
        // std::string b = input.substr( sp_pos );


        // int num_cust = std::stoi( a );
        // int tm = 0;
        // std::stoi( b );
        // std::cout << num_cust << std::endl;

        std::cin >> a;

    }

    // while ( std::getline( std::cin, input, ' ' ) )
    // {
    //     std::cout << input << std::endl;
    //     std::cin >> input;  
    // }

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
                /* add customer to lost 
                break */
            }
            else
            {
                /* there is a viable line that a customer can join */
                r->getInLine( new Customer { tm } );   
            }
        }

    }
    else 
    {

    }

}
