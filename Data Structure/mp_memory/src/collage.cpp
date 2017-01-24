/*
 * @file Collage.cpp
 * @author Chen Zhang
 * @date Summer 2014
 */

#include <iostream>
#include "collage.h"
#include "scoped_ptr.h"
#include "scoped_array.h"
#include "epng.h"

namespace cs225
{
cs225::collage::collage(uint64_t size)
{	
	// the array_ptr is already a nullptr with size_=0 at the declaration
	 cs225::scoped_array< epng::png* > temp{size};
	 array_ptr=temp;

	x_=new uint64_t[size];
	y_=new uint64_t[size];
	for (uint64_t i=0;i<size;i++)
	{
		x_[i]=0;
		y_[i]=0;
		array_ptr[i]=new epng::png;
	}
//	array_ptr=temp;

}

cs225::collage::collage(const collage& other)
{
	
	// the array_ptr is already a nullptr with size_=0 at the declaration
	std::cout<<"const reference constructor is used"<<std::endl;
	array_ptr=other.array_ptr;
	for (uint64_t i=0;i<other.array_ptr.size();i++)
	{
		if ( other.array_ptr.at(i)!=nullptr)
		{std::cout<<i<<std::endl;
		//epng::png temptemp=(*other.array_ptr.at(i));
		array_ptr[i]=new epng::png{(*other.array_ptr.at(i))};
		//(*array_ptr[i])=temptemp;
		}
	}
		
	x_=new uint64_t[other.array_ptr.size()];
	y_=new uint64_t[other.array_ptr.size()];
	for (uint64_t i=0;i<other.array_ptr.size();i++)
	{
		x_[i]=other.x_[i];
		y_[i]=other.y_[i];
	}
}

cs225::collage::collage(collage && other)
{
	
	// the array_ptr is already a nullptr with size_=0 at the declaration
	std::cout<<"Copy constructor used"<<std::endl;
	swap(other);
}

cs225::collage::~collage()
{
	std::cout<<"At the collage destructor layers is "<<layers()<<"Filled is "<<filled()<<std::endl;
	for (uint64_t i=0;i<array_ptr.size();i++)
	{	if(array_ptr[i]!=nullptr)
		{
		std::cout<<"At the collage destructor Line:"<<__LINE__<<"png number is :"<<i<<std::endl;
		delete array_ptr.at(i);
		array_ptr.at(i)=nullptr;
		}
	}	
	array_ptr.clear();
	delete[] x_;
	delete[] y_;
	x_=nullptr;
	y_=nullptr;

	std::cout<<" at the final line of collage destructor"<<std::endl;
}

collage& cs225::collage::operator=(collage rhs)
{
	swap(rhs);
	return(*this);
}

void cs225::collage::swap(collage& other)
{
	array_ptr.swap(other.array_ptr);
	std::swap(x_,other.x_);
	std::swap(y_,other.y_);
}

void cs225::collage::layers(uint64_t max)
{
	array_ptr.resize(max);
	uint64_t* temp_x=new uint64_t[max];
	uint64_t* temp_y=new uint64_t[max];
	
	for (uint64_t i=0;i<max;i++)
	{
		temp_x[i]=0;
		temp_y[i]=0;
	}

	if(max<=array_ptr.size())
	{
		for (uint64_t i=0;i<max;i++)
		{
			temp_x[i]=x_[i];
			temp_y[i]=y_[i];
		}
	}
	else
	{
		for (uint64_t i=0; i<array_ptr.size();i++)
		{
			temp_x[i]=x_[i];
			temp_y[i]=y_[i];
		}
	}

	std::swap(x_,temp_x);
	std::swap(y_,temp_y);
}

uint64_t cs225::collage::layers() const
{
	return array_ptr.size();
}

uint64_t cs225::collage::filled() const
{
	uint64_t counter=0;
	for (uint64_t i=0;i<array_ptr.size();i++)
	{
		if (array_ptr.at(i)!=nullptr)
			counter=counter+1;
	}

	return counter;
}

void cs225::collage::emplace_picture(const std::string& filename, uint64_t index,uint64_t x,uint64_t y)
{
	
	if (array_ptr.size()<=index)
	{
		throw std::out_of_range("This out of range happens at collage.emplace_picture()");
	}
	else 
	{
		x_[index]=x;
		y_[index]=y;
		(*array_ptr[index]).load(filename);
		
	}
}

void cs225::collage::change_layer(uint64_t src, uint64_t dest)
{
	if (array_ptr.size()<=src || array_ptr.size()<=dest)
	{
		throw std::out_of_range("This out of range happens at collage.change_layers()");
	}
	else
	{
		if (array_ptr.at(dest)!=nullptr)
		{
			delete array_ptr.at(dest);
			array_ptr.at(dest)=array_ptr.at(src);
			array_ptr.at(src)=nullptr;
			x_[dest]=x_[src];
			x_[src]=0;
			y_[dest]=y_[src];
			y_[src]=0;
		}
		else
		{
			array_ptr.at(dest)=array_ptr.at(src);
			array_ptr.at(src)=nullptr;

			x_[dest]=x_[src];
			x_[src]=0;
			y_[dest]=y_[src];
			y_[src]=0;
		}
	}

}

void cs225::collage::position(uint64_t index, uint64_t x,uint64_t y)
{
	if (array_ptr.size()<=index)
	{
		throw std::out_of_range("This out of range happends at collage.position()");
	}
	else if (array_ptr.at(index)==nullptr)
	{
		throw std::invalid_argument("This invalid argument happens at collage.position()");
	}
	else
	{
		x_[index]=x;
		y_[index]=y;
	}

}

void cs225::collage::erase(uint64_t index)
{
	if (array_ptr.size()<=index)
	{
		throw std::out_of_range("This out of range happens at collage.erase()");
	}
	else
	{
		delete array_ptr.at(index);
		array_ptr.at(index)=nullptr;
		x_[index]=0;
		y_[index]=0;
	}


}

const epng::png* cs225::collage::at(uint64_t index) const
{
	if (array_ptr.size()<=index)
	{
		throw std::out_of_range("This out of range happens at collage.at()");
	}
	else 
	{
		return array_ptr.at(index);
	}

}

epng::png* cs225::collage::at(uint64_t index) 
{
	return array_ptr.at(index);
}

epng::png cs225::collage::draw() const
{
	uint64_t width=0;
	uint64_t height=0;
	
	for (uint64_t i=0;i<array_ptr.size();i++)
	{	
		if (array_ptr[i]!=nullptr)
		{
		if (width<(x_[i]+array_ptr[i]->width()))
			width=(x_[i]+array_ptr[i]->width());
		if (height<(y_[i]+array_ptr[i]->height()))
			height=(y_[i]+array_ptr[i]->height());
		}
	}	
	//std::cout<<width<<height<<std::endl;
	epng::png image(width,height);
	
	for (uint64_t count_png=0;count_png<array_ptr.size();count_png++)
	{	//std::cout<<count_png<<std::endl;
		//std::cout<<array_ptr[count_png]->width()<<std::endl;
		//std::cout<<array_ptr[count_png]->height()<<std::endl;
		if( array_ptr[count_png]!=nullptr)
		{
		for (uint64_t count_width=0;count_width<array_ptr[count_png]->width();count_width++)
		{	//std::cout<<count_width<<std::endl;
			for (uint64_t count_height=0;count_height<array_ptr[count_png]->height();count_height++)
			{	//std::cout<<count_width<<count_height<<std::endl;
				image(count_width+x_[count_png],count_height+y_[count_png])->green=((*array_ptr[count_png])(count_width,count_height))->green;
	
				image(count_width+x_[count_png],count_height+y_[count_png])->red=((*array_ptr[count_png])(count_width,count_height))->red;
			
				image(count_width+x_[count_png],count_height+y_[count_png])->blue=((*array_ptr[count_png])(count_width,count_height))->blue;
			
				image(count_width+x_[count_png],count_height+y_[count_png])->alpha=((*array_ptr[count_png])(count_width,count_height))->alpha;
			}
			
		}
		}
	}

	return image;
}

}







