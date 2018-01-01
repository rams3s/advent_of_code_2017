#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

template< typename It >
class cyclic_iterator
    : public std::iterator <std::bidirectional_iterator_tag, int>
{
public:

    cyclic_iterator( const It & begin, const It & end, const int index ) : begin( begin ), end( end )
    {
        auto length = std::distance( begin, end );
        current = begin;
        std::advance( current, index % length );
    }

    bool operator==( const cyclic_iterator & other ) const
    {
        return current == other.current;
    }

    bool operator!=( const cyclic_iterator & other ) const
    {
        return current != other.current;
    }

    reference operator*() const
    {
        return *current;
    }

    cyclic_iterator & operator++()
    {
        ++current;
        if (current == end) current = begin;

        return *this;
    }

    cyclic_iterator & operator--()
    {
        if (current == begin) current = end;
        --current;

        return *this;
    }

private:

    It current;
    It begin;
    It end;
};

void sparse_hash( std::array<int, 256> & v, const std::vector<int> & lengths, const int round_count )
{
    int skip = 0;
    int index = 0;

    std::iota( v.begin(), v.end(), 0 );

    for ( int i = 0; i < round_count; ++ i )
    {
        for ( const auto length : lengths )
        {
            cyclic_iterator<std::array<int, 256>::iterator> begin( v.begin(), v.end(), index );
            cyclic_iterator<std::array<int, 256>::iterator> end( v.begin(), v.end(), index + length );

            std::reverse( begin, end );
            index += length + skip;
            ++skip;
        }
    }
}

std::string dense_hash( std::array<int, 256> & v )
{
    std::ostringstream hash;
    int index = 0;

    for (int i = 0; i < 16; ++i)
    {
        int block = v[index++];
        for (int j = 1; j < 16; ++j)
        {
            block ^= v[index++];
        }
        hash << std::setfill('0') << std::setw(2) << std::hex << block;
    }

    return hash.str();
}

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string input;
    std::getline( std::cin, input );

    std::array<int, 128 * 128> grid;
    int index = 0;

    for (int i = 0; i < 128; ++i)
    {
        std::stringstream input_ss;
        input_ss << input << "-" << i;

        std::vector<int> lengths;
        lengths.reserve( input.size() + 5 );

        char c;

        while( input_ss.get( c ) )
        {
            lengths.push_back( c );
        }

        lengths.push_back( 17 );
        lengths.push_back( 31 );
        lengths.push_back( 73 );
        lengths.push_back( 47 );
        lengths.push_back( 23 );

        std::array<int, 256> v;
        sparse_hash( v, lengths, 64 );
        std::string hash = dense_hash( v );

        for ( char c : hash )
        {
            int value;

            if ( c >= '0' && c <= '9' )
            {
                value = c - '0';
            }
            else
            {
                assert ( c >= 'a' && c <= 'f' );
                value = 10 + c - 'a';
            }

            grid[index++] = ( value & 0x8 ) ? 1 : 0;
            grid[index++] = ( value & 0x4 ) ? 1 : 0;
            grid[index++] = ( value & 0x2 ) ? 1 : 0;
            grid[index++] = ( value & 0x1 ) ? 1 : 0;
        }
    }

    std::cout << "Part 1: " << std::accumulate( grid.cbegin(), grid.cend(), 0 ) << std::endl;

    int group_count = 0;
    decltype( grid )::const_iterator it;
    std::set<int> visited;

    std::for_each( grid.begin(), grid.end(), [] (auto & v) { --v; } );

    while ( ( it = std::find( grid.cbegin(), grid.cend(), 0 ) ) != grid.cend() )
    {
        std::deque<int> to_visit;

        ++group_count;
        index = std::distance( grid.cbegin(), it );

        to_visit.push_back( index );

        while ( !to_visit.empty() )
        {
            index = to_visit.front();
            to_visit.pop_front();

            if ( visited.find( index ) != visited.end() ) continue;
            visited.insert( index );

            auto & cell = grid[index];
            assert( cell == 0 );
            cell = group_count;

            auto add_cell = [&]( int cell_index ) { if ( grid[ cell_index ] == 0 ) to_visit.push_back( cell_index ); };

            int row = index / 128;
            int col = index % 128;
            if ( row > 0 ) add_cell( index - 128 );
            if ( row < 127 ) add_cell( index + 128 );
            if ( col > 0 ) add_cell( index - 1 );
            if ( col < 127 ) add_cell( index + 1 );
        }
    }

    std::cout << "Part 2: " << group_count << std::endl;

    return 0;
}
