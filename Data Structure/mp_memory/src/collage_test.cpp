/**
 * @file collage_test.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "epng.h"
#include "collage.h"

uint8_t clamp(int val)
{
    return std::max(0, std::min(255, val));
}

int main()
{
    using namespace cs225;
    using namespace epng;

    scoped_ptr<collage> set{new collage{7}};
    std::cout<<set->layers()<<std::endl;
	set->emplace_picture("in_01.png", 6, 0, 0);
    set->emplace_picture("in_02.png", 1, 60, 60);
    set->emplace_picture("in_03.png", 2, 150, 0);
    set->emplace_picture("in_04.png", 3, 30, 90);
    set->emplace_picture("in_05.png", 4, 160, 200);
    auto result = set->draw();
	std::cout<<"At main function"<<__LINE__<<std::endl;
    result.save("scene.png");

    set->change_layer(1, 5);
    //std::cout<<"At main function"<<__LINE__<<std::endl;
	//std::cout<<set->layers()<<set->filled()<<std::endl;
	result = set->draw();
	//std::cout<<"At main function"<<__LINE__<<std::endl;
    result.save("scene2.png");

    set->position(5, 60, 160);
    result = set->draw();
    result.save("scene3.png");

    set->erase(3);
    result = set->draw();
    result.save("scene4.png");

    set->at(2)->load("in_04.png");
    result = set->draw();
    result.save("scene5.png");

    scoped_ptr<collage> sc{new collage{*set}};
    sc->position(4, 230, 200);
    result = set->draw();
    result.save("scene6.png"); // scene 5 and scene 6 should be the same
    result = sc->draw();
    result.save("scene7.png");

    set.clear();
    set = scoped_ptr<collage>{new collage{5}};
    *set = *sc;
    result = set->draw();
    result.save("scene8.png"); // scene 7 and scene 8 should be the same.
	std::cout<<"At Main "<<__LINE__<<std::endl;
    return 0;
}
