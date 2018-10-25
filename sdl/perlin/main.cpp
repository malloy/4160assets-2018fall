#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include "frameGenerator.h"
#include "colorPicker.h"
#include "colorDiv.h"
#include "PerlinNoise.h"

const std::string TITLE = "Fantasy Map by Mitchell Bowser";
const std::string NAME = "mbowser";

const int WIDTH = 1024;
const int HEIGHT = 768;
int seed = time(NULL) % 10000;
void render(SDL_Renderer* renderer, PerlinNoise& perlin,
				colorPicker& palette, double, double);//prototype
void loadColors(colorPicker& palette);

/*
Modified from the drawCircle method provided by Dr. Malloy.
Fills in everything in the window except for the specified circle.
*/
void drawCircle(SDL_Renderer* renderer,
		 SDL_Point center, int radiusX, int radiusY, SDL_Color color) {
			 SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			 for (int w = 0; w < radiusX * 2; w++) {
				 for (int h = 0; h < radiusY * 2; h++) {
					 int dx = radiusX - w; // horizontal offset
					 int dy = radiusY - h; // vertical offset
					 if ((dx*dx + dy*dy) >= (radiusX * radiusX)) {
						 SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
					 }
				 } //end height for loop
			 } //end width for loop
		 }

//Write name function provided by Dr. Malloy
void writeName(SDL_Renderer* renderer) {
	TTF_Init();
	TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
	if (font == NULL) {
		throw std::string("error: font not found");
	}
	SDL_Color textColor = {210, 220, 210, 0};
	SDL_Surface* surface =
	TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	int textWidth = surface->w;
	int textHeight = surface->h;
	SDL_FreeSurface(surface);
	SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
}


int main(void) {
	try {
		if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
			std::cout << "Failed to initialize SDL2" << std::endl;
			return EXIT_FAILURE;
		}
		SDL_Window* window = SDL_CreateWindow(
			TITLE.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_SHOWN
		);
		// Apparently we can't use hardware acceleration with
		// SDL_GetWindowSurface
		SDL_Renderer* renderer = SDL_CreateRenderer(
			window, -1, SDL_RENDERER_SOFTWARE
		);

		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
		SDL_RenderClear(renderer);

		/*
		Init colorpicker with all color divisions, to be accessed using noise
		These divisions are entirely subjective, and chosen by trial and error
		to find the desired ratio of land to water.
		*/
		colorPicker palette;
		loadColors(palette);
		std::cout << palette << std::endl; //print loaded colors

		//Initialize perlin noise - please see README for Perlin citation
		seed = 5509; //Remove to generate new image each time based on timestamp
		PerlinNoise perlin(seed); //Seed to generate the same image each time
		std::cout << "seed was: " << seed << std::endl;


		double userXOffset = 0;
		double userYOffset = 0;

		//Generate first image. Further images generated with arrow keys and space
		render(renderer, perlin, palette, userXOffset, userYOffset);
		FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
		frameGen.makeFrame();

		//Added scancodes to allow user to pan map with arrow keys
		SDL_Event event;
		const Uint8* keystate;
		while ( true ) {
			keystate = SDL_GetKeyboardState(0);
			if (keystate[SDL_SCANCODE_ESCAPE]) { break; }

			if (keystate[SDL_SCANCODE_SPACE]){seed++;
				render(renderer, perlin, palette, userXOffset, userYOffset);
				std::cout << "seed was: " << seed << std::endl;
			}

			if (keystate[SDL_SCANCODE_UP]) {userYOffset += 5;
				render(renderer, perlin, palette, userXOffset, userYOffset);}

			if (keystate[SDL_SCANCODE_DOWN]) {userYOffset -= 5;
					render(renderer, perlin, palette, userXOffset, userYOffset); }

			if (keystate[SDL_SCANCODE_RIGHT]) {userXOffset -= 5;
					render(renderer, perlin, palette, userXOffset, userYOffset);}

			if (keystate[SDL_SCANCODE_LEFT]) {userXOffset += 5;
					render(renderer, perlin, palette, userXOffset, userYOffset);}

			if (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
							break;
						}
			}
		} //end event loop

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		}
		catch (const std::string& msg) { std::cout << msg << std::endl; }
		catch (...) {
				std::cout << "Oops, someone threw an exception!" << std::endl;
		}

		return EXIT_SUCCESS;
}

/*
Load colorpicker palette with all color divisions to be accessed using noise.
These divisions are entirely subjective, and chosen by trial and error
to find the desired ratio of land to water.
*/
void loadColors(colorPicker& palette){
	//List of Colors used
	 SDL_Color waterDeep =		{130, 167, 196, 255};
	 SDL_Color water =			{155, 191, 226, 255};
	 SDL_Color waterShallow =	{170, 206, 232, 255};
	 SDL_Color sand = 			{245, 196, 126, 255};
	 SDL_Color grassLow	=		{160, 180, 110, 255};
	 SDL_Color grass = 			{170, 196, 126, 255};
	 SDL_Color grassHigh = 		{180, 210, 140, 255};
	 SDL_Color dirt = 			{165, 153, 126, 255};
	 SDL_Color ice =				{220, 210, 230, 255};
	 SDL_Color snow =				{230, 230, 245, 255};

	/*Divisions between [0,1] to map with scaled noise, must be ascending.
	  The constructor is overloaded, and the names only need to be included for the
	  first use of each color, or else they will be listed twice when using the
	  overloaded output operator on palette.
	*/
	palette.addDiv(0.36, waterDeep, "waterDeep");
	palette.addDiv(0.37, water, "water");
	palette.addDiv(0.38, waterDeep);
	palette.addDiv(0.39, water);
	palette.addDiv(0.4, waterDeep);
	palette.addDiv(0.54, water);
	palette.addDiv(0.6, waterShallow, "waterShallow");
	palette.addDiv(0.62, sand, "sand");
	palette.addDiv(0.64, grassLow, "grassLow");
	palette.addDiv(0.67, grass, "grass");
	palette.addDiv(0.68, grassLow);
	palette.addDiv(0.75, grass);
	palette.addDiv(0.71, grassLow);
	palette.addDiv(0.75, grass);
	palette.addDiv(0.85, grassHigh, "grassHigh");
	palette.addDiv(0.95, dirt, "dirt");
	palette.addDiv(0.97, ice, "ice");
	palette.addDiv(1.0, snow, "snow");
}

//Render function that is called on execution, and with each user input
void render(SDL_Renderer* renderer, PerlinNoise& perlin, colorPicker& palette, double userXOffset, double userYOffset){

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear(renderer);

	perlin.seed(seed); // TAKE OUT

	//Init perlin
	double val = 0; 	//holds value returned by perlin noise
	double maxVal = 0; //Initial max
	double minVal = 100; //Initial min
	SDL_Color color;
	double i = 0; //height pixel counter
	double j = 0; //width pixel counter

	/*Noise scales for each layer of noise
	  High numbers zoom out on the noise, creating more random variations.
	*/
	double nScale1 = 16;
	double nScale2 = 6;
	double nScale3 = 0.2;
	double nScale4 = 50;

	/*Noise ratios for each layer of noise
		Used when layering the noise. To give a layer more influence, increase
		these values.
	*/
	double nRatio1 = 0.2;
	double nRatio2 = 0.8;
	double nRatio3 = 1.4;
	double nRatio4 = 0.04;

	/*
		Loop through the entire image twice. The first loop finds the max and min
		values returned by the perlin noise, the second scales the noise and uses
		it to get a color from palette for the current pixel.
	*/
	for(int k = 0; k < 2; k++){
		for( i = 0; i < HEIGHT; i++){
			for( j = 0; j < WIDTH; j++){
				/*Calculate pixel's color using scaled perlin noise
				  i and j divided by image dimensions at the recommendation of the
				  noise library author. */
				double ii = (i + userYOffset) / HEIGHT; //scaled for use with perlin
				double jj = (j + userXOffset) / WIDTH; //scaled for use with perlin

				//The numbers at the end of perlin calls are arbitrary z values
				val = nRatio1 * perlin.noise(nScale1 * jj, nScale1 * ii, 0.8);
				val+= nRatio2 * perlin.noise(nScale2 * jj, nScale2 * ii, 0.6);
				val+= nRatio3 * perlin.noise(nScale3 * jj, nScale3 * ii, 0.2);
				val+= nRatio4 * perlin.noise(nScale4 * jj, nScale4 * ii, 0.1);


				if(k == 0){ //Find min and max
					if(val > maxVal)
						maxVal = val;
					if(val < minVal)
						minVal = val;
				}
				else{ //Scale layered noise to [0,1] and get color for current pixel
					val = (val - minVal) / (maxVal - minVal);
					color = palette.getColor(val);
				}
				//Draw color to window
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
				SDL_RenderDrawPoint(renderer, j, i);
			}
		}
	}
	//Draw Map Gridline every 'gridSize' number of pixels
	SDL_SetRenderDrawColor(renderer, 150, 150, 150, 10);
	int gridSize = 100;
	for(int i = 0; i < HEIGHT; i++){
		if(i % gridSize == 0)
		SDL_RenderDrawLine(renderer,0,i,WIDTH,i);
	}
	for(int j = 0; j < WIDTH; j++){
		if(j % gridSize == 0)
		SDL_RenderDrawLine(renderer, j,0,j,HEIGHT);
	}

	//Add inverted circle border
	SDL_Point center = {WIDTH /2, HEIGHT/2};
	color = {53,50,47,255};
	drawCircle(renderer, center, WIDTH/2, HEIGHT/2, color);
	color = {60,28,6,255};
	drawCircle(renderer, center, WIDTH/2 + 10, HEIGHT/2 + 10, color);

	writeName(renderer);
	SDL_RenderPresent(renderer);
}
