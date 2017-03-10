#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int w; // width of the board
    int h; // height of the board
    int playerCount; // number of players (2 or 3)
    int myId; // id of my player (0 = 1st player, 1 = 2nd player, ...)
    int opX;
    int opY;
    int turn = 0;
    cin >> w >> h >> playerCount >> myId; cin.ignore();

    // game loop
    while (1) {
        turn++;
        for (int i = 0; i < playerCount; i++) {
            int x; // x-coordinate of the player
            int y; // y-coordinate of the player
            int wallsLeft; // number of walls available for the player
            cin >> x >> y >> wallsLeft; cin.ignore();
            if (i != myId) {
                opX = x;
                opY = y;
            }
            
        }
        int wallCount; // number of walls on the board
        cin >> wallCount; cin.ignore();
        for (int i = 0; i < wallCount; i++) {
            int wallX; // x-coordinate of the wall
            int wallY; // y-coordinate of the wall
            string wallOrientation; // wall orientation ('H' or 'V')
            cin >> wallX >> wallY >> wallOrientation; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // action: LEFT, RIGHT, UP, DOWN or "putX putY putOrientation" to place a wall
        if (myId == 0)
            if (turn == 3)
                cout << "1 " << opY << " " << "V" << endl;
            else
                cout << "RIGHT" << endl;
        else
            if (turn == 3)
                cout << w - 1 << " " << opY << " " << "V" << endl;
            else
                cout << "LEFT" << endl;
    }
}
