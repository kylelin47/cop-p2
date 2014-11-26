#ifndef HASHBUCKET_H
#define HASHBUCKET_H
#include "item.h"
#include <math.h>
#include <cstddef>
#include <iostream>

namespace cop3530
{
    class hashBucket
    {
    private:
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
        size_t count;
        size_t max_count;
        Node** table;
        unsigned int hash( int k )
        {
            return floor(capacity()*(k*0.6 - floor(k*0.6)));
        }
    public:
        hashBucket( size_t capacity )
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
        bool insert( int key, char value )
        {
            Node* kv = new Node(item(key, value));
            unsigned int i = hash(key);
            if (table[i] == NULL) //nothing there; insert as head
            {
                ++count;
                table[i] = kv;
                return true;
            }
            else
            {
                Node* prev = NULL;
                Node* current = table[i];
                //iterate; can't just insert at head because have to search
                //for duplicate key
                while ( current != NULL )
                {
                    if ( current->data.getKey() == key ) //replace
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
                        ++count;
                        delete current;
                        current = NULL;
                        return true;
                    }
                    prev = current;
                    current = current->next;
                }
                //add on to end of the list
                if (prev != NULL)
                {
                    prev->next = kv;
                }
                ++count;
                return true;
            }
        }
        bool remove( int key, char &value )
        {
            unsigned int i = hash(key);
            if (table[i] == NULL) //nothing there; cannot remove
            {
                return false;
            }
            else
            {
                Node* prev = NULL;
                Node* current = table[i];
                //something's there; search through linked list to find a match
                while ( current != NULL )
                {
                    if ( current->data.getKey() == key ) //found; remove it
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
                        return true;
                    }
                    prev = current;
                    current = current->next;
                }
                //not in the linked list either
                return false;
            }
        }
        bool search( int key, char &value )
        {
            unsigned int i = hash(key);
            if (table[i] == NULL) //nothing there; cannot find
            {
                return false;
            }
            else
            {
                Node* current = table[i];
                //something's there; search through linked list to find a match
                while ( current != NULL )
                {
                    if ( current->data.getKey() == key ) //found; return it
                    {
                        value = current->data.getValue();
                        return true;
                    }
                    current = current->next;
                }
                //not in the linked list either
                return false;
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
        size_t capacity() const
        {
            return max_count;
        }
        size_t size() const
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
                    }
                }
            }
            out << ']';
            return out;
        }
    };
}

#endif // HASHBUCKET_H