
#include <iostream>
#include <clocale>
#include <vector>
#include "graph.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "Turkish");
    int row,col,srow,scol;
    cout << "Başlangıç için satır sayısını giriniz:";
    cin >> row;
    cout << "Başlangıç için sütün sayısını sayısını giriniz:";
    cin >> col;


 


    Graph g(row, col);

    std::cout << "BAŞLANGIÇ (0, 0):" << std::endl;
    g.DFS(0, 0);
   
    

    return 0;
}




