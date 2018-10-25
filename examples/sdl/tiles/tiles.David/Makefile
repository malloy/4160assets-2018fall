
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = g++
endif
CXX_LINK = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat

OBJS = \
	main.o \
	viewport.o \
	world.o \
	manager.o \
	gamedata.o \
	parseXML.o \
	clock.o \
	vector2f.o \
	sprite.o \
	frame.o \
	ioManager.o \
	frameFactory.o \
	spriteFactory.o \
	multisprite.o \
	multisprite2way.o \
	tilesprite.o

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp manager.h
manager.o: manager.cpp manager.h gamedata.h ioManager.h sprite.h clock.h \
	world.h viewport.h frame.h
ioManager.o: ioManager.cpp ioManager.h
viewport.o: viewport.cpp viewport.h sprite.h gamedata.h
world.o: world.cpp world.h frame.h viewport.h
parseXML.o: parseXML.cpp parseXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h
frameFactory.o: frameFactory.cpp frameFactory.h
spriteFactory.o: spriteFactory.cpp spriteFactory.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h
multisprite.o: multisprite.cpp multisprite.h drawable.h frame.h
multisprite2way.o: multisprite2way.cpp multisprite2way.h drawable.h frame.h
tilesprite.o: tilesprite.cpp tilesprite.h drawable.h frame.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
