#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    using ivec = std::vector<int>;
    ivec v;
    std::map<ivec, int> seen;

    while( std::getline( std::cin, line ) )
    {
        std::stringstream line_ss{ line };
        std::string token;

        while( std::getline( line_ss, token, '\t' ) )
        {
            int i;
            std::stringstream token_ss{ token };
            token_ss >> i;
            v.push_back( i );
        }
    }

    int count = 0;
    bool inserted;

    do
    {
        auto max = std::max_element( v.cbegin(), v.cend() );
        int value = *max;
        int index = max - v.cbegin();
        v[index] = 0;

        while ( value > 0 )
        {
            index = ++index % v.size();
            ++(v[index]);
            --value;
        }

        ++count;

        auto insert = seen.emplace( v, count );
        inserted = insert.second;
    }
    while (inserted);

    std::cout << "Part 1: " << count << std::endl;
    int cycle_length = count - seen[v];
    std::cout << "Part 2: " << cycle_length << std::endl;

    return 0;
}
