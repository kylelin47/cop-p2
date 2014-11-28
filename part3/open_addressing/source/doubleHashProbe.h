#ifndef DOUBLEHASHPROBE_H
#define DOUBLEHASHPROBE_H
#include "baseProbe.h"
namespace cop3530
{
    template <typename K, typename V>
    class doubleHashProbe : public baseProbe<K, V>
    {
    public:
        doubleHashProbe( std::size_t max_count )
        {
            this->count = 0;
            this->max_count = max_count;
            this->table = new item<K, V>*[max_count](); //initialize table to null
            this->deleted = new int[max_count];
            for (unsigned int i=0; i < max_count; ++i)
            {
                this->deleted[i] = 0;
            }
        }
        ~doubleHashProbe()
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
            delete[] this->deleted;
            this->deleted = NULL;
        }
        int insert( K key, V value )
        {
            int probe_count = 0;
            unsigned int i = this->hash(key);
            unsigned int h = this->hash2(key);
            while( this->deleted[i] != 0 && this->deleted[i] != 1 )
            {
                if (this->table[i] != NULL && this->compareKeys(this->table[i]->getKey(), key))
                {
                    item<K, V>* kv = new item<K, V>(key, value);
                    delete this->table[i];
                    this->table[i] = kv;
                    this->deleted[i] = 2;
                    return probe_count;
                }
                ++probe_count;
                i += h;
                i = i%this->capacity();
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
            this->deleted[i] = 2;
            return probe_count;
        }
        int remove( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = this->hash(key);
            unsigned int h = this->hash2(key);
            while( this->deleted[i] != 0 )
            {
                if (this->table[i] != NULL && this->compareKeys(this->table[i]->getKey(), key))
                {
                    value = this->table[i]->getValue();
                    this->deleted[i] = 1;
                    delete this->table[i];
                    this->table[i] = NULL;
                    --this->count;
                    return probe_count;
                }
                ++probe_count;
                i += h;
                i = i%this->capacity();
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
                this->deleted[i] = 1;
                delete this->table[i];
                this->table[i] = NULL;
                --this->count;
                return probe_count;
            }
        }
        int search( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = this->hash(key);
            unsigned int h = this->hash2(key);
            while( this->deleted[i] != 0 )
            {
                if (this->table[i] != NULL && this->compareKeys(this->table[i]->getKey(), key))
                {
                    value = this->table[i]->getValue();
                    return probe_count;
                }
                ++probe_count;
                i += h;
                i = i%this->capacity();
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
    };
}

#endif
