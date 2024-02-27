#ifndef __PLAYER_TYPE_1__
#define __PLAYER_TYPE_1__

#include <iostream>
#include "common.h"
#include "maze.h"
#include "player.h"
#include "ds_for_search.h"
using namespace std;

class PlayerRandomMove : public IPlayer
{
    MazeElem player;
    char ** internal_maze;  // internal maze
    bool ** closed_set;
    Loc current_loc;
    Loc prev_loc;
    //Loc goal;
    Loc start;
    int i_m_rows;
    int i_m_cols;
    //Node* start_node;
   // PriorityQueue<Node*> openSet;
    Queue<Direct> path;
    Node*** openSetNode;
    Stack<Direct> moves_taken;
    bool back_tracking;
    bool visited_loc[100][100] = {false};//this is fot determining direction
    //bool v[100][100];
    bool goal_visible_in_i_m;
    Queue<Node*> queue;
    Queue<Node*>visited;
    bool path_valid;
    bool targets[100][100];
    int explored_cells_count;
    int totalCells ;

     double baseThreshold;
  //  PriorityQueue<Node*> openSet;
   // bool backtracking;

public:
    PlayerRandomMove();
    void Init(const MazeElem player, const int maze_rows, const int maze_cols);
    void Close();
    Direct Move(const int iter, const Loc& loc, const IMaze* maze);
    void InitAStar(const Loc& start, const Loc& final);
    bool AStarSearch(const IMaze *pMaze, Loc start, Loc target);
    bool isPassable(const IMaze *maze, const Loc &loc);

    bool is_passable_internal_matrix(Loc loc);

    void ReconstructPath(Node *pNode);

    double CalculateTargetScore(const Loc &potentialTarget, const Loc &currentLoc);

    bool alreadyExplored(const Loc &loc);

    Loc DetermineNextTarget(const Loc &currentLoc, const IMaze *pMaze, int i);


    Direct ReverseMove(Direct move);

    void update_maze(const Loc loc, const IMaze *pMaze);
    double get_exploration_progress();
    double calculate_adjusted_threshold();


   // Loc findNearestUnexploredArea(const Loc &loc);
};

#endif
