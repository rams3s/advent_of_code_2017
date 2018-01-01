#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::string input = "116	1470	2610	179	2161	2690	831	1824	2361	1050	2201	118	145	2275	2625	2333\n 976	220	1129	553	422	950	332	204	1247	1092	1091	159	174	182	984	713\n 84	78	773	62	808	83	1125	1110	1184	145	1277	982	338	1182	75	679\n 3413	3809	3525	2176	141	1045	2342	2183	157	3960	3084	2643	119	108	3366	2131\n 1312	205	343	616	300	1098	870	1008	1140	1178	90	146	980	202	190	774\n 4368	3905	3175	4532	3806	1579	4080	259	2542	221	4395	4464	208	3734	234	4225\n 741	993	1184	285	1062	372	111	118	63	843	325	132	854	105	956	961\n 85	79	84	2483	858	2209	2268	90	2233	1230	2533	322	338	68	2085	1267\n 2688	2022	112	130	1185	103	1847	3059	911	107	2066	1788	2687	2633	415	1353\n 76	169	141	58	161	66	65	225	60	152	62	64	156	199	80	56\n 220	884	1890	597	3312	593	4259	222	113	2244	3798	4757	216	1127	4400	178\n 653	369	216	132	276	102	265	889	987	236	239	807	1076	932	84	864\n 799	739	75	1537	82	228	69	1397	1396	1203	1587	63	313	1718	1375	469\n 1176	112	1407	136	1482	1534	1384	1202	604	851	190	284	1226	113	114	687\n 73	1620	81	1137	812	75	1326	1355	1545	1666	1356	1681	1732	85	128	902\n 571	547	160	237	256	30	496	592	385	576	183	692	192	387	647	233";
    std::stringstream ss( input );
    std::string line;

    std::vector< std::vector< int > > token_table;

    token_table.resize( 16 );

    int line_index = 0;

    while ( std::getline( ss, line ) )
    {
        auto & line_token_table = token_table[ line_index++ ];
        line_token_table.reserve( 16 );

        std::stringstream line_ss( line );
        std::string token;

        while ( std::getline( line_ss, token, '\t' ) )
        {
            std::stringstream token_ss( token );
            int value;
            token_ss >> value;
            line_token_table.push_back( value );
        }
    }

    int checksum = 0;

    for ( const auto & line : token_table )
    {
        auto minmax = std::minmax_element( line.cbegin(), line.cend() );

        checksum += *minmax.second - *minmax.first;
    }

    std::cout << "File checksum: " << checksum << std::endl;

    checksum = 0;

    for ( const auto & line : token_table )
    {
        bool found = false;

        for ( const auto & token : line )
        {
            for ( const auto & token2 : line )
            {
                if ( &token != &token2 && token % token2 == 0 )
                {
                    checksum += token / token2;

                    found = true;
                    break;
                }
            }

            if ( found ) break;
        }
    }

    std::cout << "File checksum: " << checksum << std::endl;

    return 0;
}
