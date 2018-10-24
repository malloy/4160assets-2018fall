#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "colorDiv.h"

class colorPicker{
public:
	colorPicker();
	void addDiv(double div, SDL_Color col, std::string name);
	void addDiv(double div, SDL_Color col);
	void removeDivs();
	// pass in a noise val and get correct color
	SDL_Color getColor(double val) const; 	colorDiv getDiv(int index) const;
	int getColorCount() const;
private:
	std::vector<colorDiv> divs;
	int colorCount;
};

std::ostream & operator<<( std::ostream & cout, const colorPicker &colPic);
