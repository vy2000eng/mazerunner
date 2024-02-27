# Compiler and flags
CXX = g++
CXXFLAGS = -g -ansi -pedantic -std=c++14

# Targets
all: player_randommove.so mazerunner

# Compile player_randommove.so
player_randommove.so: my_solution.cxx ds_for_search.cpp
	$(CXX) -shared -fPIC $(CXXFLAGS) $< -o $@

# Compile mazerunner
mazerunner: maze.cxx mazerunner.cxx main.cxx
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean
clean:
	rm -f *.so mazerunner


#g++ -shared -g -fPIC -ansi -pedantic -std=c++14 player_randommove.cxx ds_for_search.cpp -o player_randommove.so
