
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <queue>
#include <random>
#include <thread>



class Grid {

private:
	int gridX=40, gridY=40;
	int f�n�shrow, f�n�shcol;
	
public:
	
	Grid();
	Grid(int, int);
	void init();
	void initGrid(int, int);
	void unitsquare(int x, int y);
	void drawGrid();
	void �HABFS(int, int, int, int, int, int, int, int);
	 void obstacle(int);
	 void �HA2BFS(int, int, int, int);
	
	 bool pathsIntersected = false;

	

};
