#ifndef HASHPROBE_H
#define HASHPROBE_H
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
namespace cop3530
{
    template <typename K, typename V>
    class hashProbe
    {
    public:
        hashProbe( std::size_t max_count, char type = 'l' )
        {
            count = 0;
            this->max_count = max_count;
            table = new item*[max_count](); //initialize table to null
            this->type = type; //what type of probe
            if (type != 'r' && type != 'l')
            {
                type = 'l';
            }
        }
        ~hashProbe()
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
        int insert( K key, V value )
        {
            int probe_count = 0;
            unsigned int i = hash(key);
            unsigned int j = i;
            while( table[i] != NULL && !(compareKeys(table[i]->getKey(), key)) )
            {
                ++probe_count;
                i = probe(i, j, probe_count);
                if (probe_count > 10000)
                {
                    return -1 * probe_count; //prevent infinite loop while looking for something to replace
                }
            }
            if (table[i] == NULL)
            {
                ++count;
            }
            else
            {
                delete table[i];
            }
            item* kv = new item(key, value);
            table[i] = kv;
            return probe_count;
        }
        int remove( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = hash(key);
            unsigned int j = i;
            while( table[i] != NULL && !(compareKeys(table[i]->getKey(), key)) )
            {
                ++probe_count;
                i = probe(i, j, probe_count);
                if (probe_count > 10000)
                {
                    return -1 * probe_count; //prevent infinite loop
                }
            }
            if ( table[i] == NULL )
            {
                return -1 * probe_count;
            }
            else
            {
                value = table[i]->getValue();
                bool first = true;
                //shift all entries in the cluster left by the proper probe amount
                int probe_count_tmp = probe_count; //need to preserve value for return
                while ( table[i] != NULL )
                {
                    K key = table[i]->getKey();
                    V v = table[i]->getValue();
                    delete table[i];
                    table[i] = NULL;
                    --count;
                    if (!first)//first needs to actually be deleted, not reinserted in proper place
                    {
                        insert(key, v);
                    }
                    first = false;
                    ++probe_count_tmp;
                    i = probe(i, j, probe_count_tmp);
                }
                return probe_count;
            }
        }
        int search( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = hash(key);
            unsigned int j = i;
            while( table[i] != NULL && !(compareKeys(table[i]->getKey(), key)) )
            {
                ++probe_count;
                i = probe(i, j, probe_count);
                if (probe_count > 10000)
                {
                    return -1 * probe_count; //prevent infinite loop
                }
            }
            if ( table[i] == NULL )
            {
                return -1 * probe_count;
            }
            else
            {
                value = table[i]->getValue();
                return probe_count;
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
    private:
        class item
        {
        private:
            K key;
            V value;
        public:
            item(){}
            item( K key, V value )
            {
                this->key = key;
                this->value = value;
            }
            K getKey() const
            {
                return key;
            }
            V getValue() const
            {
                return value;
            }
        };
        std::size_t count;
        std::size_t max_count;
        item** table;
        unsigned int hash( int k )
        {
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash( std::string k )
        {
            const char* v = k.c_str();
            int h = 0, a = 127;
            for (; *v != 0; v++)
                h = (a*h + *v) % capacity();
            return h;
        }
        unsigned int hash( double k )
        {
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash( char* k )
        {
            int h = 0, a = 127;
            for (; *k != 0; k++)
                h = (a*h + *k) % capacity();
            return h;
        }
        unsigned int probe( unsigned int i, unsigned int j, int probe_count )
        {
            if ( type == 'l' ) ++i;
            else {i = j + probe_count * probe_count;}
            i = i % capacity();
            return i;
        }
        char type;
    };
}

#endif // HASHPROBE_H
