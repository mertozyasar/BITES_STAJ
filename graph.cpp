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
    

     // Rastgele sayý üreteci 
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, (numRows-1));
    for (int i = 0; i < numobstacle; i++) {
        // Ýki rastgele sayý 
        int rowobstacle = distribution(generator);
        int colobstacle = distribution(generator);

        //RANDOM ENGEL YERLEÞTÝRME
        if (rowobstacle != 0 || colobstacle != 0 ) {
            //BÝTÝÞ ÝLE ENGEL ÇAKIÞMASIN
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
    // Rastgele sayý üreteci 
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, (numRows-1));
    
        // BÝtiþ için iki rastgele sayý üret. 
        frow = distribution(generator);
        fcol = distribution(generator);
        //BÝTÝÞ NOKTASINI YAZDIR
        cout << "BÝTÝÞ:" << "(" << frow << "," << fcol << ")" << endl;
    


}

void Graph::DFS(int row, int col) {


   
    visited[row][col] = true;
    currentRow = row; // Þu anki satýrý güncelle
    currentCol = col; // Þu anki sütunu güncelle

        std::cout << "(" << row << ", " << col << ")" << endl;

        //çapraz komþularýda kontrol et
        static int dr[] = { 1,1,0,-1,-1,-1,0,1 };
        static int dc[] = { 0, 1,1,1,0,-1,-1,-1 };



        for (int dir = 0; dir < 8; ++dir) {

           
            int newRow = row + dr[dir];
            int newCol = col + dc[dir];
            //BÝTÝÞ NOKTASINA GELÝNCE BÝTÝR
            if (currentRow == frow && currentCol == fcol) {
                break;
            }

            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && !visited[newRow][newCol]) {

                DFS(newRow, newCol);
            }



            
        }
    
}