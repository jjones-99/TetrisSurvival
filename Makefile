# project source and header files
SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.h)

# C++ compile and linker flags
CPPFLAGS=-O0 `sdl2-config --cflags`
LDFLAGS=`sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL

# location of cxxtest
CXXTEST_HOME = cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

# additional lists
MAIN_OBJECTS=$(SOURCES:.cpp=.o)

# rules
all: main

main: $(MAIN_OBJECTS)
	g++ -std=c++11 -fPIC $^ -o $@ $(LDFLAGS)

$(MAIN_OBJECTS): %.o: %.cpp $(HEADERS) Makefile
	g++ -std=c++11 -c $< -o $@ $(CPPFLAGS)

clean:
	rm -f main  $(MAIN_OBJECTS) *~
