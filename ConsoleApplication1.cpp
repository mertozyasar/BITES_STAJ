
#include <iostream>
#include <clocale>
#include <vector>
#include "graph.h"
#include "libraries/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "grid.h"

using namespace std;

int main() {
    
    setlocale(LC_ALL, "Turkish");
    Grid grid(900,600);
    if (grid.getwindow() == NULL) {
        std::cout << "FAİLED TO CREATE  WİNDOW" << std::endl;
        return -1;
    }
    grid.createwindow();


    // Main while loop
    while (!glfwWindowShouldClose(grid.getwindow()))
    {
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // Delete window before ending the program
    glfwDestroyWindow(grid.getwindow());
    // Terminate GLFW before ending the program
    glfwTerminate();



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




