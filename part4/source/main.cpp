#include <iostream>
#include "RBST.h"

int main()
{
    if (true)
    {
        std::cout << "RBST: Ints and Chars" << std::endl;
        cop3530::RBST<int, char> h(20);
        std::cout << "Capacity: " << h.capacity() << std::endl;
        h.insert(10, 'A');
        h.insert(10, 'B');
        char x;
        h.search(10, x);
        std::cout << "Character at Key 10: " << x << std::endl;
        for (unsigned int i=0; i < 20; ++i)
        {
            h.insert(i*10, 'A');
        }
        h.insert(20, 'C');
        std::cout << "Attempting to Remove Key 30: " << h.remove(30, x) << std::endl;
        std::cout << "Attempting to Remove Key 31: " << h.remove(31, x) << std::endl;
        h.insert(23, 'D');
        h.search(20, x);
        std::cout << "Character at Key 20: " << x << std::endl;
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << "Size: " << h.size() << std::endl;
        std::cout << "Load: " << h.load() << std::endl;
        std::cout << "Is Empty: " << h.is_empty() << std::endl;
        h.clear();
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << "Is Empty: " << h.is_empty() << std::endl;
        for (int i=0; i<75; ++i)
        {
            h.insert(i, 'A');
        }
        std::cout << h.insert(15, 'D') << std::endl;
        std::cout << h.search(15, x) << std::endl;
        std::cout << h.search(61, x) << std::endl;
        std::cout << x << std::endl;
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << std::endl;
        for (unsigned int i=0; i<h.size(); ++i)
        {
            std::cout << "Key Randomly Removed: " << h.remove_random() << std::endl;
        }
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << h.size() << std::endl;
        h.remove(12, x);
        h.remove(10, x);
        h.remove(7, x);
        h.insert(7, 'E');
        h.search(7, x);
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << x << std::endl;
    }
    return 0;
}
