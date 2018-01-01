#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    char c;
    std::stringstream filtered;

    while( std::cin.get( c ) )
    {
        if (c == '!') std::cin.ignore(1);
        else filtered << c;
    }

    std::stringstream filtered2;
    int garbage = 0;

    while( filtered.get( c ) )
    {
        if (c == '<')
        {
            filtered.ignore( std::numeric_limits< std::streamsize >::max(), '>' );
            garbage += filtered.gcount() - 1;
        }
        else filtered2 << c;
    }

    int depth = 0;
    int score = 0;

    while( filtered2.get( c ) )
    {
        if (c == '{')
        {
            ++depth;
        }
        else if (c == '}')
        {
            score += depth;
            --depth;
            assert( depth >= 0 );
        }
    }

    std::cout << "Part 1: " << score << std::endl;
    std::cout << "Part 2: " << garbage << std::endl;

    return 0;
}
