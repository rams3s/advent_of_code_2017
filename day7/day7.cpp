#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Program
{
    std::string name;
    Program * parent = nullptr;
    std::vector<Program *> children;
    int weight;
    int totalWeight;

    int computeTotalWeightRecursive()
    {
        return totalWeight = weight + std::accumulate( children.begin(), children.end(), 0, []( int w, Program * child ) { return w + child->computeTotalWeightRecursive(); } );
    }

    std::pair< bool, int > isBalanced() const
    {
        if ( children.size() >= 2 )
        {
            int first_child_weight = children[0]->totalWeight;
            int other_child_weight;
            bool first_child_weight_confirmed = false;
            bool all_the_same = true;
            int other_child_index = 0;

            for ( int i = 1; i < children.size(); ++i )
            {
                if ( !all_the_same && i > 2 ) break;

                if ( children[i]->totalWeight == first_child_weight )
                {
                    first_child_weight_confirmed = true;
                }
                else
                {
                    all_the_same = false;
                    other_child_index = i;
                    other_child_weight = children[i]->totalWeight;
                }
            }

            return std::make_pair(
                    all_the_same,
                    children[ first_child_weight_confirmed ? other_child_index : 0 ]->weight + ( first_child_weight - other_child_weight ) * ( first_child_weight_confirmed ? 1 : -1 )
                    );
        }

        return std::make_pair( true, 0 );
    }
};

int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    std::string line;
    std::map<std::string, std::unique_ptr<Program>> map;

    while( std::getline( std::cin, line ) )
    {
        char name[32];
        int weight;
        char children[256];
        memset( children, 0, sizeof( children ) );
        int scanned = std::sscanf( line.c_str(), "%s (%d) -> %[^\n]", name, &weight, children );

        auto insert = map.emplace( name, std::make_unique<Program>() );
        Program * program = insert.first->second.get();
        program->weight = weight;
        program->name = name;

        if ( scanned == 3 )
        {
            std::regex child_re( "[a-z]+" );
            auto child_it_begin = std::cregex_iterator( std::cbegin( children ), std::cend( children ), child_re );
            auto child_it_end = std::cregex_iterator();

            for ( auto child_it = child_it_begin; child_it != child_it_end; ++child_it )
            {
                auto child_insert = map.emplace( child_it->str(), std::make_unique<Program>() );
                auto * child = child_insert.first->second.get();
                child->parent = program;
                child->name = child_it->str();
                program->children.push_back( child );
            }
        }
    }

    auto root_it = std::find_if( map.cbegin(), map.cend(), []( const auto & it ) { return it.second->parent == nullptr; } );
    std::cout << "Part 1: " << root_it->first << std::endl;

    root_it->second->computeTotalWeightRecursive();

    for ( auto & it : map )
    {
        auto balanced = it.second->isBalanced();

        if ( !balanced.first )
        {
            int depth = 0;
            Program * current = it.second.get();
            while ( ( current = current->parent ) != nullptr ) ++depth;

            std::cout << "Part 2: " << it.first << " unbalanced; corrected child weight: "<< balanced.second << "; depth: " << depth << std::endl;
        }
    }

    return 0;
}
