#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector<vector<int>> aStar(const vector<vector<int>>& grid, vector<int> src, vector<int> dst)
{
    //establish bounds
    int rows = grid.size();
    int cols = grid[0].size();

    //vector of coords to be checked
    vector<vector<int>> openSet;
    openSet.push_back(src); //start from start

    //temp invalid values
    vector<vector<vector<int>>> cameFrom(rows, vector<vector<int>>(cols, vector<int>(2, -1)));

    //help avoid redundant nodes in the openSet
    vector<vector<bool>> inOpenSet(rows, vector<bool>(cols, false));
    inOpenSet[src[0]][src[1]] = true;

    //path cost
    vector<vector<int>> gScore(rows, vector<int>(cols, 1e9));
    gScore[src[0]][src[1]] = 0;

    //heuristic that just points directly towards goal via taxicab distance
    //used to determine if a node is "more likely" to be closer to the goal
    vector<vector<int>> fScore(rows, vector<int>(cols, 1e9));

    /*
        stupid implementation that avoids using abs(src + dst)
        this was easier than doing bitmath to flip the sign bit but the whole concept is stupid
        you could probably also do diagonals instead of taxicab distance, this would make this
        implementation less jank but would overvalue nodes in some instances
        I felt smart for coming up with this before realizing that a^2 + b^2 would work too, but its
        technically more accurate so it stays.
    */
    int dx = src[0] - dst[0];
    int dy = src[1] - dst[1];
    int h = (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);
    fScore[src[0]][src[1]] = h;

    //valid movement directions, can be modified for diagonals or even weirder movements i.e chess knights
    vector<vector<int>> compass = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };


    while (!openSet.empty())
    {
        // Find node with lowest fScore in the openSet to start with
        // would be avoided by just using a priority queue
        int low = 0;
        for (size_t i = 1; i < openSet.size(); ++i)
        {
            vector<int>& point = openSet[i];
            if (fScore[point[0]][point[1]] < fScore[openSet[low][0]][openSet[low][1]])
            {
                low = i;
            }
        }

        //remove current node from the queue so its not rechecked
        vector<int> current = openSet[low];
        openSet.erase(openSet.begin() + low);
        inOpenSet[current[0]][current[1]] = false;

        //if the current node happens to be the destination, rebuild the shortest path
        //using the cameFrom grid, really this would be better done with classes/structs rather
        //than like 3 2d vectors

        //if the path is the wrong way around, IE (y,x) this is where the swap should be but it would
        //probably need a decent rewrite
        if (current[0] == dst[0] && current[1] == dst[1])
        {
            vector<vector<int>> path;
            while (current[0] != src[0] || current[1] != src[1]) {
                path.insert(path.begin(), current);
                int prevX = cameFrom[current[0]][current[1]][0];
                int prevY = cameFrom[current[0]][current[1]][1];
                current[0] = prevX;
                current[1] = prevY;
            }
            path.insert(path.begin(), src);
            return path;
        }

        //look through all neighbors to find the one with the cheapest path cost
        //add it to the list to be checked
        for (vector<int>& dir : compass)
        {
            //neighbor coordinates
            int nx = current[0] + dir[0];
            int ny = current[1] + dir[1];

            //check that neighbor is not out of bounds
            bool isValid = nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0;
            if (!isValid) continue;

            //this is the cost to reach neighbor via the current node
            int tentative_g = gScore[current[0]][current[1]] + 1;

            //if this is better than the previous cost update it
            if (tentative_g < gScore[nx][ny])
            {
                cameFrom[nx][ny][0] = current[0];
                cameFrom[nx][ny][1] = current[1];
                gScore[nx][ny] = tentative_g;

                //again stupid taxicab distance calculation to determine the better node
                //would be better with abs()
                int hdx = dst[0] - nx;
                int hdy = dst[1] - ny;
                int h = (hdx < 0 ? -hdx : hdx) + (hdy < 0 ? -hdy : hdy);
                fScore[nx][ny] = tentative_g + h;
                
                //avoid duplication
                if (!inOpenSet[nx][ny])
                {
                    openSet.push_back({nx, ny});
                    inOpenSet[nx][ny] = true;
                }
            }
        }
    }

    return {}; // No path found
}

void printGridWithPath(const vector<vector<int>>& grid, const vector<vector<int>>& path, vector<int> src, vector<int> dst) {
    vector<vector<char>> visual(grid.size(), vector<char>(grid[0].size(), ' '));

    // Fill in obstacles
    for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[0].size(); ++j)
            if (grid[i][j] == 1)
                visual[i][j] = '#';

    // Fill in path
    for (const auto& p : path)
        visual[p[0]][p[1]] = '.';

    // Mark start and destination
    visual[src[0]][src[1]] = 'S';
    visual[dst[0]][dst[1]] = 'D';

    // Print grid
    for (int i = 0; i < visual.size(); ++i) {
        for (int j = 0; j < visual[0].size(); ++j) {
            cout << visual[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 1, 0}
    };

    vector<int> src = {0, 9};
    vector<int> dst = {6, 0};

    vector<vector<int>> path = aStar(grid, src, dst);

    if (!path.empty()) {
        cout << "Path found:\n";
        for (const auto& p : path) {
            cout << "(" << p[0] << ", " << p[1] << ") ";
        }
        cout << "\n\nGrid Visualization:\n";
        printGridWithPath(grid, path, src, dst);
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
