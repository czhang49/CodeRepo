/**
 * @file wordcount.cpp
 * Testing program for the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "word_counter.h"

using namespace cs225;

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::vector;

template <template <class K, class V> class HT>
void countWords( const string & file, int frequency ) {
    WordFreq<HT> wf( file );
cout<<"I'm here at wordcount.cpp line "<<__LINE__<<endl;
    vector< pair<string, int> > ret = wf.getWords( frequency );
cout<<"I'm here at wordcount.cpp line "<<__LINE__<<endl;
cout<<"I'm here at wordcount.cpp line "<<__LINE__<<"The number of found words is "<<ret.size()<<"\n"<<endl;
    for( unsigned int i = 0; i < ret.size(); i++ )
        cout << ret[i].first << " " << ret[i].second << endl;
}

void printUsage( const string & progname ) {
    cout << progname << " filename frequency tabletype" << endl;
    cout << "\tfilename: path to the file to count characters in" << endl;
    cout << "\tfrequency: threshold at which a character's frequency must "
        "be to appear in output" << endl;
    cout << "\ttabletype: type of hash table to use (sc_hash_table or lp_hash_table)" << endl;
}

int main( int argc, char ** argv ) {
    vector<string> args( argv, argv+argc );
    if( argc < 4 ) {
        printUsage( args[0] );
        return 1;
    }
    string file = args[1];
    int arg;
    istringstream iss( args[2] );
    iss >> arg;
    string htarg = args[3];
    std::transform( htarg.begin(), htarg.end(), htarg.begin(), tolower );
    if( htarg.find("sc") == 0 )
        htarg = "sc_hash_table";
    else
        htarg = "lp_hash_table";
    cout << "Finding words in " << file << " with frequency >= " << arg << 
        " using " << htarg << "..." << endl;
    if( htarg == "sc_hash_table" )
        countWords<sc_hash_table>( file, arg );
    else
        countWords<lp_hash_table>( file, arg );
}
