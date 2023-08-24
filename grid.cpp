#include "grid.h"

#define COLS 40
#define ROWS 40

void display_calback();
void reshabe_calback(int ,int );
void Grid::init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLS, ROWS);
}

void display_calback() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	Grid g1;
	g1.drawGrid();
	glutSwapBuffers();
}
void reshabe_calback(int w, int h) {
	//her yenilendiðinde görüntüyü ayarlar boyut
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//prpjeksiyon matrixine geçer
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//ortografi matrix
	glOrtho(0.0, COLS, 0.0, ROWS, -1.0, 1.0);
	//geri model matrixine döndü
	glMatrixMode(GL_MODELVIEW);
}

 Grid::Grid(int w, int h) {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("PATHFINDING");
	glutDisplayFunc(display_calback);
	glutReshapeFunc(reshabe_calback);
	init();
	glutMainLoop();

}
 void Grid::initGrid(int x, int y) {
	 gridX = x;
	 gridY = y;

 }
 void Grid::unitsquare(int x,int y) {


		 glLineWidth(1.0);
		 glColor3f(1.0, 1.0, 1.0);
	 


	 glBegin(GL_LINE_LOOP);
	 glVertex2f(x, y);
	 glVertex2f(x + 5, y);
	 glVertex2f(x + 5, y + 5);
	 glVertex2f(x, y + 5);

	 glEnd();

 }
 void Grid::drawGrid() {
	
	 // Ýç çerçeve çizimi
	 for (int row = 0; row < ROWS; row = row + 5) {
		 for (int col = 0; col < COLS; col = col + 5) {
			 unitsquare(row, col);
		 }
	 }

	 // Dýþ çerçeve çizimi (kýrmýzý renk)
	 glLineWidth(7.0);
	 glColor3f(1.0, 0.0, 0.0);

	 glBegin(GL_LINE_LOOP);
	 glVertex2f(0, 0);
	 glVertex2f(COLS, 0);
	 glVertex2f(COLS, ROWS);
	 glVertex2f(0, ROWS);
	 glEnd();
		

	
 }
 Grid::Grid() {

 }




