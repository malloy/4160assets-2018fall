
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = g++
endif

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS =
else
  ifeq ("$(shell uname)", "Linux")
  LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat
  endif
endif

OBJS = \
	main.o \
	ioManager.o \
	vector2f.o \
	health.o \
	aaline.o

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp ioManager.h health.h
vector2f.o: vector2f.cpp vector2f.h
ioManager.o: ioManager.cpp ioManager.h
health.o: health.cpp health.h aaline.h
aaline.o: aaline.cpp aaline.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
