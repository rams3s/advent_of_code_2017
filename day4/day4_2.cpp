#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    int valid_count{ 0 };

    while( std::getline( std::cin, line ) )
    {
        using key_t = std::multiset<char>;
        std::map< key_t, std::string > encountered;
        std::stringstream line_ss{ line };
        std::string token;
        bool valid{ true };

        while( std::getline( line_ss, token, ' ' ) )
        {
            key_t key;

            for (char c : token)
            {
                key.insert( c );
            }

            auto result = encountered.insert( { key, token } );

            if( !result.second )
            {
                valid = false;
                //std::cout << "found invalid: " << token << std::endl;

                break;
            }
        }

        if ( valid ) ++valid_count;
    }

    std::cout << "Valid count: " << valid_count << std::endl;

    return 0;
}

