#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <thread>
#include <queue>
#include <cmath>
#include <sstream> 



class Graph {
private:
    int numRows;
    int numCols;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> visited;
    int frow, fcol;
    int currentRow; 
    int currentCol; 
    double tentative_g_cost;
    double heuristic(int row, int col);
    std::vector<std::pair<int, int>> path; // Geçilen yolu saklamak için
    
    

public: 
    Graph(int rows, int cols);
    void AStar();
    void finish();
    void obstacle(int numobstacle);
    void DFS(int row, int col);
    void BFS();
    
};