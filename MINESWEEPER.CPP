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

    void printmap(char opened[SIZE][SIZE]) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (opened[i][j] != ' ') {
                    cout << opened[i][j] << ' ';
                } else {
                    cout << '*' << ' ';//change to somthing good
                }
            }
            cout << endl;
        }
    }

    int checkbomb(int x, int y) {
        if (map[x][y] == 'B') {
            return 1;
        } else {
            return 0;
        }
    }
    
    int countbombs(int x, int y) {
        int bomb_count = 0;
            for (int i = -1; i <= 1; i++) 
			{
	            for (int j = -1; j <= 1; j++) 
				{
	                if (i == 0 && j == 0) continue;
	                
	                int X = x + i;
	                int Y = y + j;
	                
	                if (X >= 0 && X < SIZE && Y >= 0 && Y < SIZE)
	                    if (map[X][Y] == 'B')
	                        bomb_count++;
            }
        }
        
        return bomb_count;
    }
    void revealbombs(char opened[SIZE][SIZE]) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (map[i][j] == 'B') {
                    opened[i][j] = 'B';  // Reveal all bombs
                }
            }
        }
    }
};
int main() {
    Maps m;
    char opened[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            opened[i][j] = ' ';
        }
    }

    int bomb;
    for (int i = 0; i < SIZE*SIZE; i++) {
        m.printmap(opened);

        int grid1, grid2;
        cout << "Choose a space (row and column, 0-based): ";
        cin >> grid1 >> grid2;

        if (grid1 < 0 || grid1 >= SIZE || grid2 < 0 || grid2 >= SIZE) {
            cout << "Invalid input, try again." << endl;
            continue;
        }

        bomb = m.checkbomb(grid1, grid2);
        if (bomb == 1) {
            cout << "Game Over, You Blew Up." << endl;
            m.revealbombs(opened);
        } else {
            int bomb_count = m.countbombs(grid1, grid2);
            opened[grid1][grid2] = bomb_count + '0';
        }
    }

    return 0;
}
