#include <iostream>
#include "hashBucket.h"

int main()
{
    if (true)
    {
        std::cout << "Bucket Based: Ints and Chars" << std::endl;
        cop3530::hashBucket<int, char> h(20);
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
        h.cluster_distribution(std::cout);
        std::cout << std::endl;
        for (unsigned int i=0; i<20; ++i)
        {
            std::cout << "Key Randomly Removed: " << h.remove_random() << std::endl;
        }
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << h.size() << std::endl;
        h.cluster_distribution(std::cout);
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
        std::cout << "Bucket Based: Strings and Ints" << std::endl;
        cop3530::hashBucket<std::string, int> h(4);
        h.insert("Hello!", 1);
        h.print(std::cout);
        std::cout << std::endl;
        int x;
        h.insert("Hello!", 2);
        std::cout << "Number of Probes to Search: " << h.search("Hello!", x) << std::endl;
        std::cout << x << std::endl;
        std::cout << "Number of Probes to Remove: " << h.remove("Hello!", x) << std::endl;
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << "Is Empty: " << h.is_empty() << std::endl;
        h.insert("Goodbye!", 1);
        h.insert("HHH", 3);
        h.insert("DDD", 4);
        h.insert("Hello!", 2);
        std::cout << "Number of Probes to Search: " << h.search("HHH", x) << std::endl;
        std::cout << x << std::endl;
        std::cout << "Number of Probes to Remove: " << h.remove("HHH", x) << std::endl;
        for (unsigned int i=0; i<h.size(); ++i)
        {
            std::cout << "Key Randomly Removed: " << h.remove_random() << std::endl;
        }
    }
    if (true)
    {
        std::cout << "Bucket Based: C-Strings and Chars" << std::endl;
        char str1[] = "Hello!";
        cop3530::hashBucket<char*, char> h(4);
        h.insert(str1, 'C');
        h.print(std::cout);
        std::cout << std::endl;
        char x;
        h.insert(str1, 'D');
        std::cout << "Number of Probes to Search: " << h.search(str1, x) << std::endl;
        std::cout << x << std::endl;
        std::cout << "Number of Probes to Remove: " << h.remove(str1, x) << std::endl;
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << "Is Empty: " << h.is_empty() << std::endl;
        char str2[] = "Goodbye!";
        h.insert(str2, 'A');
        char str3[] = "HHH";
        h.insert(str3, 'C');
        char str4[] = "DDD";
        h.insert(str4, 'D');
        h.insert(str1, 'B');
        std::cout << "Number of Probes to Search: " << h.search(str3, x) << std::endl;
        std::cout << x << std::endl;
        std::cout << "Number of Probes to Remove: " << h.remove(str3, x) << std::endl;
        for (unsigned int i=0; i<h.size(); ++i)
        {
            std::cout << "Key Randomly Removed: " << h.remove_random() << std::endl;
        }
    }
    if (true)
    {
        std::cout << "Bucket Based: Doubles and Ints" << std::endl;
        cop3530::hashBucket<double, int> h(20);
        for (double i=0; i<10; i = i + 0.2)
        {
            h.insert(i, 5);
        }
        h.print(std::cout);
        std::cout << std::endl;
        std::cout << "Number of Probes to Insert: " << h.insert(8.4, 25) << std::endl;
        int x;
        std::cout << "Number of Probes to Search: " << h.search(8.4, x) << std::endl;
        std::cout << x << std::endl;
        for (unsigned int i=0; i<40; ++i)
        {
            h.remove_random();
        }
        h.print(std::cout);
        std::cout << std::endl;
        h.cluster_distribution(std::cout);
        std::cout << std::endl;
    }
    return 0;
}
