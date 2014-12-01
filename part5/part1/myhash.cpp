#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/resource.h>
#define RUSAGE_SELF	0
#define RUSAGE_CHILDREN	(-1)

std::size_t hash( std::string k )
{
    const char* v = k.c_str();
    int h = 0, a = 127;
    for (; *v != 0; v++)
        h = (a*h + *v);
    return h;
}
int main( int argc, char** argv ) {
    std::string line;
    while ( getline( std::cin, line ) )
    {
        hash(line);
    }
    struct rusage usage;
    struct timeval utime, stime;
    getrusage(RUSAGE_SELF, &usage);
    utime = usage.ru_utime;
    stime = usage.ru_stime;
    std::cout << "User time: " << utime.tv_sec + 1.0*utime.tv_usec/1000000 << " seconds" << std::endl;
    std::cout << "System time: " << stime.tv_sec + 1.0*stime.tv_usec/1000000 << " seconds" << std::endl;
    return 0;
}