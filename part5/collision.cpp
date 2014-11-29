#include <cstdlib>
#include <string>
#include <iostream>
#include <stdint.h>

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

std::size_t hash( std::string const& s ) {
  const char * data = s.c_str();
  int len = s.length();
  uint32_t hash = len, tmp;
  int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= data[sizeof (uint16_t)] << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += *data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return std::size_t( hash );
}
std::size_t hash2( std::string const& s ) {
  char const* data = s.c_str();
  std::size_t hash;
  std::size_t a = 31415U;
  std::size_t b = 27183U;

  for ( hash = 0; *data != 0; ++data, a = a * b % 25165843U )
    hash = a * hash + *data;
  
  return hash;
}
std::size_t hash3( std::string const& s ) {
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
std::size_t hash4( std::string k )
{
    const char* v = k.c_str();
    int h = 0, a = 127;
    for (; *v != 0; v++)
        h = (a*h + *v);
    return h;
}

int main( int argc, char** argv ) {
    int capacity = atoi( argv[1] );
    std::string line;
    int* collisions = new int[capacity]();
    int* collisions2 = new int[capacity]();
    int* collisions3 = new int[capacity]();
    int* collisions4 = new int[capacity]();
    int num_lines = 0;
    while ( getline( std::cin, line ) )
    {
        std::size_t index = hash(line) % capacity;
        ++collisions[index];
        std::size_t index2 = hash2(line) % capacity;
        ++collisions2[index2];
        std::size_t index3 = hash3(line) % capacity;
        ++collisions3[index3];
        std::size_t index4 = hash4(line) % capacity;
        ++collisions4[index4];
        ++num_lines;
    }
    std::cout << capacity << std::endl;
    std::cout << "Super Fast Hash" << std::endl;
    int counted = 0;
    for ( int i=1; i < capacity; ++i )
    {
        int count = 0;
        for ( int j=0; j < capacity; ++j )
        {
            if (collisions[j] == i) ++count;
        }
        if (count > 0) std::cout << i << ' ' << count << std::endl;
        counted += count * i;
        if (counted == num_lines) break;
    }
    delete[] collisions;
    std::cout << "Book Hash" << std::endl;
    counted = 0;
    for ( int i=1; i < capacity; ++i )
    {
        int count = 0;
        for ( int j=0; j < capacity; ++j )
        {
            if (collisions2[j] == i) ++count;
        }
        if (count > 0) std::cout << i << ' ' << count << std::endl;
        counted += count * i;
        if (counted == num_lines) break;
    }
    delete[] collisions2;
    counted = 0;
    std::cout << "Cat Hash" << std::endl;
    for ( int i=1; i < capacity; ++i )
    {
        int count = 0;
        for ( int j=0; j < capacity; ++j )
        {
            if (collisions3[j] == i) ++count;
        }
        if (count > 0) std::cout << i << ' ' << count << std::endl;
        counted += count * i;
        if (counted == num_lines) break;
    }
    delete[] collisions3;
    counted = 0;
    std::cout << "My Hash" << std::endl;
    for ( int i=1; i < capacity; ++i )
    {
        int count = 0;
        for ( int j=0; j < capacity; ++j )
        {
            if (collisions4[j] == i) ++count;
        }
        if (count > 0) std::cout << i << ' ' << count << std::endl;
        counted += count * i;
        if (counted == num_lines) break;
    }
    delete[] collisions4;
    return 0;
}