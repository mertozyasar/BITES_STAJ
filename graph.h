#include <iostream>
#include <vector>


class Graph {
private:
    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> visited;
    int frow = 2, fcol = 3;
    int currentRow; // �u anki sat�r konumu
    int currentCol; // �u anki s�tun konumu
    
    

public:
    void obstacle(int numobstacle);
    Graph(int rows, int cols);
    void DFS(int row, int col);
    
};