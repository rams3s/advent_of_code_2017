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
    int valid_count_1{ 0 };
    int valid_count_2{ 0 };

    while( std::getline( std::cin, line ) )
    {
        std::set< std::string > encountered_1;
        using key_t = std::multiset<char>;
        std::map< key_t, std::string > encountered_2;
        std::stringstream line_ss{ line };
        std::string token;
        bool valid_1{ true };
        bool valid_2{ true };

        while( std::getline( line_ss, token, ' ' ) )
        {
            key_t key;

            for (char c : token)
            {
                key.insert( c );
            }

            if ( auto [it, inserted] = encountered_1.insert( token ); !inserted ) valid_1 = false;
            if ( auto [it, inserted] = encountered_2.insert( { key, token } ); !inserted ) valid_2 = false;

            if( !valid_1 && !valid_2 ) break;
        }

        if ( valid_1 ) ++valid_count_1;
        if ( valid_2 ) ++valid_count_2;
    }

    std::cout << "Part 1: " << valid_count_1 << std::endl;
    std::cout << "Part 2: " << valid_count_2 << std::endl;

    return 0;
}

