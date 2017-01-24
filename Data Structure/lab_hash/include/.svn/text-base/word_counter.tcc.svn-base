/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class HT>
WordFreq<HT>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}



/**
 * @todo Implement this function.
 * @see char_counter.cpp if you're having trouble.
 */
template <template <class K, class V> class HT>
vector<pair<string, int>> WordFreq<HT>::getWords(int threshold) const
{
    	vector< pair<string, int> > ret;
	HT<string,int> hashtable(8192);	
	TextFile infile(filename);

	while (infile.good()){
	
		hashtable[infile.getNextWord()]++;
	}

	cout<<"I'm here at word_counter.tcc line "<<__LINE__<<"\n"<<endl;
	for ( const auto & p : hashtable){

		if(p.second>=threshold){
			ret.push_back(p);
			cout<<"I'm here at word_counter.tcc line "<<__LINE__<<"\n"<<endl;
		}
	}
cout<<"I'm here at word_counter.tcc line "<<__LINE__<<" the size of the string is "<<ret.size()<<"\n"<<endl;
for( unsigned int i = 0; i < ret.size(); i++ )
        cout << ret[i].first << " " << ret[i].second << endl;

cout<<"I'm here at word_counter.tcc line "<<__LINE__<<"\n"<<endl;
    	return ret;
}
