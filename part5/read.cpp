#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/resource.h>
#define RUSAGE_SELF	0
#define RUSAGE_CHILDREN	(-1)
int main( int argc, char** argv ) {
    std::string line;
    struct rusage usage;
    struct timeval start, end;
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    while ( getline( std::cin, line ) )
    {
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
    printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
    return 0;
}