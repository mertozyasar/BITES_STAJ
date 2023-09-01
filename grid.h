
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <queue>
#include <random>



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
	void bfsGrid(int, int, int, int);
	 void obstacle(int);

	

};
