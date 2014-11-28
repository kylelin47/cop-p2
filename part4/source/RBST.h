#ifndef RBST_H
#define RBST_H
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <stack>
#include <iostream>
namespace cop3530
{
    template <typename K, typename V>
    class RBST
    {
    public:
        RBST(int capacity)
        {
            this->cap = capacity;
            count = 0;
            node_table = new Node*[capacity];
            for (unsigned int i=0; i < capacity; ++i)
            {
                node_table[i] = new Node;
            }
            for (unsigned int i=0; i < capacity - 1; ++i)
            {
                node_table[i]->left = node_table[i+1];
            }
            root = NULL;
            free = node_table[0];
        }
        ~RBST()
        {
            for (unsigned int i=0; i < capacity(); ++i)
            {
                delete node_table[i];
                node_table[i] = NULL;
            }
            delete[] node_table;
            node_table = NULL;
        }
        int insert(K key, V value)
        {
            if (root != NULL)//first search for something to replace to avoid changing structure of the tree
            {
                int probe_count = 0;
                Node* current = root;
                while ( current != NULL && compareKeys(key, current->data.getKey()) != 0 )
                {
                    if (compareKeys(key, current->data.getKey()) == -1)
                    {
                        ++probe_count;
                        current = current->left;
                    }
                    else
                    {
                        ++probe_count;
                        current = current->right;
                    }
                }
                if ( current != NULL )
                {
                    current->data = item(key, value);
                    return probe_count;
                }
            }
            int nodes_visited = 0;
            //else insert and rotate
            if (size() < capacity())
            {
                insertR(root, item(key, value), nodes_visited);
            }
            return nodes_visited;
        }
        int remove(K key, V& value)
        {
            int nodes_visited = 0;
            removeR(root, key, value, nodes_visited);
            return nodes_visited;
        }
        int search(K key, V& value)
        {
            int probe_count = 0;
            if (root != NULL)
            {
                Node* current = root;
                while ( current != NULL && compareKeys(key, current->data.getKey()) != 0 )
                {
                    if (compareKeys(key, current->data.getKey()) == -1)
                    {
                        ++probe_count;
                        current = current->left;
                    }
                    else
                    {
                        ++probe_count;
                        current = current->right;
                    }
                }
                if ( current == NULL )
                {
                    probe_count = probe_count * -1;
                }
                else
                {
                    value = current->data.getValue();
                }
            }
            return probe_count;
        }
        void clear()
        {
            for(unsigned int i=0; i < capacity() - 1; ++i)
            {
                node_table[i]->right = NULL;
                node_table[i]->left = node_table[i+1];
            }
            node_table[capacity()-1]->left = NULL;
            node_table[capacity()-1]->right = NULL;
            root = NULL;
            free = node_table[0];
            count = 0;
        }
        bool is_empty()
        {
            return (count == 0);
        }
        std::size_t capacity()
        {
            return cap;
        }
        std::size_t size()
        {
            return count;
        }
        double load()
        {
            return ((double)size())/((double)(capacity()));
        }
        void print(std::ostream& out)
        {
            out << "[ ";
            if ( root != NULL )
            {
                std::queue<Node*> q;
                q.push(root);
                while ( !q.empty() )
                {
                    Node* n = q.front();
                    q.pop();
                    out << n->data.getKey() << ' ';
                    if (n->left != NULL) q.push(n->left);
                    if (n->right != NULL) q.push(n->right);
                }
            }
            out << ']';
        }
        std::ostream& cluster_distribution ( std::ostream& out ) const
        {
            return out;
        }
        K remove_random()
        {
            srand(time(NULL));
            int i = 0;
            unsigned int R = (rand() % size()) + 1;
            if ( root != NULL )
            {
                std::stack<Node*> s;
                Node* n = root;

                while ( !s.empty() || n != NULL )
                {
                    while ( n != NULL )
                    {
                        s.push( n );
                        n = n->left;
                    }
                    n = s.top();
                    s.pop();
                    V tmp;
                    if ( ++i == R )
                    {
                        K key = n->data.getKey();
                        remove( key, tmp );
                        return key;
                    }
                    n = n->right;
                }
            }
            else
            {
                throw "Cannot return valid key";
            }
        }
    protected:
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
            Node* left;
            Node* right;
            item data;
            std::size_t subtree_size;
            Node( item data, Node* left = NULL, Node* right = NULL, std::size_t subtree_size = 1 )
            {
                this->data = data;
                this->left = left;
                this->right = right;
                this->subtree_size = subtree_size;
            }
            Node() : left(NULL), right(NULL), subtree_size(1) {}
            ~Node()
            {
                left = NULL;
                right = NULL;
            };
        };
        Node* root;
        Node* free;
        Node** node_table;
        std::size_t cap;
        std::size_t count;
        void partR(Node*& h, int k)
        {
            int t = (h->left == NULL) ? 0: h->left->subtree_size;
            if (t > k )
            {
                partR(h->left, k);
                rotR(h);
            }
            if (t < k )
            {
                partR(h->right, k-t-1);
                rotL(h);
            }
        }
        Node* joinLR(Node* a, Node* b)
        {
            if (b == NULL) return a;
            partR(b, 0);
            b->left = a;
            return b;
        }
        void removeR(Node*& h, K v, V& value, int& nodes_visited)
        {
            if (h == NULL)
            {
                nodes_visited = nodes_visited * -1;
                return;
            }
            K w = h->data.getKey();
            if (compareKeys(v, w) == -1)
            {
                ++nodes_visited;
                removeR(h->left, v, value, nodes_visited);
            }
            if (compareKeys(w, v) == -1)
            {
                ++nodes_visited;
                removeR(h->right, v, value, nodes_visited);
            }
            if (compareKeys(w, v) == 0)
            {
                Node* t = h;
                value = h->data.getValue();
                h = joinLR(h->left, h->right);
                t->left = free;
                t->right = NULL;
                free = t;
                --count;
            }
        }
        void insertR(Node*& h, item x, int& nodes_visited)
        {
            if (h == NULL)
            {
                ++count;
                h = free;
                free = free->left;
                h->left = NULL;
                h->data = x;
                return;
            }
            if (rand() < RAND_MAX/(h->subtree_size+1))
            {
                insertT(h, x, nodes_visited);
                return;
            }
            if (compareKeys(x.getKey(), h->data.getKey()) == 0 )
            {
                h->data = x;
                return;
            }
            else if (compareKeys(x.getKey(), h->data.getKey()) == -1 )
            {
                ++nodes_visited;
                insertR(h->left, x, nodes_visited);
            }
            else
            {
                ++nodes_visited;
                insertR(h->right, x, nodes_visited);
            }
            h->subtree_size++;
        }
        void insertT(Node*& h, item x, int& nodes_visited)
        {
            if (h == NULL)
            {
                ++count;
                h = free;
                free = free->left;
                h->left = NULL;
                h->data = x;
                return;
            }
            if (compareKeys(x.getKey(), h->data.getKey()) == -1 )
            {
                ++nodes_visited;
                insertT(h->left, x, nodes_visited);
                rotR(h);
            }
            else
            {
                ++nodes_visited;
                insertT(h->right, x, nodes_visited);
                rotL(h);
            }
        }
        void rotR(Node*& h)
        {
            Node* x = h->left;
            h->left = x->right;
            x->right = h;
            h = x;
        }
        void rotL(Node*& h)
        {
            Node* x = h->right;
            h->right = x->left;
            x->left = h;
            h = x;
        }
        int compareKeys( const char* k1, const char* k2 )
        {
            if (strcmp(k1, k2) == 0) return 0;
            if (strcmp(k1, k2) < 0) return -1;
            if (strcmp(k1, k2) > 0) return 1;
        }
        int compareKeys( int k1, int k2 )
        {
            if (k1==k2) return 0;
            else if (k1 < k2) return -1;
            else return 1;
        }
        int compareKeys( std::string k1, std::string k2 )
        {
            if (k1==k2) return 0;
            else if (k1 < k2) return -1;
            else return 1;
        }
        int compareKeys( double k1, double k2 )
        {
            if (k1==k2) return 0;
            if (k1 < k2) return -1;
            else return 1;
        }
    };
}
#endif // RBST_H
