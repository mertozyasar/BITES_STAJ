#include <iostream>
#include <vector>


class Graph {
private:
    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> visited;
    int frow, fcol;
    int currentRow; 
    int currentCol; 
    int row,col;
    
    

public:
    void finish();
    void obstacle(int numobstacle);
    Graph(int rows, int cols);
    void DFS(int row, int col);
    
};