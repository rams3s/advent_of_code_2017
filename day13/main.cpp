#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Layer
{
    int depth;
    int range;

    bool catchesPacket( const int delay = 0 ) const
    {
        return ( depth + delay ) % ( 2 * ( range - 1 ) ) == 0;
    }

    int getSeverity() const
    {
        return depth * range;
    }
};

struct Firewall
{
    std::vector<Layer> layerTable;

    bool catchesPacket( int delay ) const
    {
        for ( const auto & layer : layerTable )
        {
            if ( layer.catchesPacket( delay ) )
            {
                return true;
            }
        }

        return false;
    }

    int getSeverity() const
    {
        int severity = 0;

        for ( const auto & layer : layerTable )
        {
            if ( layer.catchesPacket() )
            {
                severity += layer.getSeverity();
            }
        }

        return severity;
    }
};

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    Firewall firewall;

    while( std::getline( std::cin, line ) )
    {
        std::istringstream line_ss{ line };
        Layer layer;
        std::string dummy;
        line_ss >> layer.depth;
        line_ss >> dummy;
        line_ss >> layer.range;

        firewall.layerTable.push_back( layer );
    }

    std::cout << "Part 1: " << firewall.getSeverity() << std::endl;

    int delay = 0;
    while( firewall.catchesPacket( ++delay ) );

    std::cout << "Part 2: " << delay << std::endl;

    return 0;
}

