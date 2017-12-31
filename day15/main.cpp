#include <iostream>

uint64_t generator( const uint64_t start, const uint64_t multiplier, const uint64_t mask )
{
    uint64_t value = start;

    do
    {
        value = ( value * multiplier ) % 2147483647u;
    } while ( ( value & mask ) != 0 );

    return value;
}

int judge( const int value_count, const uint64_t a_start, const uint64_t a_mask, const uint64_t b_start, const uint64_t b_mask )
{
    int count = 0;
    uint64_t a = a_start;
    uint64_t b = b_start;

    for (int i = 0; i < value_count; ++i)
    {
        a = generator( a, 16807u, a_mask );
        b = generator( b, 48271u, b_mask );
        if ( ( a & 0xFFFF ) == ( b & 0xFFFF ) ) ++count;
    }

    return count;
}

int main()
{
    std::cout << "Part 1 test: " << judge( 40'000'000, 65u, 0u, 8921u, 0u ) << std::endl;
    std::cout << "Part 1: " << judge( 40'000'000, 512u, 0u, 191u, 0u ) << std::endl;

    std::cout << "Part 2 test: " << judge( 5'000'000, 65u, 3u, 8921u, 7u ) << std::endl;
    std::cout << "Part 2: " << judge( 5'000'000, 512u, 3u, 191u, 7u ) << std::endl;

    return 0;
}
