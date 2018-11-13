# Change the following values to suit your system.
CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O2
SDL_LIB=`sdl-config --libs`
CCC=g++

run: main.cpp explodedSprite.h
	$(CCC) $(CFLAGS) main.cpp -o run $(SDL_LIB)

clean:
	rm -f run
	rm -f *~
