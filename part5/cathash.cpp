#include <cstdlib>
#include <string>
#include <iostream>

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
    getrusage();
    return 0;
}