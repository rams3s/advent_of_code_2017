#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <set>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    int valid_count{ 0 };

    while( std::getline( std::cin, line ) )
    {
        std::set< std::string > set;
        std::stringstream line_ss{ line };
        std::string token;
        bool valid{ true };

        while( std::getline( line_ss, token, ' ' ) )
        {
            auto result = set.insert( token );

            if( !result.second )
            {
                valid = false;
                break;
            }
        }

        if ( valid ) ++valid_count;
    }

    std::cout << "Valid count: " << valid_count << std::endl;

    return 0;
}

