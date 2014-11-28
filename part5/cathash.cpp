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
    struct rusage usage;
    struct timeval start, end;
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    while ( getline( std::cin, line ) )
    {
        hash(line);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
    printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
    return 0;
}