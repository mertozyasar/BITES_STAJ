
#include <iostream>
#include <clocale>
#include <vector>
#include "graph.h"
#include "libraries/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "grid.h"
#include <thread>



using namespace std;

int main(int argc,char **argv) {
    
    setlocale(LC_ALL, "Turkish");
    //PENCERE AÇTI
    glutInit(&argc, argv);
    Grid g(500,500);

    
  
    /*
    int row , col ;

    //Kullanıcıdan array satır sutun isteme
    do {
        cout << "satır sayısını giriniz:";
        cin >> row;
        cout << "sütün sayısını sayısını giriniz:";
        cin >> col;
    } while (row <= 1 || col <=1);
    
    

    std::cout << "BAŞLANGIÇ (0, 0):" << std::endl;
    
    Graph g(row, col);
    g.finish();
    g.obstacle(row);

    //A*  SEARCH ALGORİTMASI İLE EN KISA YOLU BULMA
    std::cout << " A* SEARCH İLE GİDİLEN YOL:" << endl;
     g.AStar();

    //DFS ALGORİTMASI İLE TARAMA
   // std::cout << " DFS İLE GİDİLEN YOL:" << endl;
  //g.DFS(0, 0);

    //BFS ALGORİTMASI İLE GİTME
 //  std::cout << " BFS İLE GİDİLEN YOL:" << endl;
  // g.BFS(0,0);
  
    */

    return 0;
}




