#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

constexpr int prog_count = 16;
using a16 = std::array<std::size_t, prog_count>;

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    a16 spin_exchange_table, partner_table;

    std::iota( spin_exchange_table.begin(), spin_exchange_table.end(), 0 );
    std::iota( partner_table.begin(), partner_table.end(), 0 );

    std::string command;

    while( std::getline( std::cin, command, ',' ) )
    {
        std::istringstream command_ss{ command };
        char c;
        command_ss >> c;

        switch( c )
        {
            case 's' :
            {
                a16::difference_type spin_size;
                command_ss >> spin_size;
                std::rotate( spin_exchange_table.rbegin(), spin_exchange_table.rbegin() + spin_size, spin_exchange_table.rend() );
            }
            break;

            case 'x' :
            {
                char dummy;
                std::size_t a, b;
                command_ss >> a >> dummy >> b;
                std::swap( spin_exchange_table[ a ], spin_exchange_table[ b ] );
            }
            break;

            case 'p' :
            {
                char dummy, a, b;
                command_ss >> a >> dummy >> b;
                std::iter_swap( std::find( partner_table.begin(), partner_table.end(), a - 'a' ), std::find( partner_table.begin(), partner_table.end(), b - 'a' ) );
            }
            break;
        }
    }

    auto just_dance = [ &spin_exchange_table, &partner_table ] ( const uint32_t iteration_count )
    {
        std::array< a16, 2 > dance_double_buffer;

        std::iota( dance_double_buffer[0].begin(), dance_double_buffer[0].end(), 0 );

        for ( std::size_t iteration_index = 0; iteration_index < iteration_count; ++iteration_index )
        {
            for ( std::size_t i = 0; i < prog_count; ++i )
            {
                dance_double_buffer[ 1 ][ i ] = dance_double_buffer[ 0 ][ spin_exchange_table[ i ] ];
            }

            for ( std::size_t i = 0; i < prog_count; ++i )
            {
                dance_double_buffer[ 0 ][ i ] = partner_table[ dance_double_buffer[ 1 ][ i ] ];
            }
        }

        std::string result( prog_count, 0 );

        for ( std::size_t i = 0; i < prog_count; ++i )
        {
            result[ i ] = 'a' + static_cast< char >( dance_double_buffer[ 0 ][ i ] );
        }

        return result;
    };

    std::cout << "Part 1: " << just_dance( 1 ) << std::endl;
    std::cout << "Part 2: " << just_dance( 1'000'000'000 ) << std::endl;

    return 0;
}
