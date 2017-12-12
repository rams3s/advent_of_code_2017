#include <algorithm>
#include <iostream>

struct ivec2
{
    int x;
    int y;

    ivec2 & operator+= (const ivec2 & other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }
};

int main()
{
    constexpr ivec2 movement_table[] = {
        { 1, 0 },
        { 0, 1 },
        { -1, 0 },
        { 0, -1 }
    };
    constexpr int input{ 289326 };

    {
        ivec2 coords{ 0, 0 };
        int current_length{ 0 };
        int length{ 1 };
        int movement_index{ 0 };

        for (int i = 2; i <= input; ++i )
        {
            coords += movement_table[ movement_index ];

            if ( ++current_length == length )
            {
                current_length = 0;
                movement_index = ( movement_index + 1 ) % 4;
                length += (~movement_index) & 1;
            }
        }

        std::cout << "x: " << coords.x << " y: " << coords.y << std::endl;
        std::cout << "distance: " << ( std::abs( coords.x ) + std::abs( coords.y ) ) << std::endl;
    }

    {
        int current_length{ 0 };
        int length{ 1 };
        int movement_index{ 0 };
        constexpr int size = 200; //std::ceil( std::sqrt( input ) ); // over evaluated for this problem
        ivec2 coords{ size / 2, size / 2 };
        int array[size][size];

        int * current = &array[ 0 ][ 0 ];
        std::fill( current, current + size * size, 0 );

        current = &array[ coords.x ][ coords.y ];
        *current = 1;

        while ( *current <= input )
        {
            coords += movement_table[ movement_index ];
            current = &array[ coords.x ][ coords.y ];

            *current += array[ coords.x + 1 ][ coords.y + 0 ];
            *current += array[ coords.x + 1 ][ coords.y + 1 ];
            *current += array[ coords.x + 0 ][ coords.y + 1 ];
            *current += array[ coords.x - 1 ][ coords.y + 1 ];
            *current += array[ coords.x - 1 ][ coords.y + 0 ];
            *current += array[ coords.x - 1 ][ coords.y - 1 ];
            *current += array[ coords.x + 0 ][ coords.y - 1 ];
            *current += array[ coords.x + 1 ][ coords.y - 1 ];

            if ( ++current_length == length )
            {
                current_length = 0;
                movement_index = ( movement_index + 1 ) % 4;
                length += (~movement_index) & 1;
            }
        }

        std::cout << "x: " << coords.x << " y: " << coords.y << std::endl;
        std::cout << "value: " << *current << std::endl;
    }
    return 0;
}
