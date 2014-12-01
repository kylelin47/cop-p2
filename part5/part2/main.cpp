#include "hashBucket.h"
#include <fstream>
#include <vector>
void print_probes(int* probes, int size)
{
    for ( int i=0; i < size; ++i )
    {
        if (probes[i] > 0) std::cout << i << ' ' << probes[i] << std::endl;
    }
}
void print_probes_negative(int* probes, int size)
{
    for ( int i=0; i < size; ++i )
    {
        if (probes[i] > 0) std::cout << '-' << i << ' ' << probes[i] << std::endl;
    }
}
int main(int argc, char** argv)
{
    int size = 42;
    //21 per row
    int table_sizes[42] = {6000,6300,6600,6900,7200,7500,7800,8100,8400,8700,9000,9300,9600,9900,10200,10500,10800,11100,11400,11700,12000,
                           6007,6301,6607,6907,7207,7507,7817,8101,8419,8707,9001,9311,9601,9901,10211,10501,10831,11113,11411,11701,12007};
    std::ifstream unique_file (argv[1]);
    std::ifstream read_file (argv[2]);
    for (int i=0; i<size; ++i)
    {
        cop3530::hashBucket<std::string, int> h(table_sizes[i]);
        for (double j=0.03; j<=0.99; j+=0.03)
        {
            std::string line;
            int line_number = 0;
            int* insert_probes = new int[300000]();
            while ( getline (read_file,line, ' ') )
            {
                h.insert(line, line_number);
                ++line_number;
                if (h.load() >= j) break;
            }
            while ( getline (read_file,line, ' ') )
            {
                h.remove_random();
                ++insert_probes[h.insert(line, line_number)];
                ++line_number;
            }
            int* successes = new int[line_number]();
            int* failures = new int[line_number]();
            int unique_lines = 0;
            while ( getline (unique_file,line) )
            {
                int tmp;
                int probes = h.search(line, tmp);
                if (probes >= 0) ++successes[probes];
                else ++failures[-1 * probes];
                ++unique_lines;
            }
            std::cout << "Load Factor: " << j << std::endl;
            std::cout << "Capacity: " << h.capacity() << std::endl;
            std::cout << "Size: " << h.size() << std::endl;
            std::cout << "Items in Trial: " << line_number << std::endl;
            std::cout << "Items in Unique: " << unique_lines << std::endl;
            std::cout << "Insert Probe Count Distribution" << std::endl;
            print_probes(insert_probes, line_number);
            std::cout << "Success Search Probe Count Distribution" << std::endl;
            print_probes(successes, line_number);
            std::cout << "Failure Search Probe Count Distribution" << std::endl;
            print_probes_negative(failures, line_number);
            delete[] successes;
            delete[] failures;
            delete[] insert_probes;
            unique_file.clear();
            unique_file.seekg(0, std::ios::beg);
            read_file.clear();
            read_file.seekg(0, std::ios::beg);
        }
    }
    return 0;
}