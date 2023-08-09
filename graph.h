#include <iostream>
#include <vector>


class Graph {
private:
    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> visited;
    
    

public:
    void obstacle(int obstaclenum);
    void currentposition();
    Graph(int rows, int cols);
    void DFS(int row, int col);
    
};