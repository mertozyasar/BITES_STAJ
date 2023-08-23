#include "grid.h"

void display_calback();
void reshabe_calback(int ,int );
void Grid::init() {
	glClearColor(1.0, 0.0, 0.0, 1.0);
}

void display_calback() {

	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
}
void reshabe_calback(int w, int h) {
	//her yenilendiðinde görüntüyü ayarlar boyut
	glViewport(0, 0, w, h);
	//prpjeksiyon matrixine geçer
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//ortografi matrix
	glOrtho(0.0, 40.0, 0.0, 40.0, -1.0, 1.0);
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





