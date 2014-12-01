#ifndef HASHBUCKET_H
#define HASHBUCKET_H
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
namespace cop3530
{
    template <typename K, typename V>
    class hashBucket
    {
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
        struct Node
        {
            Node* next;
            item data;
            Node( item data, Node* next = NULL )
            {
                this->data = data;
                this->next = next;
            }
            ~Node()
            {
                next = NULL;
            };
        };
        std::size_t count;
        std::size_t max_count;
        Node** table;
        unsigned int hash( int k )
        {
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
        unsigned int hash( double k )
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
        unsigned int hash( char* k )
        {
            int h = 0, a = 127;
            for (; *k != 0; k++)
                h = (a*h + *k) % capacity();
            return h;
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
    public:
        hashBucket( std::size_t capacity )
        {
            count = 0;
            this->max_count = capacity;
            table = new Node*[capacity](); //initialize table to null
        }
        ~hashBucket()
        {
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                Node* current = table[i];
                while (current != NULL)
                {
                    Node* prev = current;
                    current = current->next;
                    delete prev;
                }
                table[i] = NULL;
            }
            delete[] table;
            table = NULL;
        }
        int insert( K key, V value )
        {
            int probe_count = 0;
            Node* kv = new Node(item(key, value));
            unsigned int i = hash(key);
            if (table[i] == NULL) //nothing there; insert as head
            {
                ++count;
                table[i] = kv;
                return probe_count;
            }
            else
            {
                Node* prev = NULL;
                Node* current = table[i];
                //iterate; can't just insert at head because have to search
                //for duplicate key
                while ( current != NULL )
                {
                    if ( compareKeys(current->data.getKey(), key) ) //replace
                    {
                        if (prev != NULL)
                        {
                            prev->next = kv;
                        }
                        else
                        {
                            table[i] = kv;
                        }
                        kv->next = current->next;
                        delete current;
                        current = NULL;
                        return probe_count;
                    }
                    prev = current;
                    current = current->next;
                    ++probe_count;
                }
                //add on to end of the list
                if (prev != NULL)
                {
                    prev->next = kv;
                }
                ++count;
                return probe_count;
            }
        }
        int remove( K key, V &value )
        {
            int probe_count = 0;
            unsigned int i = hash(key);
            if (table[i] == NULL) //nothing there; cannot remove
            {
                return -1;
            }
            else
            {
                Node* prev = NULL;
                Node* current = table[i];
                //something's there; search through linked list to find a match
                while ( current != NULL )
                {
                    if ( compareKeys(current->data.getKey(), key) ) //found; remove it
                    {
                        if (prev != NULL)
                        {
                            prev->next = current->next;
                        }
                        else
                        {
                            table[i] = current->next;
                        }
                        value = current->data.getValue();
                        delete current;
                        --count;
                        return probe_count;
                    }
                    prev = current;
                    current = current->next;
                    ++probe_count;
                }
                //not in the linked list either
                return -1 * probe_count;
            }
        }
        int search( K key, V &value )
        {
            unsigned int i = hash(key);
            int probe_count = 0;
            if (table[i] == NULL) //nothing there; cannot find
            {
                return -1;
            }
            else
            {
                Node* current = table[i];
                //something's there; search through linked list to find a match
                while ( current != NULL )
                {
                    if ( compareKeys(current->data.getKey(), key) ) //found; return it
                    {
                        value = current->data.getValue();
                        return probe_count;
                    }
                    current = current->next;
                    ++probe_count;
                }
                //not in the linked list either
                return -1 * probe_count;
            }
        }
        void clear()
        {
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                Node* current = table[i];
                while (current != NULL)
                {
                    Node* prev = current;
                    current = current->next;
                    delete prev;
                }
                table[i] = NULL;
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
            double occupied_buckets = 0;
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                occupied_buckets += (table[i] != NULL);
            }
            return (occupied_buckets/((double)capacity()));
        }
        std::ostream& print ( std::ostream& out ) const
        {
            out << "[ ";
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                if (table[i] == NULL)
                {
                    out << "- ";
                }
                else
                {
                    Node* current = table[i];
                    while ( current != NULL )
                    {
                        out << current->data.getKey() << ' ';
                        current = current->next;
                        if (current == NULL) out << '|';
                    }
                }
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
                unsigned int R = (rand() % size()) + 1;
                Node* current;
                while (R > 0)
                {
                    ++i;
                    if (i == capacity())
                    {
                        i = 0;
                    }
                    current = table[i];
                    while (current != NULL)
                    {
                        --R;
                        if ( R == 0) break;
                        current = current->next;
                    }
                }
                V a;
                K key = current->data.getKey();
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
            int* tmp = new int[size() + 1];
            for (unsigned int i = 0; i < size() + 1; ++i)
            {
                tmp[i] = 0;
            }
            out << '(';
            for (unsigned int i = 0; i < capacity(); ++i)
            {
                int cluster_size = 0;
                Node* current = table[i];
                while (current != NULL)
                {
                    ++cluster_size;
                    current = current->next;
                }
                ++tmp[cluster_size];
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
    };
}

#endif // HASHBUCKET_H
