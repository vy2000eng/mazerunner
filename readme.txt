Build mazerunner program and player_randommove.so library

g++ -ansi -pedantic -std=c++14  maze.cxx  mazerunner.cxx  main.cxx  -o mazerunner
g++ -shared -fPIC -ansi -pedantic -std=c++14 my_solution.cxx  -o my_solution.so


Solving fogged mazes

./mazerunner  ./maze1.txt  ./my_solution.so


Competing solving fogged mazes with others

./mazerunner  ./maze1.txt  ./my_solution.so  ./player_randommove.so

g++ -shared -g -fPIC -ansi -pedantic -std=c++14 my_solution.cxx ds_for_search.cpp -o my_solution.so
