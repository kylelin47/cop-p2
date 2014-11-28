#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/resource.h>
#define RUSAGE_SELF	0
#define RUSAGE_CHILDREN	(-1)
int main( int argc, char** argv ) {
    std::string line;
    while ( getline( std::cin, line ) )
    {
    }
    getrusage();
    return 0;
}