#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/resource.h>
#define RUSAGE_SELF	0
#define RUSAGE_CHILDREN	(-1)

std::size_t hash( std::string const& s ) {
  char const* data = s.c_str();
  std::size_t hash;
  std::size_t a = 31415U;
  std::size_t b = 27183U;

  for ( hash = 0; *data != 0; ++data, a = a * b % 25165843U )
    hash = a * hash + *data;
  
  return hash;
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
    std::cout << "User time: " << utime.tv_sec + 1.0*utime.tv_usec/1000000 << " seconds" << std::end;
    std::cout << "System time: " << stime.tv_sec + 1.0*stime.tv_usec/1000000 << " seconds" << std::end;
    return 0;
}