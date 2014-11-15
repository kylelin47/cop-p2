#ifndef HASHPROBE_H
#define HASHPROBE_H
#include <string.h>
#include <stdlib.h>
#include <time.h>
namespace cop3530
{
    template <typename K, typename V>
    class hashProbe
    {
    public:
        hashProbe( std::size_t capacity, char type )
        {
            count = 0;
            this->max_count = capacity;
            table = new item*[capacity](); //initialize table to null
            this->type = type; //what type of probe
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
            if (size() < capacity())
            {
                item* kv = new item(key, value);
                unsigned int i = hash(key);
                unsigned int j = i;
                unsigned int h = hash2(key);
                while( table[i] != NULL && !(compareKeys(table[i]->getKey(), key)) )
                {
                    ++probe_count;
                    if ( type == 'l' ) ++i;
                    else if ( type == 'q' ) i = j + probe_count * probe_count;
                    else if ( type == 'r' ) i += h;
                    while (i >= capacity())
                    {
                        i = i - capacity();
                    }
                }
                if (table[i] == NULL)
                {
                    ++count;
                }
                table[i] = kv;
                return probe_count;
            }
            else
            {
                return probe_count * -1;
            }
        }
        int remove( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = hash(key);
            unsigned int j = i;
            unsigned int h = hash2(key);
            while( table[i] != NULL && !(compareKeys(table[i]->getKey(), key)) )
            {
                ++probe_count;
                if ( type == 'l' ) ++i;
                else if ( type == 'q' ) i = j + probe_count * probe_count;
                else if ( type == 'r' ) i += h;
                while (i >= capacity())
                {
                    i = i - capacity(); //wrap-around
                }
                if (capacity() == size() && probe_count > 100)
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
                delete table[i];
                --count;
                //shift all entries in the cluster left by the proper probe amount
                int probe_count_tmp = probe_count; //need to preserve value for return
                while ( table[i] != NULL )
                {
                    ++probe_count_tmp;
                    unsigned int k;
                    if ( type == 'l' ) k = j + probe_count_tmp;
                    else if ( type == 'q' ) k = j + probe_count_tmp * probe_count_tmp;
                    else if ( type == 'r' ) k = j + h * probe_count_tmp;
                    while (k >= capacity())
                    {
                        k = k - capacity();
                    }
                    table[i] = table[k];
                    i = k;
                }
                return probe_count;
            }
        }
        int search( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = hash(key);
            unsigned int j = i;
            unsigned int h = hash2(key);
            while( table[i] != NULL && !(compareKeys(table[i]->getKey(), key)) )
            {
                ++probe_count;
                if ( type == 'l' ) ++i;
                else if ( type == 'q' ) i = j + probe_count * probe_count;
                else if ( type == 'r' ) i += h;
                while (i >= capacity())
                {
                    i = i - capacity(); //wrap-around
                }
                if (capacity() == size() && probe_count > 100)
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
            char a;
            K key = table[i]->getKey();
            remove( key, a );
            return key;
        }
        std::ostream& cluster_distribution ( std::ostream& out ) const
        {
            int* tmp = new int[size()];
            for (unsigned int i = 0; i < size(); ++i)
            {
                tmp[i] = 0;
            }
            out << '(';
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                int cluster_size = 0;
                while (i < capacity() && table[i] != NULL)
                {
                    ++cluster_size;
                    ++i;
                }
                ++tmp[cluster_size];
            }
            bool first = true;
            for (unsigned int i = 1; i < size(); ++i)
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
            item()
            {
            }
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
            //multiplication method. all multiples of 10 get mapped to 0
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash2( int k )
        {
            return 1;
        }
        unsigned int hash( std::string k )
        {
            return 0;
        }
        unsigned int hash2( std::string k )
        {
            return 1;
        }
        unsigned int hash( double k )
        {
            //multiplication method. all multiples of 10 get mapped to 0
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash2( double k )
        {
            //multiplication method. all multiples of 10 get mapped to 0
            return 1;
        }
        unsigned int hash( char* k )
        {
            //multiplication method. all multiples of 10 get mapped to 0
            return 0;
        }
        unsigned int hash2( char* k )
        {
            //multiplication method. all multiples of 10 get mapped to 0
            return 1;
        }
        char type;
    };
}

#endif // HASHPROBE_H
