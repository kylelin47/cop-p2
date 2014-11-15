#ifndef HASHOPEN_H
#define HASHOPEN_H
#include "item.h"
#include <math.h>
#include <iostream>

namespace cop3530
{
    class hashOpen
    {
    public:
        hashOpen( std::size_t capacity )
        {
            count = 0;
            this->max_count = capacity;
            table = new item*[capacity](); //initialize table to null
        }
        ~hashOpen()
        {
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                if (table[i] != NULL)
                {
                    delete table[i];
                    table[i] = NULL;
                }
            }
            delete[] table;
            table = NULL;
        }
        bool insert( int key, char value )
        {
            if (size() < capacity())
            {
                item* kv = new item(key, value);
                unsigned int i = hash(key);
                while( table[i] != NULL && table[i]->getKey() != key )
                {
                    ++i;
                    if (i == capacity())
                    {
                        i = 0;
                    }
                }
                if (table[i] == NULL)
                {
                    ++count;
                }
                table[i] = kv;
                return true;
            }
            else
            {
                return false;
            }
        }
        bool remove( int key, char &value )
        {
            unsigned int i = hash(key);
            unsigned int j = i;
            while( table[i] != NULL && table[i]->getKey() != key )
            {
                ++i;
                if (i == capacity())
                {
                    i = 0; //wrap-around
                }
                if (i == j)
                {
                    return false; //prevent infinite loop
                }
            }
            if ( table[i] == NULL )
            {
                return false;
            }
            else
            {
                value = table[i]->getValue();
                delete table[i];
                --count;
                //shift all entries in the cluster left one
                while ( table[i] != NULL )
                {
                    unsigned int k = i + 1;
                    if (k == capacity())
                    {
                        k = 0;
                    }
                    table[i] = table[k];
                    i = k;
                }
                return true;
            }
        }
        bool search( int key, char &value )
        {
            unsigned int i = hash(key);
            unsigned int j = i;
            while( table[i] != NULL && table[i]->getKey() != key )
            {
                ++i;
                if (i == capacity())
                {
                    i = 0; //wrap-around
                }
                if (i == j)
                {
                    return false; //prevent infinite loop
                }
            }
            if ( table[i] == NULL )
            {
                return false;
            }
            else
            {
                value = table[i]->getValue();
                return true;
            }
        }
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
    private:
        std::size_t count;
        std::size_t max_count;
        item** table;
        unsigned int hash( int k )
        {
            //multiplication method. all multiples of 10 get mapped to 0
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
    };
}

#endif // HASHOPEN_H