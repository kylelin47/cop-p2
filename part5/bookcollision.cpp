#include <cstdlib>
#include <string>
#include <iostream>
#include <string>

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