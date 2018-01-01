#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Program
{
    std::vector<int> ConnectedTable;
    std::size_t Group = std::numeric_limits<std::size_t>::max();
};

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    std::map<int, Program> program_map;

    while( std::getline( std::cin, line ) )
    {
        std::regex re( "(\\d+) <-> (.*)");
        std::regex re2( ", " );

        std::smatch m;
        std::regex_match( line, m, re );
        int identifier = std::stoi( m[1] );

        std::string connected = m[2];
        std::sregex_token_iterator begin ( connected.cbegin(), connected.cend(), re2, -1 );
        std::sregex_token_iterator end;

        Program program;

        for ( auto it = begin; it != end; ++it )
        {
            program.ConnectedTable.push_back( std::stoi( *it ) );
        }

        program_map.emplace( identifier, std::move( program ) );
    }

    std::vector<std::set<int>> group_table;

    for ( const auto & program : program_map )
    {
        if ( program.second.Group != std::numeric_limits<std::size_t>::max() ) continue;

        std::set<int> group;
        std::deque<int> open;
        open.push_back( program.first );

        while ( !open.empty() )
        {
            int current = open.front();
            open.pop_front();
            program_map[current].Group = group_table.size();

            auto insert = group.insert( current );
            if ( !insert.second ) continue;

            const auto & connected_table = program_map[current].ConnectedTable;
            open.insert( open.end(), connected_table.cbegin(), connected_table.cend() );
        }

        group_table.push_back( std::move( group ) );
    }

    std::cout << "Part 1: " << group_table[0].size() << std::endl;
    std::cout << "Part 2: " << group_table.size() << std::endl;

    return 0;
}

