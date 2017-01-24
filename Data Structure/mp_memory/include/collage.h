/**
 * @file collage.h 
 * @author Chen Zhang
 * @date Summer 2014
 */

#ifndef CS225_COLLAGE_H
#define CS225_COLLAGE_H

#include<iostream>
#include"scoped_ptr.h"
#include"scoped_array.h"
#include"epng.h"

namespace cs225
{
class collage
{
	public:
		collage(uint64_t size);
		collage(const collage& other);
		collage(collage && other);
		collage& operator= (collage rhs);
		~collage();
	
		void swap(collage& other);
		void layers(uint64_t max);
		uint64_t layers() const;
		uint64_t filled() const;
		void emplace_picture(const std::string& filename,uint64_t index, uint64_t x,uint64_t y);
		void change_layer(uint64_t src, uint64_t dest);
		void position(uint64_t index, uint64_t x, uint64_t y);
		void erase(uint64_t index);
		const epng::png* at(uint64_t index) const;
		epng::png* at(uint64_t index);
		epng::png draw() const;
	
	private:
		cs225::scoped_array< epng::png*  >	array_ptr;
		uint64_t* x_;
		uint64_t* y_;	
};
}

#endif
