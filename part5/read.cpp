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
    struct rusage usage;
    struct timeval utime, stime;
    getrusage(RUSAGE_SELF, &usage);
    utime = usage.ru_utime;
    stime = usage.ru_stime;
    std::cout << "utime: " << utime.tv_sec << '.' << utime.tv_usec << std::endl;
    std::cout << "stime: " << stime.tv_sec << '.' << stime.tv_usec << std::endl;
    return 0;
}