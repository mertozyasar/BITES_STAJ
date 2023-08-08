#include <iostream>
#include <vector>
#include "graph.h"
using namespace std;
Graph::Graph(int rows, int cols) {
    numRows = rows;
    numCols = cols;
    grid.resize(rows, std::vector<int>(cols, 0));
    visited.resize(rows, std::vector<bool>(cols, false));
}



void Graph::DFS(int row, int col) {
    
        visited[row][col] = true;
        std::cout << "(" << row << ", " << col << ")" << endl;



        //çapraz komþularýda kontrol et
        static int dr[] = { 1,1,0,-1,-1,-1,0,1 };
        static int dc[] = { 0, 1,1,1,0,-1,-1,-1 };

        for (int dir = 0; dir < 8; ++dir) {


            int newRow = row + dr[dir];
            int newCol = col + dc[dir];
            
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && !visited[newRow][newCol]) {
                DFS(newRow, newCol);
            }

        }
    
}