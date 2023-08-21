#include <iostream>
#include <vector>
#include "graph.h"
#include <random>
#include <thread>

using namespace std;
Graph::Graph(int rows, int cols) {



    numRows = rows;
    numCols = cols;
    grid.resize(rows, std::vector<int>(cols, 0));
    visited.resize(rows, std::vector<bool>(cols, false));
}

void Graph::obstacle(int numobstacle) {
    
    
    //Random engel yerle�tirme
    
        // Rastgele say� �reteci 
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, (numRows - 1));
        std::uniform_int_distribution<int> distribution1(0, (numCols - 1));
        for (int i = 0; i < numobstacle; i++) {
            // �ki rastgele say� 
            int rowobstacle = distribution(generator);
            int colobstacle = distribution1(generator);

            //RANDOM ENGEL YERLE�T�RME
            if (rowobstacle != 0 || colobstacle != 0) {
                //B�T�� �LE ENGEL �AKI�MASIN
                if (rowobstacle != frow || colobstacle != fcol) {
                    visited[rowobstacle][colobstacle] = true;
                    cout << "ENGEL:" << "(" << rowobstacle << ", " << colobstacle << ")" << endl;
                }
            }
            else {
                int rowobstacle1 = distribution(generator);
                int colobstacle1 = distribution(generator);
                visited[rowobstacle1][colobstacle1] = true;
                cout << "ENGEL:" << "(" << rowobstacle1 << ", " << colobstacle1 << ")" << endl;
            }

        }
    /*
    visited[1][1] = true;
    visited[1][2] = true;
    visited[2][1] = true;
    visited[3][1] = true;
    visited[4][1] = true;*/
    
}
void Graph::finish() {
    //Rastgele biti� veriyor.
    
    // Rastgele say� �reteci 
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, (numRows-1));
    std::uniform_int_distribution<int> distribution1(1, (numCols - 1));
        // B�ti� i�in iki rastgele say� �ret. 
        frow = distribution(generator);
        fcol = distribution1(generator);
        //B�T�� NOKTASINI YAZDIR
        cout << "B�T��:" << "(" << frow << "," << fcol << ")" << endl;
    /*
    frow = 3, fcol = 3;
    cout << "B�T��:" << "(" << frow << "," << fcol << ")" << endl;*/


}

void Graph::DFS(int row, int col) {


    visited[row][col] = true;
    path.push_back(std::make_pair(row, col)); // Ge�ilen yolu kaydet

    // Hedef noktaya ula��ld���nda DFS i�lemi sonland�r�l�r
    if (row == frow && col == fcol) {
        for (const auto& point : path) {
            std::cout << "(" << point.first << ", " << point.second << ")" << std::endl;
        }
        return;
    }

    // �apraz kom�ular� da kontrol et
    static int dr[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    static int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    for (int dir = 0; dir < 8; ++dir) {
        int newRow = row + dr[dir];
        int newCol = col + dc[dir];

        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && !visited[newRow][newCol]) {
            DFS(newRow, newCol);
        }
    }

    // Geri d�nd���m�zde bu h�creyi ziyaret etmemi� kabul ediyoruz
    visited[row][col] = false;
    path.pop_back(); // Ge�ilen yoldan ��kar
    
}




void Graph::BFS(int srow, int scol) {
    struct node {
        int x;
        int y;
    };
    vector<vector<pair<int, int>>> came_from1(numCols, vector<pair<int, int>>(numRows, make_pair(-1, -1)));

    // 8 y�ne hareket i�in 
    static int dr1[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    static int dc1[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    queue<node> q;
    q.push({ srow, scol });
    visited[srow][scol] = true;
    vector<pair<int, int>> reverse_path;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
     
        
        for (int dir1 = 0; dir1 < 8; ++dir1) {
            int newrow = x + dr1[dir1];
            int newcol = y + dc1[dir1];
            if (newrow >= 0 && newrow < numRows && newcol >= 0 && newcol < numCols && !visited[newrow][newcol]) {
                came_from1[newrow][newcol] = make_pair(x, y);
                visited[newrow][newcol] = true;
                q.push({ newrow, newcol });
            }

            if (newrow == frow && newcol == fcol) {
                // Hedefe ula��ld���nda yolu takip et
                int currRow = frow;
                int currCol = fcol;
                while (currRow != srow || currCol != scol) {
                     reverse_path.push_back(make_pair(currRow, currCol));
                    pair<int, int> parent1 = came_from1[currRow][currCol];
                    currRow = parent1.first;
                    currCol = parent1.second;
                }
                reverse_path.push_back(make_pair(srow, scol));

                // Yolu tersten yazd�r
                for (int i = reverse_path.size() - 1; i >= 0; --i) {
                    cout << "(" << reverse_path[i].first << ", " << reverse_path[i].second << ")" << endl;
                }

                return; // D�ng�y� sonland�r
            }
        }
    }
    cout << "Hedefe ula��lamad�!" << endl;
}



void Graph::AStar() {
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> open_list;

    vector<vector<double>> g_cost(numRows, vector<double>(numCols, numeric_limits<double>::infinity()));
    vector<vector<pair<int, int>>> came_from(numRows, vector<pair<int, int>>(numCols, make_pair(-1, -1)));

    g_cost[currentRow][currentCol] = 0;
    double h_cost = abs(currentRow - frow) + abs(currentCol - fcol);
    open_list.push(make_pair(h_cost, make_pair(currentRow, currentCol)));
    // 8 y�ne hareket i�in 
    static int dr[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    static int dc[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    while (!open_list.empty()) {
        int row = open_list.top().second.first;
        int col = open_list.top().second.second;
        open_list.pop();

        if (row == frow && col == fcol) {
            // Yolu geri izleyerek bulundu�umuz h�creden ba�layarak biti�e kadar olan yolu hesapla
            vector<pair<int, int>> path;
            while (row != -1 && col != -1) {
                path.push_back(make_pair(row, col));
                pair<int, int> temp = came_from[row][col];
                row = temp.first;
                col = temp.second;
            }
            reverse(path.begin(), path.end());

            // Bulunan yolu yazd�r
            for (const auto& point : path) {
                cout << "(" << point.first << ", " << point.second << ")" << endl;
            }

            return;
        }

        for (int dir = 0; dir < 8; ++dir) {
            int newRow = row + dr[dir];
            int newCol = col + dc[dir];

            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && !visited[newRow][newCol]) {
                if (newRow == row || newCol == col) {
                    //4 y�n ad�m maliyeti 10
                    tentative_g_cost = g_cost[row][col] + 10;
                }
                else {
                    //�apraz ad�m maliyeti 14
                    tentative_g_cost = g_cost[row][col] + 14;
                }
                if (tentative_g_cost < g_cost[newRow][newCol]) {
                    came_from[newRow][newCol] = make_pair(row, col);
                    g_cost[newRow][newCol] = tentative_g_cost;
                    double h_cost = abs(newRow - frow) + abs(newCol - fcol);
                    double f_cost = tentative_g_cost + h_cost;
                    open_list.push(make_pair(f_cost, make_pair(newRow, newCol)));
                }
            }
        }
    }

    cout << "Hedefe ula��lamad�!" << endl;
}






