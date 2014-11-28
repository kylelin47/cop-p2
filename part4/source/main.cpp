#include <iostream>
#include "RBST.h"

int main()
{
    if (true)
    {
        std::cout << "RBST: Ints and Chars" << std::endl;
        cop3530::RBST<int, char> r(10);
        std::cout << "Capacity: " << r.capacity() << std::endl;
        r.insert(10, 'A');
        r.insert(3, 'B');
        r.insert(12, 'C');
        r.insert(15, 'D');
        r.insert(17, 'E');
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
        char x;
        std::cout << "Number of Probes to Find 3: " << r.search(3, x) << std::endl;
        std::cout << "Character at 3: " << x << std::endl;
        std::cout << "Number of Probes to Find 17: " << r.search(17, x) << std::endl;
        std::cout << "Character at 17: " << x << std::endl;
        r.clear();
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
        std::cout << "Is Empty: " << r.is_empty() << std::endl;
        r.insert(1, 'A');
        r.insert(7, 'B');
        r.insert(9, 'C');
        r.insert(13, 'D');
        r.insert(17, 'E');
        r.insert(-5, 'F');
        r.insert(-10, 'Z');
        r.insert(-10, 'G');
        std::cout << "Number of Probes to Find -10: " << r.search(-10, x) << std::endl;
        std::cout << "Character at -10: " << x << std::endl;
        std::cout << "Number of Probes to Remove 7: " << r.remove(7, x) << std::endl;
        std::cout << "Character at 7: " << x << std::endl;
        std::cout << "Number of Probes to Find 13: " << r.search(13, x) << std::endl;
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
    }
    return 0;
}
