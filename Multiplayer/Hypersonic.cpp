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
	
	double distance2(Vec2D& p) {
	    return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
	}
	double distance2(int p_x, int p_y) {
	    return (x - p_x)*(x - p_x) + (y - p_y)*(y - p_y);
	}
};

class Grid {
    public:
    char m_map[13][11];
    int m_bestBombSpots[13][11];
    Vec2D m_playerPos[MAX_PLAYER];
    Vec2D nextMove;
    Vec2D bestMove;
    string nextAction;
    int m_myId;
    int m_maxTurnScore;
    
    Grid(int p_id) : m_myId(p_id) {}
    
    void updateRow(int p_y, string& p_row) {
        for (int i = 0; i < 13; i++) {
            m_map[i][p_y] = p_row.at(i);
        }
    }
    
    void updatePlayer(int p_owner, int p_x, int p_y, int p_param1, int p_param2) {
	    //TODO Create a Player class, and update this method
        m_playerPos[p_owner].x = p_x;
	    m_playerPos[p_owner].y = p_y;
    }	
    
    void updateBomb(int p_owner, int p_x, int p_y, int p_param1, int p_param2) {
    	//TODO Create a Bomb class and fill this method
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
	
    void computeBestMove() {
    	double closestDist = 999999.0;
    	for (int x = 0; x < 13; x++) {
            for (int y = 0; y < 11; y++) {
                if (m_bestBombSpots[x][y] == m_maxTurnScore && m_playerPos[m_myId].distance2(x, y) < closestDist) {
		            bestMove.x = x;
		            bestMove.y = y;
	                closestDist = m_playerPos[m_myId].distance2(x, y);
		        }
            }
        }
    }
	
    void setNextAction() {
        if (m_playerPos[m_myId].x == bestMove.x && m_playerPos[m_myId].y == bestMove.y) {
	        nextAction = "BOMB";
	    }
        else {
	        nextAction = "MOVE";
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
            if (entityType == 0)
	    	m_grid.updatePlayer(owner, x, y, param1, param2);
            else if (entityType == 1)
	    	m_grid.updateBomb(owner, x, y, param1, param2);
        }
	m_grid.computeBestMove();
	m_grid.setNextAction();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << m_grid.nextAction << " " << m_grid.bestMove.x << " " << m_grid.bestMove.y << endl;
    }
}
