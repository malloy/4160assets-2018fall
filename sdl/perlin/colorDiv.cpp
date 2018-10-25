#include "colorDiv.h"

//Color Div Constructors - With and without name string
colorDiv::colorDiv(double & div, SDL_Color & col, std::string name):
 	color(col), division(div), name(name){;}

colorDiv::colorDiv(double & div, SDL_Color & col):
 	color(col), division(div), name("none"){;}

//Getters, used by colorPicker.cpp
SDL_Color colorDiv::getColor() const{
	return color;
}

double colorDiv::getDiv() const{
	return division;
}

std::string colorDiv::getName() const{
	return name;
}

