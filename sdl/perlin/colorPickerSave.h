#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>

//"div" is shorthand for "division"

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

class colorPicker{
public:
	colorPicker();
	void addDiv(double div, SDL_Color col, std::string name);
	void addDiv(double div, SDL_Color col);
	void removeDivs();
	SDL_Color getColor(double val) const; // pass in a noise val and get correct color
	colorDiv getDiv(int index) const;
	int getColorCount() const;
private:
	std::vector<colorDiv> divs;
	int colorCount;
};

std::ostream & operator<<( std::ostream & cout, const colorPicker &colPic);
