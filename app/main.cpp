#include <iostream>
#include <vector>
#include <algorithm>

#include "Customer.hpp"
#include "Simulation.hpp"

void get_input ( unsigned int & var )
{
    std::cin >> var;
}

int main()
{

    Simulation s {};
    s.run();

    // unsigned int  dur = 0;
    // unsigned int reg = 0;
    // unsigned int maxLine = 0;
    // unsigned int lineMode = 0;
    
    // // Store data in vector
    // std::vector< unsigned int  > input { dur, reg, maxLine, lineMode };

    // // Populate vector with user input
    // std::for_each( input.begin(), input.end(), get_input );

    // // Print vector to ensure write
    // std::for_each( input.begin(), input.end(), [] ( unsigned int & var ) { std::cout << var << std::endl; });

    // // Get register duration input

    // // Store register durations in vector
    // std::vector<unsigned int> regTime;

    // // For each register, get input
    // for ( unsigned int i = 0; i < input[0]; ++i )
    // {
    //     unsigned int time = 0;
    //     regTime.push_back( time );
    //     get_input( regTime[i] );
    // }
    // // Print register times 
    // std::for_each( regTime.begin(), regTime.end(), [] ( unsigned int & var ) { std::cout << var << std::endl; });

    // std::cout << dur << std::endl;
    

    // // Main loop
    // std::string inp;
    // std::cin >> inp;
    // if ( input[3] == 83 )  // If user has selected single line
    // { while ( inp != "END" )
    // {


        

    // }
            
    // }
    

    return 0;
}

