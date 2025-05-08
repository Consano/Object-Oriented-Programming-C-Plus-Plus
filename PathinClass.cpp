#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> aStar(const vector<vector<int>>& grid, vector<int> src, vector<int> dst)
{
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> openSet;
    openSet.push_back(src);

    vector<vector<vector<int>>> cameFrom(rows, vector<vector<int>>(cols, {-1, -1}));

    vector<vector<bool>> inOpenSet(rows, vector<bool>(cols, false));
    inOpenSet[src[0]][src[1]] = true;

    vector<vector<int>> gScore(rows, vector<int>(cols, 1e9));
    gScore[src[0]][src[1]] = 0;

    vector<vector<int>> fScore(rows, vector<int>(cols, 1e9));
    //this is really stupid and made irrelavant by if I can use cmath or similar
    //int combinedHeuristic = abs(src[0] - dst[0]) + abs(src[1] - dst[1]);
    int differenceX = (src[0] - dst[0]);
    int differenceY = (src[1] - dst[1]);
    int heuristicX = (differenceX < 0) ? -(differenceX) : (differenceX);
    int heuristicY = (differenceY < 0) ? -(differenceY) : (differenceY);
    int combinedHeuristic = heuristicX + heuristicY;
    fScore[src[0]][src[1]] = combinedHeuristic;

    vector<vector<int>> compass = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1} // up, down, left, right
    };

    while (!openSet.empty())
    {
        // Sort openSet to find best node, priority queue makes this irrelevant
        int low = 0;
        for (size_t i = 1; i < openSet.size(); ++i)
        {
            vector<int>& point = openSet[i]; //establish current point being checked
            if (fScore[point[0]][point[1]] < fScore[openSet[low][0]][openSet[low][1]]) // check vs current lowest point
            {
                low = i;
            }
        }


        vector<int> current = openSet[low];
        openSet.erase(openSet.begin()+low); //remove from openSet
        inOpenSet[current[0]][current[1]] = false; //remove from open set as its checked

        if (current == dst) // reconstruct the path used to get here from the best nodes
        {
            vector<vector<int>> path;
            while (current != src) {
                path.insert(path.begin(), current);
                current = cameFrom[current[0]][current[1]];
            }
            path.insert(path.begin(), src);
            return path;
        }

        for (vector<int>& dir : compass) //check neighbors for closer nodes
        {
            vector<int> neighbor = {current[0] + dir[0], current[1] + dir[1]}; // set neighbor to first node in compass list
        
            //check for valid neighbor
            bool isValid = neighbor[0] >= 0 && neighbor[1] >= 0 && neighbor[0] < rows && neighbor[1] < cols && grid[neighbor[0]][neighbor[1]] == 0;
            
            if (!isValid)
            {
                continue;
            }

            int temp_gScore = gScore[current[0]][current[1]] + 1; //check if neighbor is better
            if (temp_gScore < gScore[neighbor[0]][neighbor[1]])
            {
                cameFrom[neighbor[0]][neighbor[1]] = current; //move to the neighbor and set a marker backwards
                gScore[neighbor[0]][neighbor[1]] = temp_gScore;

                //again this is stupid
                differenceY = (neighbor[1] - dst[1]);
                differenceX = (neighbor[0] - dst[0]);
                heuristicX = (differenceX < 0) ? -(differenceX) : (differenceX);
                heuristicY = (differenceY < 0) ? -(differenceY) : (differenceY);
                combinedHeuristic = heuristicX + heuristicY;
                fScore[neighbor[0]][neighbor[1]] = temp_gScore + combinedHeuristic;

                if (!inOpenSet[neighbor[0]][neighbor[1]]) //avoid duplicate entries in openSet
                {
                    openSet.push_back(neighbor);
                    inOpenSet[neighbor[0]][neighbor[1]] = true; //update list of nodes to be checked
                }
            }

        }
    }

    return {}; //no path found
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    vector<int> start(0,0);
    vector<int> destination(4,4);

    vector<vector<int>> path = aStar(grid, start, destination);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (const auto& pos : path) {
            cout << "(" << pos[0] << ", " << pos[1] << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}