#include "colorPicker.h"
#include "colorDiv.h"

//Default Constructor
colorPicker::colorPicker(): divs({}), colorCount(0) {;}

/*REQUIREMENT: divisions must be added to colorPicker
	in increasing order

	Loops through divs vector in ascending order until a division is found with
	a higher value than val. That division color is then returned.

	The use of "val*scale - 100" was an attempt at introducing slight color
	variations to make the image more interesting. Experimental, and any changes
	so far have resulted in unexpected colors.
*/
SDL_Color colorPicker::getColor(double val) const {
 	double scale = 100.0;
	for(colorDiv i : divs){
		if(val < i.getDiv()){

			SDL_Color col = i.getColor();
			col.r = i.getColor().r + val*scale - 95;
			col.g = i.getColor().g + val*scale - 105;
			col.b = i.getColor().b + val*scale - 100;
			return col;
		}
	}
	//If val is not less than any of the divisions
	return (divs.at(divs.size() - 1)).getColor();
}

/*
	A division can be considered a color range from double value from the
	division added directly before, to the double val of the current division.
	Separate nameless version added for use in creating color list.
*/
void colorPicker::addDiv(double div, SDL_Color col, std::string name){
	colorDiv newDiv(div, col, name);
	divs.emplace_back(newDiv);
	colorCount++;
}

void colorPicker::addDiv(double div, SDL_Color col){
	divs.emplace_back(div, col);
	colorCount++;
}

//Clears divs vector
void colorPicker::removeDivs(){
	divs.clear();
}

//Getters
colorDiv colorPicker::getDiv(int index) const{
	return divs.at(index);
}

int colorPicker::getColorCount() const{
	return colorCount;
}

//Overloaded Output operator
std::ostream & operator<<( std::ostream & cout, const colorPicker &colPic){
	 SDL_Color color;
	std::string colorName;

	 cout <<  "ColorPicker's color palette contains: " << std::endl;
	 for(int i = 0; i < colPic.getColorCount(); i++){
 		color = (colPic.getDiv(i)).getColor();
		colorName = colPic.getDiv(i).getName();
		if(colorName != "none"){
			cout << colorName << ": " 
			<< static_cast<int>(color.r) << "," 
			<< static_cast<int>(color.g) << ","
			<< static_cast<int>(color.b) << std::endl;
		  }
 	}
    return cout;
  }
