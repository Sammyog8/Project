#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define SIZE 9
#define BOMBS 10

class Maps {
public:
    char map[SIZE][SIZE];
    char opened[SIZE][SIZE];
    
    Maps() {
        srand(time(NULL));
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                map[i][j] = ' ';
                opened[i][j] = '*';
            }
        }
        placebombs();
    }
        
    void placebombs() {
        int bombs_placed = 0;
        while (bombs_placed < BOMBS) {
            int x = rand() % SIZE;
            int y = rand() % SIZE;
            if (map[x][y] != 'B') {
                map[x][y] = 'B';
                bombs_placed++;
            }
        }
    }

    void printmap() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                cout << opened[i][j] << ' ';
            }
            cout << endl;
        }
    }

    int checkbomb(int x, int y) {
        return map[x][y] == 'B';
    }
    
    int countbombs(int x, int y) {
        int bomb_count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int X = x + i;
                int Y = y + j;
                if (X >= 0 && X < SIZE && Y >= 0 && Y < SIZE && map[X][Y] == 'B') {
                    bomb_count++;
                }
            }
        }
        return bomb_count;
    }

    void revealbombs() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (map[i][j] == 'B') {
                    opened[i][j] = 'B';
                }
            }
        }
    }

    void reveal(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || opened[x][y] != '*') 
			return;

        int bomb_count = countbombs(x, y);
        if (bomb_count > 0) {
            opened[x][y] = bomb_count + '0';
        } else {
            opened[x][y] = ' ';
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    reveal(x + i, y + j);
                }
            }
        }
    }
};

int main() {
    Maps m;

    while (true) {
        m.printmap();
        int grid1, grid2;
        cout << "Choose a space (row and column, 0-based): ";
        cin >> grid1 >> grid2;

        if (grid1 < 0 || grid1 >= SIZE || grid2 < 0 || grid2 >= SIZE) {
            cout << "Invalid input, try again." << endl;
            continue;
        }

        if (m.checkbomb(grid1, grid2)) {
            cout << "Game Over, You Blew Up." << endl;
            m.revealbombs();
            m.printmap();
            break;
        } else {
            m.reveal(grid1, grid2);
        }

        bool won = true;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (m.opened[i][j] == '*' && m.map[i][j] != 'B') {
                    won = false;
                    break;
                }
            }
        }
        if (won) {
            cout << "Congratulations, You Win!" << endl;
            m.revealbombs();
            m.printmap();
            break;
        }
    }

    return 0;
}
