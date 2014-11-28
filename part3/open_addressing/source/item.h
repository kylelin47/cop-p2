#ifndef ITEM_H
#define ITEM_H

namespace cop3530
{
    template <typename K, typename V>
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
}
#endif // ITEM_H
