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
        r.print(std::cout);
        std::cout << std::endl;
        r.insert(3, 'B');
        r.insert(12, 'C');
        r.print(std::cout);
        std::cout << std::endl;
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
        for (unsigned int i=0; i < 3; ++i)
        {
            std::cout << "Key Randomly Removed: " << r.remove_random() << std::endl;
        }
        std::cout << "Number of Probes to Find 13: " << r.search(13, x) << std::endl;
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
    }
    if (true)
    {
        std::cout << "RBST: C-String and Ints" << std::endl;
        cop3530::RBST<char*, int> r(4);
        std::cout << "Capacity: " << r.capacity() << std::endl;
        char str1[] = "Hello!";
        char str2[] = "Goodbye!";
        char str3[] = "HHH";
        char str4[] = "DDD";
        char str5[] = "SHOULD NOT WORK";
        r.insert(str1, 12);
        r.insert(str2, 13);
        r.insert(str3, 14);
        r.insert(str4, 15);
        r.insert(str1, 16);
        r.insert(str5, 200);
        r.print(std::cout);
        std::cout << std::endl;
        int x;
        std::cout << "Number of Probes to Find Hello!: " << r.search(str1, x) << std::endl;
        std::cout << "Int at Hello!: " << x << std::endl;
        for (unsigned int i=0; i < 2; ++i)
        {
            std::cout << "Key Randomly Removed: " << r.remove_random() << std::endl;
        }
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
    }
    if (true)
    {
        std::cout << "RBST: Strings and Strings" << std::endl;
        cop3530::RBST<std::string, std::string> r(4);
        std::cout << "Capacity: " << r.capacity() << std::endl;
        std::string str1 = "Hello!";
        std::string str2 = "Goodbye!";
        std::string str3 = "HHH";
        std::string str4 = "DDD";
        r.insert(str1, "First");
        r.insert(str2, "Second");
        r.insert(str3, "Third");
        r.insert(str4, "Fourth");
        r.insert(str1, "Fifth");
        r.print(std::cout);
        std::cout << std::endl;
        std::string x;
        std::cout << "Number of Probes to Find Hello!: " << r.search(str1, x) << std::endl;
        std::cout << "String at Hello!: " << x << std::endl;
        for (unsigned int i=0; i < 2; ++i)
        {
            std::cout << "Key Randomly Removed: " << r.remove_random() << std::endl;
        }
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
    }
    if (true)
    {
        std::cout << "RBST: Doubles and Doubles" << std::endl;
        cop3530::RBST<double, double> r(50);
        std::cout << "Capacity: " << r.capacity() << std::endl;
        for (double i=0; i<13; i+=0.4)
        {
            r.insert(i, i);
        }
        r.print(std::cout);
        std::cout << std::endl;
        double x;
        std::cout << "Number of Probes to Find 1.6: " << r.search(1.6, x) << std::endl;
        std::cout << "Double at 1.6: " << x << std::endl;
        for (unsigned int i=0; i < 20; ++i)
        {
            std::cout << "Key Randomly Removed: " << r.remove_random() << std::endl;
        }
        r.print(std::cout);
        std::cout << std::endl;
        std::cout << "Load: " << r.load() << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
    }
    return 0;
}
