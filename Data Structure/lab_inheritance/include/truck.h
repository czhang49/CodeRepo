/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#ifndef TRUCK_H_
#define TRUCK_H_

#include "circle.h"
#include "drawable.h"
#include "rectangle.h"
#include "vector2.h"
#include "shape.h"

class Truck : public Drawable
{
  private:
    Vector2 center_;
    Circle** wheels;
    Rectangle* trailer;
    Rectangle* cabin;
    Rectangle* window;
    Rectangle* engine;

    void copy(const Truck& other);
    void clear();

  public:
    Truck(const Vector2& center);
    Truck(const Truck& other);
    Truck(Truck&& other);
    ~Truck();
    Truck& operator=(Truck rhs);
    void swap(Truck& other);
    Vector2 center() const;
    void set_center(const Vector2& center);
	void draw(epng::png& canvas) const override;
};

#endif // TRUCK_H_
