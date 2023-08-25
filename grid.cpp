#include "grid.h"
#include "graph.h"

#define COLS 40
#define ROWS 40
#define FBS 2.5
bool visitedArray[40][40] = { {false} };
void timer_calback(int);
void display_calback();
void reshabe_calback(int ,int );
int index = 0;
int indexy = 0;

void timer_calback(int) {
	//görüntülemeyi mümkün olan en kýsa da döndürmesi
	glutPostRedisplay();
	glutTimerFunc(1000 / FBS, timer_calback, 0);
}

void display_calback() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	Grid g1;
	g1.drawGrid();

	// Ziyaret edilen konumu iþaretle ve izle
	visitedArray[index / 5][indexy / 5] = true;

	// Daha önce ziyaret edilen konumlarý çiz
	glColor3f(0.0, 1.0, 0.0); 
	for (int x = 0; x < 40; x = x + 5) {
		for (int y = 0; y < 40; y = y + 5) {
			if (visitedArray[x / 5][y / 5]) {
				glRectd(x, y, x + 5, y + 5);
			}
		}
	}

	// Son konumu çiz
	glRectd(index, indexy, index + 5, indexy + 5);

	// Son konumu sadece bir kere çizdikten sonra ileri git
	if (index == 40 && indexy == 40) {
		return;
		
	}
	else {
		index = index + 5;
		indexy = indexy + 5;
	}

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
	glutTimerFunc(0, timer_calback, 0);
	init();
	glutMainLoop();

}
 void Grid::init() {
	 glClearColor(0.0, 0.0, 0.0, 1.0);
	 initGrid(COLS, ROWS);
 }
 void Grid::initGrid(int x, int y) {
	 gridX = x;
	 gridY = y;

 }
 void Grid::unitsquare(int x,int y) {


	 glLineWidth(2.0);
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
	 glLineWidth(3.0);
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




