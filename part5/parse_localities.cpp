#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

int main( int argc, char** argv ) {
    std::string line;
    std::ofstream uid, location, country, population, coords;
    uid.open("uid.txt");
    location.open("location.txt");
    country.open("country.txt");
    population.open("population.txt");
    coords.open("coords.txt");
    
    std::stringstream sline;
    while ( getline( std::cin, line ) )
    {
        sline << line;
        std::string token;
        int i = 0;
        while ( getline(sline, token, ' ') )
        {
            if (i == 0) uid << token << '\n';
            else if (i == 1) location << token << '\n';
            else if (i == 2) country << token << '\n';
            else if (i == 3) population << token << '\n';
            else if (i == 4) coords << token << '\n';
            ++i;
        }
        sline.clear();
    }
    uid.close();
    location.close();
    country.close();
    population.close();
    coords.close();
    return 0;
}