#include <iostream>
#include <vector>
#include "graph.h"
#include <random>
#include <chrono>
#include <thread>

using namespace std;
Graph::Graph(int rows, int cols) {



    numRows = rows;
    numCols = cols;
    grid.resize(rows, std::vector<int>(cols, 0));
    visited.resize(rows, std::vector<bool>(cols, false));
}

void Graph::obstacle(int numobstacle) {
    

     // Rastgele say� �reteci 
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, (numRows-1));
    for (int i = 0; i < numobstacle; i++) {
        // �ki rastgele say� 
        int rowobstacle = distribution(generator);
        int colobstacle = distribution(generator);

        //RANDOM ENGEL YERLE�T�RME
        if (rowobstacle != 0 || colobstacle != 0 ) {
            //B�T�� �LE ENGEL �AKI�MASIN
            if (rowobstacle != frow || colobstacle != fcol) {
                visited[rowobstacle][colobstacle] = true;
                cout << "ENGEL:" << "(" << rowobstacle << ", " << colobstacle << ")" << endl;
            }
        }
        else {
            int rowobstacle1 = distribution(generator);
            int colobstacle1 = distribution(generator);
            visited[rowobstacle1][colobstacle1] = true;
            cout << "ENGEL:" << "(" << rowobstacle1 << ", " << colobstacle1 << ")" << endl;
        }
        
    }
   

}
void Graph::finish() {
    // Rastgele say� �reteci 
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, (numRows-1));
    
        // B�ti� i�in iki rastgele say� �ret. 
        frow = distribution(generator);
        fcol = distribution(generator);
        //B�T�� NOKTASINI YAZDIR
        cout << "B�T��:" << "(" << frow << "," << fcol << ")" << endl;
    


}

void Graph::DFS(int row, int col) {


   
    visited[row][col] = true;
    currentRow = row; // �u anki sat�r� g�ncelle
    currentCol = col; // �u anki s�tunu g�ncelle

        std::cout << "(" << row << ", " << col << ")" << endl;

        //�apraz kom�ular�da kontrol et
        static int dr[] = { 1,1,0,-1,-1,-1,0,1 };
        static int dc[] = { 0, 1,1,1,0,-1,-1,-1 };



        for (int dir = 0; dir < 8; ++dir) {

           
            int newRow = row + dr[dir];
            int newCol = col + dc[dir];
            //B�T�� NOKTASINA GEL�NCE B�T�R
            if (currentRow == frow && currentCol == fcol) {
                break;
            }

            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && !visited[newRow][newCol]) {

                DFS(newRow, newCol);
            }



            
        }
    
}