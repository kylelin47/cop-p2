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
    int capacity = atoi( argv[1] );
    std::string line;
    int collisions[200000] = { 0 };
    while ( getline( std::cin, line ) )
    {
        std::size_t index = hash(line) % capacity;
        ++collisions[index];
    }
    std::cout << capacity << std::endl;
    for ( int i=1; i < capacity; ++i )
    {
        int count = 0;
        for ( int j=0; j < capacity; ++j )
        {
            if (collisions[j] == i) ++count;
        }
        if (count > 0) std::cout << i << ' ' << count << std::endl;
    }
    return 0;
}