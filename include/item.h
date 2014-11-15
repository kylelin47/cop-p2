#ifndef ITEM_H
#define ITEM_H

namespace cop3530
{
    class item
    {
    private:
        int key;
        char value;
    public:
        item()
        {
        }
        item( int key, char value )
        {
            this->key = key;
            this->value = value;
        }
        int getKey() const
        {
            return key;
        }
        char getValue() const
        {
            return value;
        }
    };
}
#endif // ITEM_H
