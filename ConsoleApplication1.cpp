
#include <iostream>
#include <clocale>
#include <vector>
#include "graph.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "Turkish");
    int row,col;
    cout << "satır sayısını giriniz:";
    cin >> row;
    cout << "sütün sayısını sayısını giriniz:";
    cin >> col;


  
    
    Graph g(row, col);
    
    g.obstacle(3);
    std::cout << "BAŞLANGIÇ (0, 0):" << std::endl;
    g.DFS(0, 0);
   
    

    return 0;
}




