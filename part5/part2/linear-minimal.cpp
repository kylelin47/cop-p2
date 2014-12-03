#include "hashProbe.h"
#include <fstream>
double find_average(int* probes, int size)
{
    double x = 0;
    int num_tries = 0;
    for ( int i=0; i < size; ++i )
    {
        num_tries += probes[i];
        x += probes[i] * i;
        if (num_tries == size) break;
    }
    return x/num_tries;
}

int main(int argc, char** argv)
{
    std::ifstream unique_file (argv[1]);
    std::ifstream read_file (argv[2]);
    int size = 45;
    //21 per row
    int table_sizes[45] = {6000,6300,6600,6900,7200,7500,7800,8100,8400,8700,9000,9300,9600,9900,10200,10500,10800,11100,11400,11700,12000,
                           6007,6301,6607,6907,7207,7507,7817,8101,8419,8707,9001,9311,9601,9901,10211,10501,10831,11113,11411,11701,12007,
                           8192,8191,6151};
    for (int i=0; i<size; ++i)
    {
        cop3530::hashProbe<std::string, int> h(table_sizes[i], 'l');
        double average_across_loads = 0;
        for (double j=0.3; j<1; j+=0.3)
        {
            h.clear();
            std::string line;
            int line_number = 0;
            int* total = new int[200000]();
            while ( getline (read_file,line) )
            {
                h.insert(line, line_number);
                ++line_number;
                if (h.load() >= j) break;
            }
            int removes = 0;
            while ( getline (read_file,line) )
            {
                h.remove_random();
                int probes = h.insert(line, line_number);
                ++total[probes];
                ++line_number;
                ++removes;
            }
            int unique_lines = 0;
            while ( getline (unique_file,line) )
            {
                int tmp;
                int probes = h.search(line, tmp);
                if (probes < 0) probes = probes * -1;
                ++total[probes];
                ++unique_lines;
            }
            double average = find_average(total, line_number);
            average_across_loads += average;
            delete[] total;
            unique_file.clear();
            unique_file.seekg(0, std::ios::beg);
            read_file.clear();
            read_file.seekg(0, std::ios::beg);
        }
        std::cout << average_across_loads/3 << std::endl;
    }
    return 0;
}