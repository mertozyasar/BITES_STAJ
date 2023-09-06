	#include "grid.h"
	#include "graph.h"
	#include <omp.h>

	#define COLS 40
	#define ROWS 40
	#define FBS 2.5
	bool visitedArray[40][40] = { {false} };
	bool visitedArrayiha2[40][40] = { {false} };
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

		//g1.obstacle(5);
		g1.drawGrid();
	
		g1.İHABFS(0, 0, 40, 40, 0, 40, 40, 0);
		
		
 

		//g1.runBFS(0, 0, 20, 20);
		//std::thread t2(&Grid::drawGrid, g1);
		//std::thread t1(&Grid::İHA1BFS, g1, 0, 0, 40,40);
		//std::thread t2(İHA2BFS, start_x2, start_y2, finish_x, finish_y);
		
		//t2.join();
	//	t1.join();

		
		//t2.join();

	
		//std::thread t1(&Grid::drawGrid, &g1);
	//	std::thread t2(&Grid::İHA1BFS, &g1, 0, 0, 20, 30);
		//std::thread t3(&Grid::İHA2BFS, &g1, 0, 0, 30, 10);
		//t1.join();
		//t2.join();
		//t3.join();
		
		

	
		



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

	 void Grid::İHABFS(int startrow, int startcol, int fınıshrow, int fınıshcol, int startrowiha2, int startcoliha2, int fınıshrowiha2, int fınıshcoliha2) {
	
		 struct node {
			 int x;
			 int y;
		 };
		 //2.İHA 
		 struct nodeiha2 {
			 int xiha2;
			 int yiha2;
		 };

		 std::vector<std::vector<std::pair<int, int>>> parent1(ROWS, std::vector<std::pair<int, int>>(COLS, { -5, -5 }));
		 std::vector<std::pair<int, int>> shortestPath;
		 //2.İHA
		 std::vector<std::vector<std::pair<int, int>>> parent1iha2(ROWS, std::vector<std::pair<int, int>>(COLS, { -5, -5 }));
		 std::vector<std::pair<int, int>> shortestPathiha2;
		 //kombine en kısa yol
		 std::vector<std::pair<int, int>> shortestPathCombined;

		 // 8 yöne hareket için 
		 static int dr[] = { -5, -5, -5, 0, 5, 5, 5, 0 };
		 static int dc[] = { -5, 0, 5, 5, 5, 0, -5, -5 };
		 //2.İHA 8 yöne hareket için 
		 static int driha2[] = { -5, -5, -5, 0, 5, 5, 5, 0 };
		 static int dciha2[] = { -5, 0, 5, 5, 5, 0, -5, -5 };

		 std::queue<node> q;
		 q.push({ startrow,startcol });
		 visitedArray[startrow][startcol] = true;
		 visitedArrayiha2[startrow][startcol] = true;
		 visitedArrayiha2[fınıshrow][fınıshcol] = true;
		 visitedArray[fınıshrowiha2][fınıshcoliha2] = true;
		 //2.İHA
		 std::queue<nodeiha2> qiha2;
		 qiha2.push({ startrowiha2,startcoliha2});
		 visitedArrayiha2[startrowiha2][startcoliha2] = true;
		 visitedArray[startrowiha2][startcoliha2] = true;

		//ENGEL YERLEŞTİRME
		obstacle(8);

		

		while ( !q.empty() || !qiha2.empty()) {
			int newColiha2, newRowiha2;
			if (!qiha2.empty()) {

				int xiha2 = qiha2.front().xiha2;
				int yiha2 = qiha2.front().yiha2;
				qiha2.pop();


				for (int dir = 0; dir < 8; ++dir) {
					  newRowiha2 = xiha2 + driha2[dir];
					 newColiha2 = yiha2 + dciha2[dir];
					int fınıshrowiha2_, fınıshcoliha2_, startrowiha2_, startcoliha2_;

					drawGrid();


					if (fınıshrowiha2 == 40) { fınıshrowiha2_ = 35; }
					else { fınıshrowiha2_ = fınıshrowiha2; }
					if (fınıshcoliha2 == 40) { fınıshcoliha2_ = 35; }
					else { fınıshcoliha2_ = fınıshcoliha2; }
					if (startrowiha2 == 40) { startrowiha2_ = 35; }
					else { startrowiha2_ = startrowiha2; }
					if (startcoliha2 == 40) { startcoliha2_ = 35; }
					else { startcoliha2_ = startcoliha2; }
					glColor3f(1.0, 0.0, 0.0);
					glRectd(fınıshrowiha2_, fınıshcoliha2_, fınıshrowiha2_ + 5, fınıshcoliha2_ + 5);
					glColor3f(0.0, 1.0, 0.0);
					glRectd(startrowiha2_, startcoliha2_, startrowiha2_ + 5, startcoliha2_ + 5);

					glutSwapBuffers();

					if (newRowiha2 >= 0 && newRowiha2 < 40 && newColiha2 >= 0 && newColiha2 < 40 && !visitedArrayiha2[newRowiha2][newColiha2]) {

						visitedArrayiha2[newRowiha2][newColiha2] = true;
						parent1iha2[newRowiha2][newColiha2] = { xiha2, yiha2 };
						qiha2.push({ newRowiha2,newColiha2 });
					//	Sleep(130); //  uyku
					}
					if (newRowiha2 == fınıshrowiha2 && newColiha2 == fınıshcoliha2) {
						
						glutSwapBuffers();
						shortestPathiha2.push_back({ newRowiha2, newColiha2 });
						int parentXiha2 = xiha2;
						int parentYiha2 = yiha2;
						shortestPathiha2.push_back({ parentXiha2, parentYiha2 });
						
						
						// İkinci İHA'nın en kısa yolu
						while (parentXiha2 != startrowiha2 || parentYiha2 != startcoliha2) {
							int tempXiha2 = parentXiha2;
							parentXiha2 = parent1iha2[tempXiha2][parentYiha2].first;
							parentYiha2 = parent1iha2[tempXiha2][parentYiha2].second;
							shortestPathiha2.push_back({ parentXiha2, parentYiha2 });
							shortestPathiha2.push_back({ startrowiha2,startcoliha2 });
						}
						
							for (const auto& celliha2 : shortestPathiha2) {
								glColor3f(0.0, 0.0, 1.0); // Mavi renk
								glRectd(celliha2.first, celliha2.second, celliha2.first + 5, celliha2.second + 5);
							}
							
						
						

					}
					

					else {
						glutSwapBuffers();
						glColor3f(1.0, 0.5, 0.0);
						glRectd(xiha2, yiha2, xiha2 + 5, yiha2 + 5);
					}

				}

			}

			if(!q.empty()) {
				int x = q.front().x;
				int y = q.front().y;
				q.pop();




				for (int dir = 0; dir < 8; ++dir) {
					int newRow = x + dr[dir];
					int newCol = y + dc[dir];
					int fınıshrow_, fınıshcol_, startrow_, startcol_;


					drawGrid();

					if (fınıshrow == 40) { fınıshrow_ = 35; }
					else { fınıshrow_ = fınıshrow; }
					if (fınıshcol == 40) { fınıshcol_ = 35; }
					else { fınıshcol_ = fınıshcol; }
					if (startrow == 40) { startrow_ = 35; }
					else { startrow_ = startrow; }
					if (startcol == 40) { startcol_ = 35; }
					else { startcol_ = startcol; }
					glColor3f(1.0, 0.0, 0.0);
					glRectd(fınıshrow_, fınıshcol_, fınıshrow_ + 5, fınıshcol_ + 5);
					glColor3f(0.0, 1.0, 0.0);
					glRectd(startrow_, startcol_, startrow_ + 5, startcol_ + 5);


					glutSwapBuffers();

					if (newRow >= 0 && newRow < 40 && newCol >= 0 && newCol < 40 && !visitedArray[newRow][newCol]) {

						visitedArray[newRow][newCol] = true;
						parent1[newRow][newCol] = { x, y };
						q.push({ newRow,newCol });
						Sleep(200); //  uyku
					}


					if (newRow == fınıshrow && newCol == fınıshcol) {
						
						glutSwapBuffers();
						shortestPath.push_back({ newRow, newCol });
						int parentX = x;
						int parentY = y;
						shortestPath.push_back({ parentX, parentY });

						// Geriye doğru giderek en kısa yolu takip et
						// İlk İHA'nın en kısa yolu
						while (parentX != startrow || parentY != startcol) {
							int tempX = parentX;
							parentX = parent1[tempX][parentY].first;
							parentY = parent1[tempX][parentY].second;
							shortestPath.push_back({ parentX, parentY });
						}
						
						for (const auto& cell : shortestPath) {

							glColor3f(0.8, 0.0, 1.0);
							glRectd(cell.first, cell.second, cell.first + 5, cell.second + 5);
						}
						



						//kare çizgileri belli olsun.
						drawGrid();
						glutSwapBuffers();
						

						

					}

					else {

						glutSwapBuffers();
						glColor3f(1.0, 1.0, 1.0);
						glRectd(x, y, x + 5, y + 5);


					}


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
			 if (rowobstacle == 40) { rowobstacle = 35; }
			 if (colobstacle == 40) { colobstacle = 35; }

			 //RANDOM ENGEL YERLEŞTİRME
			 if (rowobstacle != 0 || colobstacle != 0) {
				 //BİTİŞ İLE ENGEL ÇAKIŞMASIN
				 if (rowobstacle != fınıshrow || colobstacle != fınıshcol) {
					 visitedArray[rowobstacle][colobstacle] = true;
					 visitedArrayiha2[rowobstacle][colobstacle] = true;
					 glColor3f(0.0, 1.0, 1.0);
					 glRectd(rowobstacle, colobstacle, rowobstacle + 5, colobstacle + 5);
				 }
			 }
			 else {
				 int rowobstacle1 = distribution(generator) * 5;
				 int colobstacle1 = distribution(generator) * 5;
				 if (rowobstacle1 == 40) { rowobstacle1 = 35; }
				 if (colobstacle1 == 40) { colobstacle1 = 35; }
				 visitedArray[rowobstacle1][colobstacle1] = true;
				 visitedArray[rowobstacle1][colobstacle1] = true;
				 glColor3f(0.0, 1.0, 1.0);
				 glRectd(rowobstacle1, colobstacle1, rowobstacle1 + 5, colobstacle1 + 5);
			 }
		 }

	 }
	 


	 Grid::Grid() {

	 }
 
	 void Grid::İHA2BFS(int startrowiha2, int startcoliha2, int fınıshrowiha2, int fınıshcoliha2) {
		
		 struct nodeiha2 {
			 int xiha2;
			 int yiha2;
		 };
		 std::vector<std::vector<std::pair<int, int>>> parent1iha2(ROWS, std::vector<std::pair<int, int>>(COLS, { -5, -5 }));
		 std::vector<std::pair<int, int>> shortestPathiha2;
		 // 8 yöne hareket için 
		 static int dr[] = { -5, -5, -5, 0, 5, 5, 5, 0 };
		 static int dc[] = { -5, 0, 5, 5, 5, 0, -5, -5 };


		 
		 glColor3f(0.0, 1.0, 0.0);
		 glRectd(startrowiha2, startcoliha2, startrowiha2 + 5, startcoliha2 + 5);
		 std::queue<nodeiha2> qiha2;
		 qiha2.push({ startrowiha2,startcoliha2 });
		 visitedArrayiha2[startrowiha2][startcoliha2] = true;

		//obstacle(20);
	
		


		 while (!qiha2.empty()) {
			 int xiha2 = qiha2.front().xiha2;
			 int yiha2 = qiha2.front().yiha2;
			 qiha2.pop();

			 for (int dir = 0; dir < 8; ++dir) {
				 int newRowiha2 = xiha2 + dr[dir];
				 int newColiha2 = yiha2 + dc[dir];
				 int fınıshrowiha2_, fınıshcoliha2_;
				 drawGrid();
				


				 glutSwapBuffers();

				 if (newRowiha2 >= 0 && newRowiha2 < 40 && newColiha2 >= 0 && newColiha2 < 40 && !visitedArray[newRowiha2][newColiha2]) {

					 visitedArrayiha2[newRowiha2][newColiha2] = true;
					 parent1iha2[newRowiha2][newColiha2] = { xiha2, yiha2 };
					 qiha2.push({ newRowiha2,newColiha2 });
					Sleep(200); //  uyku
				 }


				 if (newRowiha2 == fınıshrowiha2 && newColiha2 == fınıshcoliha2) {

					glutSwapBuffers();
					 shortestPathiha2.push_back({ newRowiha2, newColiha2 });
					 int parentXiha2 = xiha2;
					 int parentYiha2 = yiha2;
					 shortestPathiha2.push_back({ parentXiha2, parentYiha2 });
					 // Geriye doğru giderek en kısa yolu takip et
					 while (parentXiha2 != startrowiha2 || parentYiha2 != startcoliha2) {
						 int tempX = parentXiha2;
						 parentXiha2 = parent1iha2[tempX][parentYiha2].first; // Bu satırı güncelledik
						 parentYiha2 = parent1iha2[tempX][parentYiha2].second; // Bu satırı güncelledik
						 shortestPathiha2.push_back({ parentXiha2, parentYiha2 });
					 }
					 
					 // En kısa yolu görselleştir
					 for (const auto& celliha2 : shortestPathiha2) {

						 glColor3f(0.0, 0.0, 1.0); // Mavi renk
						 glRectd(celliha2.first, celliha2.second, celliha2.first + 5, celliha2.second + 5);

					 }
					 //kare çizgileri belli olsun.
					 drawGrid();
					 glutSwapBuffers();
					 
					 return;

				 }

				 else {
					
					 glutSwapBuffers();
					 glColor3f(1.0, 0.0, 0.0);
					 glRectd(xiha2, yiha2, xiha2 + 5, yiha2 + 5);
					
					
					 
				 }



			 }



		 }

	 }

	 


