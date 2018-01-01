#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

struct coords
{
    int x;
    int y;
    int z;

    coords & operator+=(const coords & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    int distance_from_origin() const
    {
        assert( x + y + z == 0 );
        return std::max( std::max( std::abs( x ), std::abs( y ) ), std::abs( z ) );
    }
};

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::map<std::string,coords> m;
    m.emplace("n",coords{0,1,-1});
    m.emplace("s",coords{0,-1,1});
    m.emplace("ne",coords{1,0,-1});
    m.emplace("sw",coords{-1,0,1});
    m.emplace("nw",coords{-1,1,0});
    m.emplace("se",coords{1,-1,0});

    coords c{0,0,0};
    int max_from_origin = 0;
    std::string line;

    while( std::getline( std::cin, line ) )
    {
        std::istringstream line_ss{line};
        std::string dir;

        while( std::getline( line_ss, dir, ',' ) )
        {
            c += m[dir];
            max_from_origin = std::max( max_from_origin, c.distance_from_origin() );
        }

    }

    std::cout << "Part 1: " << c.distance_from_origin() << std::endl;
    std::cout << "Part 2: " << max_from_origin << std::endl;

    return 0;
}

