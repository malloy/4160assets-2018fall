#ifndef COLORDIV_H
#define COLORDIV_H
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>

//shorthand for "division"
class colorDiv{
	public:
		colorDiv(double & div, SDL_Color & col, std::string name);
		colorDiv(double & div, SDL_Color & col);

		SDL_Color getColor() const;
		std::string getName() const;
		double getDiv() const;
	private:
		SDL_Color color;
		double division;
		std::string name;
	};
#endif
