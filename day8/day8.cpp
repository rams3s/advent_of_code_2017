#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    std::map<std::string, int> registers;

    int max_seen = std::numeric_limits<int>::lowest();

    while( std::getline( std::cin, line ) )
    {
        std::istringstream line_ss{ line };
        std::string reg;
        std::string op;
        int value;
        std::string dummy;
        std::string cond_a;
        std::string cond;
        int cond_b;
        line_ss >> reg >> op >> value >> dummy >> cond_a >> cond >> cond_b;

        std::map<std::string, std::function<bool(int,int)>> cond_map;

#define add_cond(_cond_) cond_map[#_cond_] = [](int a, int b) { return a _cond_ b; }

        add_cond(<);
        add_cond(>);
        add_cond(<=);
        add_cond(>=);
        add_cond(==);
        add_cond(!=);

        if ( cond_map[cond]( registers[cond_a], cond_b ) )
        {
            if (op == "inc") registers[reg] += value;
            else if (op == "dec") registers[reg] -= value;

            max_seen = std::max( max_seen, registers[ reg ] );
        }
    }

    auto max = std::max_element( registers.cbegin(), registers.cend(), [](auto & a, auto & b){ return a.second < b.second; } );

    std::cout << "Part 1: " << max->first << " " << max->second << std::endl;
    std::cout << "Part 2: " << max_seen << std::endl;

    return 0;
}
