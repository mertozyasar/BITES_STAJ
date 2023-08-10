
#include <iostream>
#include <clocale>
#include <vector>
#include "graph.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "Turkish");
    int row,col;
    do {
        cout << "satır sayısını giriniz:";
        cin >> row;
        cout << "sütün sayısını sayısını giriniz:";
        cin >> col;
    } while (row <= 1 && col <=1);
    
    

    std::cout << "BAŞLANGIÇ (0, 0):" << std::endl;
  
    
    Graph g(row, col);
    g.finish();
    g.obstacle(row);
    std::cout << "GİDİLEN YOL:" << endl;
    g.DFS(0, 0);
    
   
    

    return 0;
}




