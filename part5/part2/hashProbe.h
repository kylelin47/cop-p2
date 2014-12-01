#ifndef HASHPROBE_H
#define HASHPROBE_H
#include "baseProbe.h"
namespace cop3530
{
    template <typename K, typename V>
    class hashProbe : public baseProbe<K, V>
    {
    public:
        hashProbe( std::size_t max_count, char type = 'l' )
        {
            this->count = 0;
            this->max_count = max_count;
            this->table = new item<K, V>*[max_count](); //initialize this->table to null
            this->type = type; //what type of probe
            if (type != 'r' && type != 'l')
            {
                type = 'l';
            }
        }
        ~hashProbe()
        {
            for (unsigned int i = 0; i < this->capacity(); ++i)
            {
                if (this->table[i] != NULL)
                {
                    delete this->table[i];
                    this->table[i] = NULL;
                }
            }
            delete[] this->table;
            this->table = NULL;
        }
        int insert( K key, V value )
        {
            int probe_count = 0;
            unsigned int i = this->hash(key);
            unsigned int j = i;
            while( this->table[i] != NULL && !(this->compareKeys(this->table[i]->getKey(), key)) )
            {
                ++probe_count;
                i = probe(i, j, probe_count);
                if (probe_count > 10000)
                {
                    return -1 * probe_count; //prevent infinite loop while looking for something to replace
                }
            }
            if (this->table[i] == NULL)
            {
                ++this->count;
            }
            else
            {
                delete this->table[i];
            }
            item<K, V>* kv = new item<K, V>(key, value);
            this->table[i] = kv;
            return probe_count;
        }
        int remove( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = this->hash(key);
            unsigned int j = i;
            while( this->table[i] != NULL && !(this->compareKeys(this->table[i]->getKey(), key)) )
            {
                ++probe_count;
                i = probe(i, j, probe_count);
                if (probe_count > 10000)
                {
                    return -1 * probe_count; //prevent infinite loop
                }
            }
            if ( this->table[i] == NULL )
            {
                return -1 * probe_count;
            }
            else
            {
                value = this->table[i]->getValue();
                bool first = true;
                //shift all entries in the cluster left by the proper probe amount
                int probe_count_tmp = probe_count; //need to preserve value for return
                while ( this->table[i] != NULL )
                {
                    K key = this->table[i]->getKey();
                    V v = this->table[i]->getValue();
                    delete this->table[i];
                    this->table[i] = NULL;
                    --this->count;
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
            unsigned int i = this->hash(key);
            unsigned int j = i;
            while( this->table[i] != NULL && !(this->compareKeys(this->table[i]->getKey(), key)) )
            {
                ++probe_count;
                i = probe(i, j, probe_count);
                if (probe_count > 10000)
                {
                    return -1 * probe_count; //prevent infinite loop
                }
            }
            if ( this->table[i] == NULL )
            {
                return -1 * probe_count;
            }
            else
            {
                value = this->table[i]->getValue();
                return probe_count;
            }
        }
    private:
        unsigned int probe( unsigned int i, unsigned int j, int probe_count )
        {
            if ( type == 'l' ) ++i;
            else {i = j + probe_count * probe_count;}
            i = i % this->capacity();
            return i;
        }
        char type;
    };
}

#endif // HASHPROBE_H
