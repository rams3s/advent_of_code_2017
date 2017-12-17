#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

template< typename It >
class cyclic_iterator
    : public std::iterator <std::bidirectional_iterator_tag, int>
{
public:

    cyclic_iterator( const It & begin, const It & end ) : current( begin ), begin( begin ), end( end ) {}

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

    cyclic_iterator operator++( int )
    {
        cyclic_iterator saved = *this;
        ++*this;

        return saved;
    }

    cyclic_iterator & operator--()
    {
        if (current == begin) current = end;
        --current;

        return *this;
    }

    cyclic_iterator operator--(int)
    {
        cyclic_iterator saved = *this;
        --*this;

        return saved;
    }

private:

    It current;
    It begin;
    It end;
};

void sparse_hash( std::vector<int> & v, const std::vector<int> & lengths, const int round_count )
{
    int skip = 0;
    int index = 0;

    std::iota( v.begin(), v.end(), 0 );

    for ( int i = 0; i < round_count; ++ i )
    {
        for ( const auto length : lengths )
        {
            cyclic_iterator<std::vector<int>::iterator> begin( v.begin(), v.end() );
            std::advance( begin, index );
            cyclic_iterator<std::vector<int>::iterator> end( v.begin(), v.end() );
            std::advance( end, index + length );

            std::reverse( begin, end );
            index += length + skip;
            ++skip;
        }
    }
}

std::string dense_hash( std::vector<int> & v )
{
    assert( v.size() == 256 );

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

    std::vector<int> lengths;
    std::istringstream input_ss{ input };
    std::string token;

    while( std::getline( input_ss, token, ',' ) )
    {
        int length = std::atoi( token.c_str() );
        lengths.push_back( length );
    }

    std::vector<int> v(256);
    sparse_hash( v, lengths, 1 );

    std::cout << "Part 1: " << v[0] * v[1] << std::endl;

    std::istringstream input_ss2{ input };
    lengths.clear();
    lengths.reserve( input.size() + 5 );

    char c;

    while( input_ss2.get( c ) )
    {
        lengths.push_back( c );
    }

    lengths.push_back( 17 );
    lengths.push_back( 31 );
    lengths.push_back( 73 );
    lengths.push_back( 47 );
    lengths.push_back( 23 );

    sparse_hash( v, lengths, 64 );

    std::cout << "Part 2: " << dense_hash( v ) << std::endl;

    return 0;
}
