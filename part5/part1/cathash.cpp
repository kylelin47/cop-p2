#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/resource.h>
#define RUSAGE_SELF	0
#define RUSAGE_CHILDREN	(-1)
std::size_t hash( std::string const& s ) {
  std::size_t value = 0xC965AF37U;
  
  std::string::const_iterator iter = s.begin();
  std::string::const_iterator end = s.end();
  while ( iter != end ) {
    std::size_t mid = ((value & 0x000000FFU) ^ *iter++) << 9;
    std::size_t lo = value >> 23;
    value = ((value << 9) & 0xFFFE0000U) | mid | lo;
  }
  return value;
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