#include <iostream>
#include "hashOpen.h"

int main()
{
    if (true)
    {
        std::cout << "Open Addressing: Inserts, Removes, and Searches" << std::endl;
        cop3530::hashOpen h(20);
        std::cout << "Capacity: " << h.capacity() << std::endl;
        h.insert(10, 'A');
        h.insert(10, 'B');
        char x;
        h.search(10, x);
        std::cout << "Character at Key 10: " << x << std::endl;
        h.insert(20, 'C');
        std::cout << "Attempting to Remove Key 30: " << h.remove(30, x) << std::endl;
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
        for (int i=0; i<25; ++i)
        {
            h.insert(i, 'A');
        }
        std::cout << h.insert(15, 'D') << std::endl;
        std::cout << h.search(15, x) << std::endl;
        std::cout << h.search(30, x) << std::endl;
        std::cout << x << std::endl;
        h.print(std::cout);
        std::cout << std::endl;
        h.remove(12, x);
        h.remove(10, x);
        h.remove(7, x);
        h.insert(7, 'E');
        h.search(7, x);
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << x << std::endl;
    }
    if (true)
    {
        std::cout << "Open Addressing: Inserts, Removes, and Searches" << std::endl;
        cop3530::hashOpen h(100);
        std::cout << "Capacity: " << h.capacity() << std::endl;
        h.insert(10, 'A');
        h.insert(10, 'B');
        char x;
        h.search(10, x);
        std::cout << "Character at Key 10: " << x << std::endl;
        h.insert(20, 'C');
        std::cout << "Attempting to Remove Key 30: " << h.remove(30, x) << std::endl;
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
        for (int i=0; i<25; ++i)
        {
            h.insert(i, 'A');
        }
        std::cout << h.insert(15, 'D') << std::endl;
        std::cout << h.search(15, x) << std::endl;
        std::cout << h.search(30, x) << std::endl;
        std::cout << x << std::endl;
        h.print(std::cout);
        std::cout << std::endl;
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
