#include <iostream>
#include "hashOpen.h"
#include "hashBucket.h"
#include "hashProbe.h"

int main()
{
    cop3530::hashBucket h(10);
    h.insert(10, 'A');
    h.insert(10, 'B');
    h.insert(20, 'B');
    h.insert(30, 'B');
    char i;
    h.search(10, i);
    std::cout << i << std::endl;
    std::cout << h.load() << std::endl;
    h.print(std::cout);
    std::cout << std::endl;
    cop3530::hashBucket h2(25);
    h2.insert(10, 'A');
    h2.insert(20, 'B');
    char i2;
    h2.remove(10, i2);
    h2.search(20, i2);
    std::cout << i2 << std::endl;
    std::cout << h2.load() << std::endl;
    h2.print(std::cout);
    std::cout << std::endl;
    std::cout << h2.search(10, i2) << std::endl;
    cop3530::hashProbe<std::string, char> h3(20, 'q');
    h3.insert("sweg", 'A');
    h3.insert("sweg1", 'B');
    h3.insert("sweg2", 'B');
    h3.insert("sweg3", 'C');
    char i3;
    int x = h3.search("sweg3", i3);
    h3.remove_random();
    h3.print(std::cout);
    std::cout << std::endl;
    std::cout << x << std::endl;
    h3.cluster_distribution(std::cout);
    return 0;
}
