#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

enum Direction {
	SOUTH = 0,
	EAST = 1,
	NORTH = 2,
	WEST = 3
};

struct Position
{
	int x;
	int y;
};

class Robot
{
public:
	Direction dir;
	char currentPlace;
	int nbMoves;
	int nbCol;
	int nbLines;
	bool isBreaker;
	bool isReversed;
	bool isStuck;
	bool isDead;
	Position pos;
	map<int, map<int, char>> grid;
	map<Direction, string> dirMap;
	vector<Direction> result;
	map<Direction, bool> testedDir;

	Robot(int L, int C) : isBreaker(false), isReversed(false), isStuck(false), nbMoves(0), dir(SOUTH), currentPlace('@'), nbCol(C), nbLines(L), isDead(false)
	{
		dirMap[SOUTH] = "SOUTH";
		dirMap[EAST] = "EAST";
		dirMap[NORTH] = "NORTH";
		dirMap[WEST] = "WEST";

		resetTestedDir();
	}

	void resetTestedDir()
	{
		testedDir[SOUTH] = false;
		testedDir[EAST] = false;
		testedDir[NORTH] = false;
		testedDir[WEST] = false;
	}

	void play()
	{
		cerr << nbMoves << endl;
		move(dir);
		update();
	}

	void move(Direction currentDir)
	{
		bool isMoveOK = false;
		char target;
		int x = pos.x;
		int y = pos.y;
		switch (currentDir)
		{
		case SOUTH:
			y++;
			break;
		case EAST:
			x++;
			break;
		case NORTH:
			y--;
			break;
		case WEST:
			x--;
			break;
		}
		cerr << x << " " << y << endl;
		target = grid[x][y];
		if (!isMoveAuthorized(target))
		{
			testedDir[currentDir] = true;			
			int nextDir = -1;
			
			if (isReversed) {
				for (int i = 3; i >= 0; --i) {
					if (!testedDir[(Direction)i]) {
						nextDir = i;
						break;
					}						
				}
			}
			else {
				for (int i = 0; i <= 3; ++i) {
					if (!testedDir[(Direction)i]) {
						nextDir = i;
						break;
					}
				}
			}

			if (nextDir != -1)
			{
				move((Direction)nextDir);
			}
			else
			{
				isStuck = true;
				return;
			}
				
		}
		else
		{
			dir = currentDir;
			currentPlace = target;
			pos.x = x;
			pos.y = y;
		}

	}

	void update()
	{
		result.push_back(dir);
		resetTestedDir();
		nbMoves++;
		switch (currentPlace)
		{
		case 'X':
			if (isBreaker) {
				grid[pos.x][pos.y] = ' ';
			}
			break;
		case 'B':
			isBreaker = !isBreaker;
			break;
		case 'I':
			isReversed = !isReversed;
			break;
		case 'N':
			dir = NORTH;
			break;
		case 'S':
			dir = SOUTH;
			break;
		case 'W':
			dir = WEST;
			break;
		case 'E':
			dir = EAST;
			break;
		case 'T':
			goToTeleport();
			break;
		case '$':
			isDead = true;
			break;
		}		
		if (nbMoves > nbCol * nbLines * 5)
		{
			isStuck = true;
		}
	}

	bool isMoveAuthorized(char target)
	{
		switch (target)
		{
		case '#':
			return false;
		case 'X':
			return isBreaker;
		default:
			return true;
		}
	}

	void goToTeleport()
	{
		for (int i = 0; i < nbCol; i++) {
			for (int j = 0; j < nbLines; j++) {				
				if (grid[i][j] == 'T' && (i != pos.x || j != pos.y)) {
					pos.x = i;
					pos.y = j;
					return;
				}
			}
		}
	}

	string printResult()
	{
		string printedResult;
		if (isStuck)
			printedResult.assign("LOOP");
		else
		{
			vector<Direction>::iterator it;
			for (it = result.begin(); it != result.end(); ++it)
			{
				printedResult.append(dirMap[*it]).append("\n");
			}
		}

		return printedResult;
	}
};

/**}
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
int main()
{
	// Place Bender at his starting position, populate its grid
	int L;
	int C;
	cin >> L >> C; cin.ignore();
	Robot* bender = new Robot(L, C);
	for (int i = 0; i < L; i++) {
		string row;
		getline(cin, row);
		cerr << row << endl;
		for (int j = 0; j < C; j++) {
			bender->grid[j][i] = row.at(j);
			if (row.at(j) == '@') {
				bender->pos.x = j;
				bender->pos.y = i;
			}
		}
	}

	while (!bender->isStuck && !bender->isDead)
		bender->play();

	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	cout << bender->printResult() << endl;
}
