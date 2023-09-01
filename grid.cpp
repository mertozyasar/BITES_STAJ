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
	//görüntülemeyi mümkün olan en kısa da döndürmesi
	glutPostRedisplay();
	glutTimerFunc(1000 / FBS, timer_calback, 0);
}

void display_calback() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	Grid g1;
	g1.drawGrid();

	
	g1.bfsGrid(0, 0,30,20);
	
	
	

}
void reshabe_calback(int w, int h) {
	//her yenilendiğinde görüntüyü ayarlar boyut
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
	 glColor3f(1.0, 0.0, 1.0);

	 glBegin(GL_LINE_LOOP);
	 glVertex2f(x, y);
	 glVertex2f(x + 5, y);
	 glVertex2f(x + 5, y + 5);
	 glVertex2f(x, y + 5);
	 

	 glEnd();

 }
 void Grid::drawGrid() {
	
	 // İç çerçeve çizimi
	 for (int row = 0; row < ROWS; row = row + 5) {
		 for (int col = 0; col < COLS; col = col + 5) {
			 unitsquare(row, col);
		 }
	 }

	 // Dış çerçeve çizimi (kırmızı renk)
	 glLineWidth(3.0);
	 glColor3f(1.0, 0.0, 0.0);

	 glBegin(GL_LINE_LOOP);
	 glVertex2f(0, 0);
	 glVertex2f(COLS, 0);
	 glVertex2f(COLS, ROWS);
	 glVertex2f(0, ROWS);
	 glEnd();


	
 }
 void Grid::bfsGrid(int startrow, int startcol, int fınıshrow, int fınıshcol) {
	 struct node {
		 int x;
		 int y;
	 };
	 std::vector<std::vector<std::pair<int, int>>> parent1(ROWS, std::vector<std::pair<int, int>>(COLS, { -5, -5 }));
	 std::vector<std::pair<int, int>> shortestPath;
	 // 8 yöne hareket için 
	 static int dr[] = { -5, -5, -5, 0, 5, 5, 5, 0 };
	 static int dc[] = { -5, 0, 5, 5, 5, 0, -5, -5 };

	 
	 
	 glColor3f(0.0, 1.0, 0.0);
	 glRectd(startrow, startcol, startrow + 5, startcol + 5);
	 std::queue<node> q;
	 q.push({ startrow,startcol });
	 visitedArray[startrow][startcol] = true;
	
		obstacle(5);
		
	
	

	 while (!q.empty()) {
		 int x = q.front().x;
		 int y = q.front().y;
		 q.pop();

		 for (int dir = 0; dir < 8; ++dir) {
			 int newRow = x + dr[dir];
			 int newCol = y + dc[dir];
			 int fınıshrow_, fınıshcol_;
			 drawGrid();

			glColor3f(1.0, 0.0, 0.0);
			if (fınıshrow == 40) { fınıshrow_ = 35; }
			else { fınıshrow_ = fınıshrow; }
			if (fınıshcol == 40) { fınıshcol_ = 35; }
			else { fınıshcol_ = fınıshcol; }
			glRectd(fınıshrow_, fınıshcol_, fınıshrow_ + 5, fınıshcol_ + 5);
	
			glColor3f(0.0, 1.0, 0.0);

			glRectd(startrow, startcol, startrow + 5, startcol + 5);
			
			glutSwapBuffers();

			 if (newRow >= 0 && newRow < 40 && newCol >= 0 && newCol < 40 && !visitedArray[newRow][newCol]) {
				 
				 visitedArray[newRow][newCol] = true;
				 parent1[newRow][newCol] = { x, y };
				 q.push({ newRow,newCol });
				Sleep(100); // 300ms uyku
			 }


			 if (newRow == fınıshrow && newCol == fınıshcol) {
				 glutSwapBuffers();
				 shortestPath.push_back({ newRow, newCol });
				 int parentX = x;
				 int parentY = y;
				 shortestPath.push_back({ parentX, parentY });
				 // Geriye doğru giderek en kısa yolu takip et
				 while (parentX != startrow || parentY != startcol) {
					 int tempX = parentX;
					 parentX = parent1[tempX][parentY].first; // Bu satırı güncelledik
					 parentY = parent1[tempX][parentY].second; // Bu satırı güncelledik
					 shortestPath.push_back({ parentX, parentY });
				 }
				 
				 // En kısa yolu görselleştir
				 for (const auto& cell : shortestPath) {

					 glColor3f(0.0, 0.0, 1.0); // Mavi renk
					 glRectd(cell.first, cell.second, cell.first + 5, cell.second + 5);
					 
				 }
				 glutSwapBuffers();
				 
				 return;
			 }
			 
			 else {
				
				 glutSwapBuffers();
				 glColor3f(1.0, 1.0, 1.0);
				 glRectd(x, y, x + 5, y + 5);
				 
				
			 }



		 }



	 }

 }
 void Grid::obstacle(int numobstacle) {
	 // Rastgele sayı üreteci
	 std::random_device rd;
	 std::mt19937 generator(rd());
	 std::uniform_int_distribution<int> distribution(0, (39 / 5));
	 std::uniform_int_distribution<int> distribution1(0, (39 / 5));
	 for (int i = 0; i < numobstacle; i++) {
		 // İki rastgele sayı 
		 int rowobstacle = distribution(generator) * 5;
		 int colobstacle = distribution1(generator) * 5;

		 //RANDOM ENGEL YERLEŞTİRME
		 if (rowobstacle != 0 || colobstacle != 0) {
			 //BİTİŞ İLE ENGEL ÇAKIŞMASIN
			 if (rowobstacle != fınıshrow || colobstacle != fınıshcol) {
				 visitedArray[rowobstacle][colobstacle] = true;
				 glColor3f(0.0, 1.0, 1.0);
				 glRectd(rowobstacle, colobstacle, rowobstacle + 5, colobstacle + 5);
			 }
		 }
		 else {
			 int rowobstacle1 = distribution(generator) * 5;
			 int colobstacle1 = distribution(generator) * 5;
			 visitedArray[rowobstacle1][colobstacle1] = true;
			 glColor3f(0.0, 1.0, 1.0);
			 glRectd(rowobstacle, colobstacle, rowobstacle + 5, colobstacle + 5);
		 }
	 }
 }
	 


 Grid::Grid() {

 }




