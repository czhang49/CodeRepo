/**
 * @file maze.cpp
 * Definition of a maze class.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <random>
#include <map>


#include "maze.h"

namespace cs225
{

std::ostream& operator<<(std::ostream& os, direction dir)
{
    switch (dir)
    {
        case direction::RIGHT:
            return os << "RIGHT";
        case direction::DOWN:
            return os << "DOWN";
        case direction::LEFT:
            return os << "LEFT";
        case direction::UP:
            return os << "UP";
    }
}

maze::maze(uint64_t width, uint64_t height) : width_{width}, height_{height}
{
	if ((width*height) <= 0){
		std::cout << "The width and heigh of maze is not correct " <<'\n'<<std::endl;
	}
    	std::random_device rd;
    	std::mt19937_64 rng{rd()};
    	// use rng for your random numbers: it's a functor that returns you
    	// random numbers

    	/// @todo your code here
	dsets vtx_set;
	vtx_set.add_elements(width*height);
	
std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;	
	for(uint64_t i=0; i<width; i++){
		for (uint64_t j=0; j<height; j++){
			vertex curr = graph_.add_vertex();
			vtx_coords.push_back(curr);
			vtx_coords_reverse[curr] = std::make_pair(i,j);
		}
	}

std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
	uint64_t counter=0;
	while (counter != width*height-1){
		
		uint64_t x1 = rng()%width;
		uint64_t y1 = rng()%height;
		
		uint64_t code = rng()%4;
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"x1 is "<<x1<<"y1 is "<<y1<<"code is "<< code <<"\n"<<std::endl;	
		int64_t x2change=0;
		int64_t y2change=0;
		switch(code){
			case 0:
				x2change = 1;
				y2change = 0;
				break;
			case 1:
				x2change = 0;
				y2change = -1;
				break;
			case 2:
				x2change = -1;
				y2change = 0;
				break;
			case 3:
				x2change = 0;
				y2change = 1;
				break;
			default:
				std::cout<<"The switch code has a problem\n"<<std::endl;
				break;
		}
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;		
		if(!coord_valid(x1,x2change,y1,y2change))
			continue;

		uint64_t x2 = x1 + x2change;
		uint64_t y2 = y1 + y2change;
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
		if (!((vtx_set.find(y1*width+x1+1) == vtx_set.find(y2*width+x2+1)) && vtx_set.find(y1*width+x1+1)>0)){
			counter++;
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
			vertex v1 = vtx_coords[y1*width+x1];
			vertex v2 = vtx_coords[y2*width+x2];
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
			graph_.add_edge(v1,v2);	
			graph_.add_edge(v2,v1);	
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
			vtx_set.merge(y1*width+x1+1,y2*width+x2+1);
		}
//std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
	}
	
	
}


bool maze::coord_valid(uint64_t x1,int64_t x2change,uint64_t y1,int64_t y2change) const {

	if ((x1 == 0)&&(x2change ==-1))
		return false;
	if ((y1 == 0)&&(y2change ==-1))
		return false;
	if ((x1 == width_-1)&&(x2change ==1))
		return false;
	if ((y1 == height_-1)&&(y2change ==1))
		return false;

	return true;
}

bool maze::can_travel(uint64_t x, uint64_t y, direction dir) const
{
    	/// @todo your code here
	int64_t x2change=0;
	int64_t y2change=0;
	uint8_t code =0;
	if (dir == direction::RIGHT)
		code =0;
	if (dir == direction::DOWN)
		code =1;
	if (dir == direction::LEFT)
		code =2;
	if (dir == direction::UP)
		code =3;

	switch(code){
			case 0:
				x2change = 1;
				y2change = 0;
				break;
			case 1:
				x2change = 0;
				y2change = -1;
				break;
			case 2:
				x2change = -1;
				y2change = 0;
				break;
			case 3:
				x2change = 0;
				y2change = 1;
				break;
			default:
				std::cout<<"The switch code has a problem\n"<<std::endl;
				break;
	}

	if(!coord_valid(x,x2change,y,y2change))
		return false;

	uint64_t x2 = x + x2change;
	uint64_t y2 = y + y2change;

	vertex v1 = vtx_coords[y*width_+x];
	vertex v2 = vtx_coords[y2*width_+x2];

	return graph_.has_edge(v1,v2);
}

void maze::set_wall(uint64_t x, uint64_t y, direction dir, bool exists)
{
    	/// @todo your code here
    	/// DON'T THROW EXCEPTIONS FROM THIS FUNCTION
	int64_t x2change=0;
	int64_t y2change=0;
	uint8_t code =0;
	if (dir == direction::RIGHT)
		code =0;
	if (dir == direction::DOWN)
		code =1;
	if (dir == direction::LEFT)
		code =2;
	if (dir == direction::UP)
		code =3;

	switch(code){
			case 0:
				x2change = 1;
				y2change = 0;
				break;
			case 1:
				x2change = 0;
				y2change = -1;
				break;
			case 2:
				x2change = -1;
				y2change = 0;
				break;
			case 3:
				x2change = 0;
				y2change = 1;
				break;
			default:
				std::cout<<"The switch code has a problem\n"<<std::endl;
				break;
	}

	uint64_t x2 = x + x2change;
	uint64_t y2 = y + y2change;

	vertex v1 = vtx_coords[y*width_+x];
	vertex v2 = vtx_coords[y2*width_+x2];
	
	if (exists){
		graph_.remove_edge(v1,v2);	
		graph_.remove_edge(v2,v1);	
	}else {
		graph_.add_edge(v1,v2);	
		graph_.add_edge(v2,v1);	
	}
	
}

std::vector<direction> maze::solve()
{
    	/// @todo your code here
	std::vector<direction> directions;
	uint64_t max_lengthpt=0;
	uint64_t temporary=0;
	uint64_t max_length=0;
	for ( uint64_t i =0; i<width_; i++){
		temporary= tools::shortest_path_length(graph_, vtx_coords[0], vtx_coords[width_*(height_-1)+i]);
		if( temporary> max_length){
			max_lengthpt=i;
			max_length = temporary;
		}
	}
std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
	tools::shortest_path_length(graph_, vtx_coords[0], vtx_coords[width_*(height_-1)+max_lengthpt]);
std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
	vertex curr = vtx_coords[0];
	for ( const auto & v: graph_.adjacent(curr)){
		std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
		if (graph_.edge_label({curr,v}) == tools::edge_state::MINPATH){
			std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
			std::pair<uint64_t,uint64_t> curr_coord = vtx_coords_reverse[curr];
			std::pair<uint64_t,uint64_t> v_coord = vtx_coords_reverse[v];
			std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;
			if ((v_coord.first == curr_coord.first +1) &&  (v_coord.second == curr_coord.second))
				directions.push_back(direction::RIGHT);
			else if ((v_coord.first == curr_coord.first)  &&  (v_coord.second == curr_coord.second+1))
				directions.push_back(direction::DOWN);
			else if ((v_coord.first == curr_coord.first -1) &&  (v_coord.second == curr_coord.second))
				directions.push_back(direction::LEFT);
			else if ((v_coord.first == curr_coord.first)  &&  (v_coord.second == curr_coord.second-1))
				directions.push_back(direction::UP);
			else 
				std::cout<<"The label in MINPATH has a problem with the coordinate"<<std::endl;
		}
	}
std::cout<<"I'm at maze.cpp line "<<__LINE__<<"\n"<<std::endl;	
	return directions;
}

epng::png maze::draw() const
{
    	/// @todo your code here
	epng::png picture(width_*10+1,height_*10+1);

	picture(0,0) -> red = 0;
	picture(0,0) -> green = 0;
	picture(0,0) -> blue = 0;
	picture(0,0) -> alpha = 0;

	for (uint64_t i =10 ; i< width_*10+1;i ++){
		picture(i,0) -> red = 0;
		picture(i,0) -> green = 0;
		picture(i,0) -> blue = 0;
		picture(i,0) -> alpha = 0;
	}
	for (uint64_t j =0 ; j< height_*10+1;j ++){
		picture(0,j) -> red = 0;
		picture(0,j) -> green = 0;
		picture(0,j) -> blue = 0;
		picture(0,j) -> alpha = 0;
	}

	for (uint64_t j=0; j<height_-1; j++){
		for (uint64_t i=0; i<width_-1; i++){
			vertex curr = vtx_coords[j*width_+i];
			vertex right = 	vtx_coords[j*width_+i+1];	
			vertex down = 	vtx_coords[(j+1)*width_+i];
			if (!graph_.has_edge(curr,right)){
				for (uint64_t n=j*10;n<j*10+10;n++){
					picture((i+1)*10,n) -> red = 0;
					picture((i+1)*10,n) -> green = 0;
					picture((i+1)*10,n) -> blue = 0;
					picture((i+1)*10,n) -> alpha = 0;
				}
			}
			if (!graph_.has_edge(curr,down)){
				for (uint64_t m=i*10;m<i*10+10;m++){
					picture(m,(j+1)*10) -> red = 0;
					picture(m,(j+1)*10) -> green = 0;
					picture(m,(j+1)*10) -> blue = 0;
					picture(m,(j+1)*10) -> alpha = 0;
				}
			}
		}
	}
	for (uint64_t j=0; j<height_-1; j++){
			vertex curr = vtx_coords[j*width_+width_-1];
			vertex down = 	vtx_coords[(j+1)*width_+width_-1];
			if (!graph_.has_edge(curr,down)){
				for (uint64_t m=(width_-1)*10;m<(width_-1)*10+10;m++){
					picture(m,(j+1)*10) -> red = 0;
					picture(m,(j+1)*10) -> green = 0;
					picture(m,(j+1)*10) -> blue = 0;
					picture(m,(j+1)*10) -> alpha = 0;
				}
			}
		

	}
	for (uint64_t i=0; i<width_-1; i++){
			vertex curr = vtx_coords[(height_-1)*width_+i];
			vertex right = 	vtx_coords[(height_-1)*width_+i+1];
			if (!graph_.has_edge(curr,right)){
				for (uint64_t n=(height_-1)*10;n<(height_-1)*10+10;n++){
					picture((i+1)*10,n) -> red = 0;
					picture((i+1)*10,n) -> green = 0;
					picture((i+1)*10,n) -> blue = 0;
					picture((i+1)*10,n) -> alpha = 0;
				}
			}
		

	}

	return picture;
}

epng::png maze::draw_with_solution()
{
    auto result = draw();

    /// @todo your code here

    return result;
}
}
