#include <iostream>
#include <assert.h>
#include <limits>
#include "common.h"
#include "maze.h"
#include "player.h"
#include "YatsutaVladyslav_vjy5021.h"

using namespace std;

extern "C" IPlayer* PlayerFactory()
{
    return new PlayerRandomMove();
}

PlayerRandomMove::PlayerRandomMove()
{
}

void PlayerRandomMove::Init(const MazeElem player, const int maze_rows, const int maze_cols)
{
    assert(player == A_PLAYER || player == B_PLAYER);
    this->player = player;
    back_tracking = false;
    srand(static_cast<unsigned int>(time(nullptr)));
    this->internal_maze = new char*[maze_rows];
    this->closed_set = new bool*[maze_rows];
    openSetNode = new Node**[maze_rows];
    path_valid = false;
    for(int i = 0; i < maze_rows; i++){
        closed_set[i] = new bool[maze_cols];
        internal_maze[i] = new char[maze_cols];
        openSetNode[i] = new Node*[maze_cols];
        std::fill(internal_maze[i], internal_maze[i] + maze_cols, '?');
        std::fill(closed_set[i], closed_set[i] + maze_cols, false);
        for(int j = 0; j < maze_cols; j++){
            openSetNode[i][j] = nullptr;
        }

    }
    this->i_m_rows = maze_rows;
    this->i_m_cols = maze_cols;
    back_tracking = false;
    goal_visible_in_i_m = false;



}

void PlayerRandomMove::Close()
{
    for(int i = 0; i < this->i_m_rows; i++){
       // delete[] openSetNode[i];
        for(int j = 0; j < i_m_cols; j++){
            delete openSetNode[i][j];
        }
        delete[] closed_set[i];
        delete [] internal_maze[i];
    }
    delete []openSetNode;
    delete [] internal_maze;
    delete[] closed_set;
    delete start_node;
}



void PlayerRandomMove::update_maze(const Loc loc, const IMaze *pMaze) {
    int fogBoundary = 4;
    Loc goal = pMaze->GetExitLoc();
    for (int r = max(0, loc.r - fogBoundary); r <= min(i_m_rows - 1, loc.r + fogBoundary); ++r) {
        for (int c = max(0, loc.c - fogBoundary); c <= min(i_m_cols - 1, loc.c + fogBoundary); ++c) {
            Loc currentLoc(r, c);
            //if(maze->GetElem(currentLoc) == EMPTY)

            //if((goal.r == currentLoc.r && goal.c == currentLoc.c) )
            if(currentLoc.r == goal.r && currentLoc.c == goal.c )
                goal_visible_in_i_m = true;


            internal_maze[r][c] = pMaze->GetElem(currentLoc);

        }
    }

}




Direct PlayerRandomMove::Move(const int iter, const Loc& loc, const IMaze* maze) {


    assert(maze->GetElem(loc) == player);


    update_maze(loc, maze);


////////////////////
//NNEEWWWW SSTTUUUFFFFFF


//    InitAStar(loc,goal);
    Loc goalLoc;

    //pdate_maze(loc,maze);
    if (maze->GetElem(loc.GetMoved(UP)) == EXIT) return UP;
    if (maze->GetElem(loc.GetMoved(DOWN)) == EXIT) return DOWN;
    if (maze->GetElem(loc.GetMoved(LEFT)) == EXIT) return LEFT;
    if (maze->GetElem(loc.GetMoved(RIGHT)) == EXIT) return RIGHT;

    assert(maze->GetElem(loc) == player);
    update_maze(loc, maze);
//    if(visited_loc[loc.r][loc.c])
//        return ReverseMove(moves_taken.Pop());
    if (!path.IsEmpty() && path_valid) {
        Direct move = path.Dequeue();
        Loc nextLoc = loc.GetMoved(move);
        if (!visited_loc[nextLoc.r][nextLoc.c] && is_passable_internal_matrix(nextLoc)) {
            moves_taken.Push(move);
            return move;
        }
    }

    // Path recalculation
    if (!path_valid || path.IsEmpty()) {
        Loc target = DetermineNextTarget(loc, maze);
        targets[target.r][target.c] = true;
        path_valid = AStarSearch(maze, loc, target);
    }

    // New path following
    if (!path.IsEmpty()) {
        Direct move = path.Dequeue();
            moves_taken.Push(move);


            return move;

    }

    // Backtracking
    while (!moves_taken.IsEmpty()) {
        Direct lastMove = moves_taken.Pop();
        Direct reverseMove = ReverseMove(lastMove);
        Loc newLoc = loc.GetMoved(reverseMove);
        if (!visited_loc[newLoc.r][newLoc.c] && is_passable_internal_matrix(newLoc)) {
            return reverseMove;
        }
    }

    // Fallback strategy (e.g., random move, reset visited locations, etc.)

    return STOP; // No moves left, stop the player

}





/////////////////////////////////////////////////////////////////////
//THIS IS THE LAST IMPLEMENTATION
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//
//    // Follow the path if it's not empty and valid
//    if (!path.IsEmpty() && path_valid) {
//        Direct move = path.Dequeue();
//        moves_taken.Push(move);
//        return move;
//    }
//
//    // Determine new target and recalculate path if path is not valid
//    if (!path_valid) {
//        Loc target = DetermineNextTarget(loc, maze);
//        visited_loc[target.r][target.c] = true;
//        path_valid = AStarSearch(maze, loc, target);
//    }
//
//    // Follow the new path
//    if (!path.IsEmpty()) {
//        Direct move = path.Dequeue();
//        moves_taken.Push(move);
//        return move;
//    }
//    else{
//        //return ReverseMove(moves_taken.Pop());
//        if (!moves_taken.IsEmpty()) {
//            // Find a valid move to backtrack
//            if (!moves_taken.IsEmpty()) {
//                Direct lastMove = moves_taken.Pop();
//                Direct reverseMove = ReverseMove(lastMove);
//                Loc target = DetermineNextTarget(loc, maze);
//
//
//                //  Loc newLoc = loc.GetMoved(reverseMove);
//                // Check if the reverse move is valid and hasn't been visited
//                if (is_passable_internal_matrix(target) ||!visited_loc[target.r][target.c]  ) {
//                   // visited_loc[newLoc.r][newLoc.c] = true;  // Mark as visited
//                    //Loc target = DetermineNextTarget(loc, maze);
//                    visited_loc[target.r][target.c] = true;
//                    path_valid = AStarSearch(maze, loc, target);
//
//                    return path.Dequeue();
//                }
//            }
//        }
//
//        return STOP;
//    }
//
//
//



//////////////////////////////////////////////////////////////////////
//THIS IS THE LAST IMPLEMENTATION
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
//    if(goal_visible_in_i_m){
//        goalLoc = maze->GetExitLoc();
//        AStarSearch(maze, loc, goalLoc);
//        //visited_loc[target.r][target.c] = true;
//        Direct move = path.Dequeue();
//        moves_taken.Push(move);
//        return move;
//
//    }
//
//    else {
//
//        Loc target = DetermineNextTarget(loc, maze);
//        visited_loc[target.r][target.c] = true;
//        AStarSearch(maze, loc, target);
//    }
//
//    if(!path.IsEmpty()){
//        current_loc = prev_loc;
//       Direct move = path.Dequeue();
//       moves_taken.Push(move);
//        return move;
//    }else{
//        //return ReverseMove(moves_taken.Pop());
//        if (!moves_taken.IsEmpty()) {
//            // Find a valid move to backtrack
//            if (!moves_taken.IsEmpty()) {
//                Direct lastMove = moves_taken.Pop();
//                Direct reverseMove = ReverseMove(lastMove);
//
//                Loc newLoc = loc.GetMoved(reverseMove);
//                // Check if the reverse move is valid and hasn't been visited
//                if (is_passable_internal_matrix(newLoc) ||!visited_loc[newLoc.r][newLoc.c]  ) {
//                    //visited_loc[newLoc.r][newLoc.c] = true;  // Mark as visited
//                    Loc target = DetermineNextTarget(loc, maze);
//                    //visited_loc[target.r][target.c] = true;
//                    AStarSearch(maze, loc, target);
//
//                    return reverseMove;
//                }
//            }
//        }
//
//        return STOP;
//    }
    //return path.Dequeue();


//    // if current location is right beside of exit, move to that direction
//    if(maze->GetElem(loc.GetMoved(UP   )) == EXIT) return UP;
//    if(maze->GetElem(loc.GetMoved(DOWN )) == EXIT) return DOWN;
//    if(maze->GetElem(loc.GetMoved(LEFT )) == EXIT) return LEFT;
//    if(maze->GetElem(loc.GetMoved(RIGHT)) == EXIT) return RIGHT;
//
//    // do not move if current location is fully blocked by walls and other player
//    if(maze->GetElem(loc.GetMoved(UP   )) != EMPTY &&
//       maze->GetElem(loc.GetMoved(DOWN )) != EMPTY &&
//       maze->GetElem(loc.GetMoved(LEFT )) != EMPTY &&
//       maze->GetElem(loc.GetMoved(RIGHT)) != EMPTY)
//        return STOP;
//
//    // find an empty direction and move toward the direction
//    while(true)
//    {
//        Direct move = (Direct)(rand() % 4);
//        Loc newloc = loc.GetMoved(move);
//        if(maze->GetElem(newloc) == EMPTY)
//            return move;
//    }

Direct PlayerRandomMove::ReverseMove(Direct move) {
    switch (move) {
        case UP: return DOWN;
        case DOWN: return UP;
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
        default: return STOP; // or a sensible default
    }
}


Loc PlayerRandomMove::DetermineNextTarget(const Loc &currentLoc, const IMaze *pMaze) {
    // Placeholder for the chosen target location


    Loc target = currentLoc;
    double bestScore = std::numeric_limits<double>::max();
    int visibilityRange = 4;
    bool foundTarget = false;


    // Variables to hold the best score (or distance, or any metric you choose)
   // double bestScore = std::numeric_limits<double>::max();
    // Iterate through the visible area or the boundary of the explored area
    //int visibilityRange = 4;
    for (int r = max(0, currentLoc.r - visibilityRange); r <= min(i_m_rows - 1, currentLoc.r + visibilityRange); ++r) {
        for (int c = max(0, currentLoc.c - visibilityRange); c <= min(i_m_cols - 1, currentLoc.c + visibilityRange); ++c) {
            Loc potentialTarget(r, c);


            if (!is_passable_internal_matrix(potentialTarget)|| targets[potentialTarget.r][potentialTarget.c]) continue;
            //if(back_tracking && targets[potentialTarget.r][potentialTarget.c]) continue;
            double score = CalculateTargetScore( potentialTarget, pMaze->GetExitLoc());


            // Update the best target if this score is better
            if (score <bestScore) {
                bestScore = score;
                target = potentialTarget;
                foundTarget = true;
            }


        }
    }
    // Return the target with the best score
    if (!foundTarget) {
        do {
            int randomRow = rand() % (2 * visibilityRange + 1) + currentLoc.r - visibilityRange;
            int randomCol = rand() % (2 * visibilityRange + 1) + currentLoc.c - visibilityRange;
            //target = Loc(randomRow, randomCol);
            randomRow = max(0, min(randomRow, i_m_rows));
            randomCol = max(0, min(randomCol, i_m_cols));
            target = Loc(randomRow, randomCol);

        } while (!is_passable_internal_matrix(target));
    }

    return target;
    return target;
}

//void PlayerRandomMove::InitAStar(const Loc &begin, const Loc &final) {
//    start_node = new Node(begin, nullptr, 0, Node::CalculateHCost(begin, final));
//    openSet.EnqueueWithPriority(start_node);
//
//}

bool PlayerRandomMove::isPassable(const IMaze *maze, const Loc &loc) {
    return maze->GetElem(loc) == EMPTY;
//    char c =  internal_maze[loc.r][loc.c];
//    if(c == '?')
//        return false;
//    else if(c == '#')
//        return false;
//    else
//        return true;

   // return c != '?'|| c != '#';


}
double PlayerRandomMove::CalculateTargetScore(const Loc& loc1, const Loc& loc2) {
    // Using Manhattan distance as the score
    double s = abs(loc1.r - loc2.r) + abs(loc1.c - loc2.c);
    return s;}


bool PlayerRandomMove::alreadyExplored(const Loc& loc) {
    return internal_maze[loc.r][loc.c] != '?';
}

void PlayerRandomMove::ReconstructPath(Node *pNode) {
   // DirectionArray path;
   //path.Clear();
   path.Clear();

   Queue<Direct> new_path;
    Node* currentNode = pNode;


    while (currentNode->parent != nullptr) {
        // Determine the direction from the parent node to the current node
        if (currentNode->location.r > currentNode->parent->location.r) {
            new_path.Enqueue(DOWN);
        } else if (currentNode->location.r < currentNode->parent->location.r) {
            new_path.Enqueue(UP);
        } else if (currentNode->location.c > currentNode->parent->location.c) {
            new_path.Enqueue(RIGHT);
        } else if (currentNode->location.c < currentNode->parent->location.c) {
            new_path.Enqueue(LEFT);
        }

        currentNode = currentNode->parent;
    }
    //path = new_path;
    path = new_path;
    path.Reverse();


    //path.Reverse();
    //return path;

}




bool PlayerRandomMove::AStarSearch(const IMaze *pMaze, Loc begin, Loc target) {

    Loc exit = pMaze->GetExitLoc();
    Node* startNode =new Node(begin, nullptr, 0, Node::CalculateHCost(begin, exit));
    //openSet.EnqueueWithPriority(startNode);
    PriorityQueue<Node*> openSet;
    Node* bestNodeSoFar = nullptr;
    double bestHCostSoFar = std::numeric_limits<double>::max();

    for (int i = 0; i < i_m_rows; ++i) {
        for (int j = 0; j < i_m_cols; ++j) {
           //closed_set[i][j] = false;
            //openSetNode[i][j] = nullptr;
        }
    }
//    Node ***ops = new Node**[i_m_rows];
//    for(int i = 0; i < i_m_rows; i++){
//        ops[i] = new Node*[i_m_cols];
//        for(int j = 0; j < i_m_cols; j++){
//           ops[i][j] = nullptr;
//        }

    // }
    for (int i = 0; i < i_m_rows; ++i) {
        std::fill(closed_set[i], closed_set[i] + i_m_cols, false); // Reset closed set
        for (int j = 0; j < i_m_cols; ++j) {
            if (openSetNode[i][j] != nullptr) {
                delete openSetNode[i][j];  // Delete existing Node
                openSetNode[i][j] = nullptr;  // Reset pointer
            }
        }
    }
    openSet.EnqueueWithPriority(startNode);

    while (!openSet.IsEmpty()) {
        Node *current = openSet.Dequeue();

        // Mark the current node as processed
        closed_set[current->location.r][current->location.c] = true;
        if (current->hCost < bestHCostSoFar) {
            bestNodeSoFar = current;
            bestHCostSoFar = current->hCost;
        }

        if (current->location.r == target.r && current->location.c == target.c) {
            // Goal reached, reconstruct path
            ReconstructPath(current);
            return true;
        }
        // Process neighbors and update open set and closed set
        // ...
        for (Direct dir: {UP, DOWN, LEFT, RIGHT}) {
            Loc neighborLoc = current->location.GetMoved(dir);
            if (!is_passable_internal_matrix( neighborLoc) || closed_set[neighborLoc.r][neighborLoc.c])
                continue;
            //if (closed_set[neighborLoc.r][neighborLoc.c]) continue;


            Node *neighborNode = openSetNode[neighborLoc.r][neighborLoc.c];
            //neighborNode->parent = current;
            double tentativeGCost = current->gCost + 1;


            if (neighborNode == nullptr) {
                neighborNode = new Node(neighborLoc, current, tentativeGCost, Node::CalculateHCost(neighborLoc, pMaze->GetExitLoc()));
                openSet.EnqueueWithPriority(neighborNode);
                openSetNode[neighborLoc.r][neighborLoc.c] = neighborNode;  // Add the node to the openSetNode array
            } else if (tentativeGCost < neighborNode->gCost) {
                // Update the costs and parent of the neighbor node if a better path is found
                neighborNode->gCost = tentativeGCost;
                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
                neighborNode->parent = current;
                openSet.EnqueueWithPriority(neighborNode);


            }


        }


    }
    if (bestNodeSoFar != nullptr) {
        ReconstructPath(bestNodeSoFar);
        //return true; // Indicate a path has been found, even if it's not to the original target
    }
//    for (int i = 0; i < i_m_rows; ++i) {
//        for (int j = 0; j < i_m_cols; ++j) {
//            //if (openSetNode[i][j] != nullptr) {
//                closed_set[i][j] = false;
//               // delete openSetNode[i][j];
//
//                //delete ops[i][j];
//              //  ops[i][j] = nullptr;
//                openSetNode[i][j] = nullptr;
//
//            //}
//        }
    //}
    if(path.IsEmpty())
        return false;
    else
        return true;



}














//////////////////////////////////////////////////////////////////////
//THIS IS THE LAST IMPLEMENTATION
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


//bool PlayerRandomMove::AStarSearch(const IMaze *pMaze, Loc begin, Loc target) {
//
//    Loc exit = pMaze->GetExitLoc();
//    Node* startNode =new Node(begin, nullptr, 0, Node::CalculateHCost(begin, exit));
//    //openSet.EnqueueWithPriority(startNode);
//    PriorityQueue<Node*> openSet;
//    Node* bestNodeSoFar = nullptr;
//    double bestHCostSoFar = std::numeric_limits<double>::max();
//
//    for (int i = 0; i < i_m_rows; ++i) {
//        for (int j = 0; j < i_m_cols; ++j) {
//            closed_set[i][j] = false;
//            //openSetNode[i][j] = nullptr;
//        }
//    }
////    Node ***ops = new Node**[i_m_rows];
////    for(int i = 0; i < i_m_rows; i++){
////        ops[i] = new Node*[i_m_cols];
////        for(int j = 0; j < i_m_cols; j++){
////           ops[i][j] = nullptr;
////        }
//
//   // }
//    for (int i = 0; i < i_m_rows; ++i) {
//        std::fill(closed_set[i], closed_set[i] + i_m_cols, false); // Reset closed set
//        for (int j = 0; j < i_m_cols; ++j) {
//            if (openSetNode[i][j] != nullptr) {
//                delete openSetNode[i][j];  // Delete existing Node
//                openSetNode[i][j] = nullptr;  // Reset pointer
//            }
//        }
//    }
//    openSet.EnqueueWithPriority(startNode);
//
//    while (!openSet.IsEmpty()) {
//        Node *current = openSet.Dequeue();
//
//        // Mark the current node as processed
//        closed_set[current->location.r][current->location.c] = true;
//        if (current->hCost < bestHCostSoFar) {
//            bestNodeSoFar = current;
//            bestHCostSoFar = current->hCost;
//        }
//
//        if (current->location.r == target.r && current->location.c == target.c) {
//            // Goal reached, reconstruct path
//            ReconstructPath(current);
//            return true;
//        }
//        // Process neighbors and update open set and closed set
//        // ...
//        for (Direct dir: {UP, DOWN, LEFT, RIGHT}) {
//            Loc neighborLoc = current->location.GetMoved(dir);
//            if (!is_passable_internal_matrix( neighborLoc) || closed_set[neighborLoc.r][neighborLoc.c])
//                continue;
//            //if (closed_set[neighborLoc.r][neighborLoc.c]) continue;
//
//
//            Node *neighborNode = openSetNode[neighborLoc.r][neighborLoc.c];
//            //neighborNode->parent = current;
//            double tentativeGCost = current->gCost + 1;
//
//
//            if (neighborNode == nullptr) {
//                neighborNode = new Node(neighborLoc, current, tentativeGCost, Node::CalculateHCost(neighborLoc, pMaze->GetExitLoc()));
//                openSet.EnqueueWithPriority(neighborNode);
//                openSetNode[neighborLoc.r][neighborLoc.c] = neighborNode;  // Add the node to the openSetNode array
//            } else if (tentativeGCost < neighborNode->gCost) {
//                // Update the costs and parent of the neighbor node if a better path is found
//                neighborNode->gCost = tentativeGCost;
//                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
//                neighborNode->parent = current;
//                openSet.EnqueueWithPriority(neighborNode);
//
//
//            }
//
//
//        }
//
//
//    }
//    if (bestNodeSoFar != nullptr) {
//        ReconstructPath(bestNodeSoFar);
//        return true; // Indicate a path has been found, even if it's not to the original target
//    }
////    for (int i = 0; i < i_m_rows; ++i) {
////        for (int j = 0; j < i_m_cols; ++j) {
////            //if (openSetNode[i][j] != nullptr) {
////                closed_set[i][j] = false;
////               // delete openSetNode[i][j];
////
////                //delete ops[i][j];
////              //  ops[i][j] = nullptr;
////                openSetNode[i][j] = nullptr;
////
////            //}
////        }
//    //}
//    return false;
//
//
//
//}




///////////////////////////////////////////////////////////////////////
//THIS IS THE LAST IMPLEMENTATION
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

bool PlayerRandomMove::is_passable_internal_matrix(Loc loc) {
    return internal_maze[loc.r][loc.c] == ' ';
}









