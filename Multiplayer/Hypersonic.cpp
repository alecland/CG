#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define BOMB_RANGE 2
#define MAX_PLAYER 2

class Vec2D {
public:
	int x;
	int y;

	Vec2D(int p_x, int p_y) : x(p_x), y(p_y) {}
	Vec2D() : x(0), y(0) {}
};

class Grid {
    public:
    char m_map[13][11];
    int m_bestBombSpots[13][11];
    Vec2D m_playerPos[MAX_PLAYER];
    Vec2D nextMove;
    int m_myId;
    int m_maxTurnScore;
    
    Grid(int p_id) : m_myId(p_id) {}
    
    void updateRow(int p_y, string& p_row) {
        for (int i = 0; i < 13; i++) {
            m_map[i][p_y] = p_row.at(i);
        }
    }
    
    void fillBestSpots() {
        m_maxTurnScore = 0;
        for (int x = 0; x < 13; x++) {
            for (int y = 0; y < 11; y++) {
                m_bestBombSpots[x][y] = 0;
                if (m_map[x][y] == '.') {
                    if ((x - 1) >= 0 && m_map[x - 1][y] == '0' || (x - 2) >= 0 && m_map[x - 2][y] == '0')
                        m_bestBombSpots[x][y]++;
                    if ((x + 1) < 13 && m_map[x + 1][y] == '0' || (x + 2) < 13 && m_map[x + 2][y] == '0')
                        m_bestBombSpots[x][y]++;
                    if ((y - 1) >= 0 && m_map[x][y - 1] == '0' || (y - 2) >= 0 && m_map[x][y - 2] == '0')
                        m_bestBombSpots[x][y]++;
                    if ((y + 1) < 11 && m_map[x][y + 1] == '0' || (y + 2) < 11 && m_map[x][y + 2] == '0')
                        m_bestBombSpots[x][y]++;
                } 
                if (m_bestBombSpots[x][y] > m_maxTurnScore)
                    m_maxTurnScore = m_bestBombSpots[x][y];
            }
        }
    }
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    
    int width;
    int height;
    int myId;
    
    cin >> width >> height >> myId; cin.ignore();
    Grid m_grid(myId);

    // game loop
    while (1) {
        for (int i = 0; i < height; i++) {
            string row;
            cin >> row; cin.ignore();
            m_grid.updateRow(i, row);
        }
        
        m_grid.fillBestSpots();
        int entities;
        cin >> entities; cin.ignore();
        for (int i = 0; i < entities; i++) {
            int entityType;
            int owner;
            int x;
            int y;
            int param1;
            int param2;
            cin >> entityType >> owner >> x >> y >> param1 >> param2; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "BOMB 6 5" << endl;
    }
}
