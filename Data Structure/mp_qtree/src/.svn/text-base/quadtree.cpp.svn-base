/**
 * @file quadtree.cpp
 * quadtree class implementation.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#include "quadtree.h"

namespace cs225
{

// default create node is to create a rigba pixel element with default values and four null pointer
quadtree::node::node(){

  northwest=nullptr;
  northeast=nullptr;
  southwest=nullptr;
  southeast=nullptr;
  element.red=255;
  element.green=255;
  element.blue=255;
  element.alpha=255;

}

// copy create node is to create a node with target element rigba pixel values and four null pointers.
quadtree::node::node(const node & node){
  
  northwest=nullptr;
  northeast=nullptr;
  southwest=nullptr;
  southeast=nullptr;

  element.red=node.element.red;
  element.green=node.element.green;
  element.blue=node.element.blue;
  element.alpha=node.element.alpha;

}

quadtree::quadtree(){
 
  root_=nullptr;  
  resol=0;
}


quadtree::quadtree(quadtree && tree){

  root_=nullptr;
  resol=0;  

  swap(tree);

}


quadtree::quadtree(const quadtree& tree){

  // make unique is to create a node with the d-referenced given root ptr
  root_ = std::make_unique<node> (*(tree.get_root_only()));
  resol = tree.get_resol();

  create_child(root_->northwest,tree.get_root_only()->northwest);
  create_child(root_->northeast,tree.get_root_only()->northeast);
  create_child(root_->southwest,tree.get_root_only()->southwest);
  create_child(root_->southeast,tree.get_root_only()->southeast);

}


uint64_t quadtree::get_resol() const{

	return resol;
}

quadtree::quadtree(const epng::png &source, uint64_t resolution){

  build_tree(source, resolution);

}


void quadtree::build_tree(const epng::png& source, uint64_t resolution){

  root_.reset(nullptr);
  root_=std::make_unique<node> ();
  resol=resolution;

  colorfy_element(root_->element, source, 1, 1, resolution, resolution); 
  create_child(root_->northwest,source, 1, 1, resolution/2, resolution/2);
  create_child(root_->northeast,source, resolution/2+1, 1, resolution, resolution/2);
  create_child(root_->southwest,source, 1, resolution/2+1,  resolution/2, resolution);
  create_child(root_->southeast,source, resolution/2+1, resolution/2+1,  resolution, resolution);

}

void quadtree::colorfy_element(epng::rgba_pixel& element, const epng::png& source, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy){

  element.red=0;
  element.green=0;
  element.blue=0;
  element.alpha=0;

  uint64_t i,j;
  uint64_t counter=0;

  for(i=startx-1;i<endx;i++){
    for (j=starty-1;j<endy;j++){
  
	element.red=element.red+source(i,j)->red;
  	element.green=element.green+source(i,j)->green;
  	element.blue=element.blue+source(i,j)->blue;
  	element.alpha=element.alpha+source(i,j)->alpha;
  	counter++;
    }
  } 
  
  element.red=(int) element.red/counter;
  element.green=(int) element.green/counter;
  element.blue=(int) element.blue/counter;
  element.alpha=(int) element.alpha/counter;

}

void quadtree::create_child(std::unique_ptr<node>& target_ptr, const std::unique_ptr<node>& given_ptr){

  if (given_ptr==nullptr)
    return;

  target_ptr=std::make_unique<node> (*given_ptr);

  create_child(target_ptr->northwest,given_ptr->northwest);
  create_child(target_ptr->northeast,given_ptr->northeast);
  create_child(target_ptr->southwest,given_ptr->southwest);
  create_child(target_ptr->southeast,given_ptr->southeast);

}

void quadtree::create_child(std::unique_ptr<node>& target_ptr,const epng::png& source, uint64_t startx, uint64_t starty, uint64_t endx, uint64_t endy){

  if (startx==endx){
    if(starty!=endy)
       throw std::invalid_argument( "startx , starty, endx, endy needs to point to the same pixel" );
    else{
       
       target_ptr=std::make_unique<node>();
       colorfy_element(target_ptr->element, source, startx, starty, endx, endy); 
       return;
    }
  }
  target_ptr= std::make_unique<node>();
  colorfy_element(target_ptr->element, source, startx, starty, endx, endy); 

  uint64_t increment_x = (endx-startx+1)/2;
  uint64_t increment_y = (endy-starty+1)/2;

  if (increment_x!=increment_y)
    throw std::invalid_argument( "The increment X is not equal to the increment Y" );

  uint64_t midx_left=startx+increment_x-1;
  uint64_t midx_right=startx+increment_x;
  uint64_t midy_up=starty+increment_y-1;
  uint64_t midy_down=starty+increment_y;

  create_child(target_ptr->northwest,source, startx, starty, midx_left, midy_up);
  create_child(target_ptr->northeast,source, midx_right, starty, endx, midy_up);
  create_child(target_ptr->southwest,source, startx, midy_down,  midx_left, endy);
  create_child(target_ptr->southeast,source, midx_right, midy_down,  endx, endy);

}


quadtree& quadtree::operator=(quadtree tree){

  swap(tree);
  return (*this);

} 

void quadtree::swap( quadtree& tree){

  std::unique_ptr<node> temp;
  temp=std::move(root_);
  root_=std::move(tree.get_root());
  tree.get_root() = std::move(temp);

}

std::unique_ptr<quadtree::node>& quadtree::get_root(){

  return root_;

}

const std::unique_ptr<quadtree::node>& quadtree::get_root_only() const{

  return root_;

}

const epng::rgba_pixel& quadtree::operator()(uint64_t x, uint64_t y) const{

  if (x>resol || y> resol)
    throw std::out_of_range( "The target x, y is out of range" );

  
  return find_rgba_pixel(x,y,resol/2, resol/2, resol, root_);

}


const epng::rgba_pixel& quadtree::find_rgba_pixel(uint64_t x,uint64_t y,uint64_t left_upX,uint64_t left_upY, uint64_t curr_range, const std::unique_ptr<node>& ptr) const{

   //   std::cout<<" X is "<<x<<" Y is "<<y<<" left_upX is "<<left_upX<<" left_upY is "<<left_upY<<"resolution is "<<resol<<"current range is "<<curr_range<<std::endl;

  if (curr_range==1)
    return ptr->element;
  if (curr_range==2){
    if (x==left_upX && y==left_upY){
      if (ptr->northwest != nullptr)
        return find_rgba_pixel(x,y,x,y, 1, ptr->northwest);
      else 
        return ptr->element;
    }
    else if (x==left_upX+1 && y==left_upY){
      if (ptr->northeast != nullptr)
        return find_rgba_pixel(x,y,x+1,y, 1, ptr->northeast);
      else 
        return ptr->element;
    }
    else if (x==left_upX && y==left_upY+1){
      if (ptr->southwest != nullptr)
        return find_rgba_pixel(x,y,x,y+1, 1, ptr->southwest);
      else 
        return ptr->element;
    }
    else if (x==left_upX+1 && y==left_upY+1){
      if (ptr->southeast != nullptr)
        return find_rgba_pixel(x,y,x+1,y+1, 1, ptr->southeast);
      else 
        return ptr->element;
    }
    else{
      
      std::cout<<" X is "<<x<<" Y is "<<y<<" left_upX is "<<left_upX<<" left_upY is "<<left_upY<<"resolution is "<<resol<<std::endl;
      throw std::out_of_range( "when curr_range is 2, there is something wrong" );
    }
  }
  

  uint64_t diff= curr_range/4;  


  if (x<=left_upX){
    if (y<=left_upY){
      if (ptr->northwest != nullptr)
        return find_rgba_pixel(x,y,left_upX-diff,left_upY-diff,curr_range/2, ptr->northwest);
      else 
        return ptr->element;
    }
    else if (y>left_upY){
      if (ptr->southwest != nullptr)
        return find_rgba_pixel(x,y,left_upX-diff,left_upY+diff,curr_range/2, ptr->southwest);
      else 
        return ptr->element;
    }
  }
  else if (x>left_upX){
    if (y<=left_upY){
      if (ptr->northeast != nullptr)
        return find_rgba_pixel(x,y,left_upX+diff,left_upY-diff,curr_range/2, ptr->northeast);
      else 
        return ptr->element;
    }
    else if (y>left_upY){
      if (ptr->southeast != nullptr)
        return find_rgba_pixel(x,y,left_upX+diff,left_upY+diff,curr_range/2, ptr->southeast);
      else 
        return ptr->element;
    }
  }
  else 
      throw std::out_of_range( "The find rigba_pixel is fucked up" );

}


epng::png quadtree::decompress() const{

  if (root_ == nullptr)
    std::runtime_error("The tree that you want a png object from is empty");

  epng::png tobecreated(resol,resol);

  uint64_t i,j;
  for (i=0;i<resol;i++){
    for (j=0;j<resol;j++){
      tobecreated(i,j)->red=(*this)(i+1,j+1).red;
      tobecreated(i,j)->green=(*this)(i+1,j+1).green;
      tobecreated(i,j)->blue=(*this)(i+1,j+1).blue;
      tobecreated(i,j)->alpha=(*this)(i+1,j+1).alpha;
  //std::cout<<"i is "<<i<<"j is "<<j<<std::endl;
    }
  }

  return tobecreated;
}

void quadtree::rotate_clockwise(){

	switch_pointer(root_);

}


void quadtree::switch_pointer(std::unique_ptr<node>& ptr){

  if (ptr==nullptr)
    return;
  
  ptr->northwest.swap(ptr->southwest);
  ptr->northeast.swap(ptr->southwest);
  ptr->southeast.swap(ptr->southwest);
 
  switch_pointer(ptr->northwest);
  switch_pointer(ptr->northeast);
  switch_pointer(ptr->southwest);
  switch_pointer(ptr->southeast);

}

// This is the name space bracket
}
