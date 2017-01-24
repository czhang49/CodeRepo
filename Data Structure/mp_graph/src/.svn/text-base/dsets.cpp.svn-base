#include "dsets.h"

void dsets::add_elements(uint64_t num){

	// each element is initilized to -1 at the beginning
	for ( uint64_t i = 0 ; i< num; i++){
		arr_.push_back((-1));
//cout <<"I'm at dsets.cpp line "<< __LINE__<<"index is :"<<i<<"and value is :"<<arr_[i]<< "\n"<<endl;
	}

}

uint64_t dsets::find (uint64_t elem){

	// elem is the element number, but what is needed is the index
	auto index = elem-1;
//std::cout<<"I'm at dsets.cpp line "<<__LINE__<<"\n"<<std::endl;
	// this is smaller than 0
	if ( arr_[index] < 0){
//std::cout<<"I'm at dsets.cpp line "<<__LINE__<<"\n"<<std::endl;
		return index;
	}
//std::cout<<"I'm at dsets.cpp line "<<__LINE__<<"\n"<<std::endl;
	return arr_[index]=find(arr_[index]+1);

}

void dsets::merge(uint64_t a, uint64_t b){

	// seta and setb are index, but a and b are element numbers

	auto seta = find(a);
	auto setb = find(b);

	// this line is crucial. If two are already in one set, try to merge using the same method will cause problems
	if (seta == setb && (seta>0)){
		return ;
	}

	if (arr_[seta] < arr_[setb]){
		// don't mess up this order, otherwise it's wrong
		arr_[seta] = arr_[seta] + arr_[setb];
		arr_[setb] = seta;
	} else {
		arr_[setb] = arr_[seta] + arr_[setb];	
		arr_[seta] = setb;
	}

}
