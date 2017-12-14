#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <limits>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    std::vector<int> v;

    while( std::getline( std::cin, line ) )
    {
        std::istringstream line_ss{ line };
        std::string token;

        while( std::getline( line_ss, token, ' ' ) )
        {
            std::istringstream token_ss{ token };
            int i;
            token_ss >> i;
            v.push_back( i );
        }

        std::cout << "line: " << line << std::endl;
    }

    std::cout << "Part 1: " << 0 << std::endl;

    return 0;
}
