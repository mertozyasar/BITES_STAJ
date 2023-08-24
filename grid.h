
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/glut.h>








class Grid {

private:
	int gridX=40, gridY=40;
	
public:
	Grid();
	Grid(int, int);
	void init();
	void initGrid(int, int);
	void unitsquare(int x, int y);
	void drawGrid();
	

};
