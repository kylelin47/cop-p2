#ifndef BASEPROBE_H
#define BASEPROBE_H
#include "item.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

namespace cop3530
{
    template <typename K, typename V>
    class baseProbe
    {
    public:
        virtual int insert( K key, V value ) {return 0;}
        virtual int remove( K key, V& value ) {return 0;}
        virtual int search( K key, V& value ) {return 0;}
        void clear()
        {
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                if (table[i] != NULL)
                {
                    delete table[i];
                    table[i] = NULL;
                }
            }
            count = 0;
        }
        bool is_empty()
        {
            return (count == 0);
        }
        std::size_t capacity() const
        {
            return max_count;
        }
        std::size_t size() const
        {
            return count;
        }
        double load()
        {
            return ((double)size())/((double)capacity());
        }
        std::ostream& print ( std::ostream& out ) const
        {
            out << "[ ";
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                if (table[i] == NULL)
                {
                    out << '-';
                }
                else
                {
                    out << table[i]->getKey();
                }
                out << ' ';
            }
            out << ']';
            return out;
        }
        K remove_random()
        {
            if (!is_empty())
            {
                srand(time(NULL));
                int i = -1;
                unsigned int R = (rand() % capacity()) + 1;
                while (R > 0)
                {
                    ++i;
                    if (i == capacity())
                    {
                        i = 0;
                    }
                    if (table[i] != NULL)
                    {
                        --R;
                    }
                }
                V a;
                K key = table[i]->getKey();
                remove( key, a );
                return key;
            }
            else
            {
                throw "Cannot return valid key";
            }
        }
        std::ostream& cluster_distribution ( std::ostream& out ) const
        {
            if (size() == capacity())
            {
                out << "((" << size() << ", 1))";
                return out;
            }
            int* tmp = new int[size() + 1];
            for (unsigned int i = 0; i < size() + 1; ++i)
            {
                tmp[i] = 0;
            }
            out << '(';
            bool first_cluster = true;
            int f = 0;
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                int cluster_size = 0;
                while (i < capacity() && table[i] != NULL)
                {
                    ++cluster_size;
                    ++i;
                }
                if (first_cluster) f = cluster_size;
                if (i == capacity()) cluster_size += f;
                else if (i == capacity() - 1) ++tmp[f];
                if (!first_cluster) ++tmp[cluster_size];
                first_cluster = false;
            }
            bool first = true;
            for (unsigned int i = 1; i < size() + 1; ++i)
            {
                if (tmp[i] > 0)
                {
                    if ( !first )
                    {
                        out << ", ";
                    }
                    out << '(';
                    out << i << ',' << tmp[i];
                    out << ')';
                    first = false;
                }
            }
            out << ')';
            delete tmp;
            return out;
        }
        bool compareKeys( const char* k1, const char* k2 )
        {
            if ( strcmp(k1, k2) == 0 ) return true;
            else return false;
        }
        bool compareKeys( int k1, int k2 )
        {
            return (k1 == k2);
        }
        bool compareKeys( std::string k1, std::string k2 )
        {
            return (k1 == k2);
        }
        bool compareKeys( double k1, double k2 )
        {
            return (k1 == k2);
        }
        std::size_t count;
        std::size_t max_count;
        item<K, V>** table;
        int* deleted;
        unsigned int hash( int k )
        {
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash2( int k )
        {
            return k % (capacity() - 1) + 1;
        }
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

            return std::size_t( hash ) % capacity();
        }
        std::size_t hash2( std::string const& s ) {
            char const* data = s.c_str();
            std::size_t hash;
            std::size_t a = 31415U;
            std::size_t b = 27183U;

            for ( hash = 0; *data != 0; ++data, a = a * b % 25165843U )
                hash = a * hash + *data;

            return hash % (capacity() - 1) + 1;
        }
        unsigned int hash( double k )
        {
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash2( double k )
        {
            return (int)k % (capacity() - 1) + 1;
        }
        unsigned int hash( char* k )
        {
            int h = 0, a = 127;
            for (; *k != 0; k++)
                h = (a*h + *k) % capacity();
            return h;
        }
        unsigned int hash2( char* k )
        {
            int h = 0, a = 31415;
            for (; *k != 0; k++)
                h = (a*h + *k) % capacity();
            return h % (capacity() -1) + 1;
        }
    };
}
#endif
