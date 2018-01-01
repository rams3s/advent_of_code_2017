#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int getSteps( const std::vector<int> & input, std::function<void(int&)> update_fn )
{
    std::vector<int> v = input;
    std::size_t index = 0;
    int count = 0;

    while ( index < v.size() )
    {
        auto & value = v[index];
        index = static_cast< std::size_t> ( static_cast<int> (index) + value );
        update_fn( value );
        ++count;
    }

    return count;
}

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );
    std::vector<int> v;
    std::string line;

    while( std::getline( std::cin, line ) )
    {
        v.push_back( std::stoi(line) );
    }

    std::cout << "Part 1: " << getSteps( v, []( int & value ) { ++value; } ) << std::endl;
    std::cout << "Part 2: " << getSteps( v, []( int & value ) { if(value>=3) --value; else ++value; } ) << std::endl;

    return 0;
}
