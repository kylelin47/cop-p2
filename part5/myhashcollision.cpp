#include <cstdlib>
#include <string>
#include <iostream>
#include <string>

std::size_t hash( std::string k )
{
    const char* v = k.c_str();
    int h = 0, a = 127;
    for (; *v != 0; v++)
        h = (a*h + *v) % capacity();
    return h;
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