#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Cell
{
    public:
    bool isVisited;
    bool isEnnemy;
    bool isForbidden;
    int x;
    int y;
    
    Cell(int p_x, int p_y)
    {
        isVisited = false;
        isEnnemy = false;
        isForbidden = false;
        x = p_x;
        y = p_y;
    }
};
 
class Map
{
    public:
    int m4_dim;
    int m4_forbiddenNb;
    map<int, map<int, Cell*>> mc_grid;
    Cell* mc_myCell;
        
    Map(int p4_x, int p4_y)
    {
        m4_forbiddenNb = p4_x;
        m4_dim = p4_y;
        for(int i = 1; i <= m4_dim; i++)
        {
            for(int j = 1; j <= m4_dim; j++)
            {
                mc_grid[i][j] = new Cell(i, j);
            }
        }
    }
    
    void updateForbidden(const string& pz_up, const string& pz_down, const string& pz_left, const string& pz_right)
    {
        if (pz_up == "#" && mc_myCell->y != 1)
            mc_grid[mc_myCell->x][mc_myCell->y - 1]->isForbidden = true;
        if (pz_down == "#" && mc_myCell->y != m4_dim)
            mc_grid[mc_myCell->x][mc_myCell->y + 1]->isForbidden = true;
        if (pz_right == "#" && mc_myCell->x != m4_dim)
            mc_grid[mc_myCell->x + 1][mc_myCell->y]->isForbidden = true;
        if (pz_left == "#" && mc_myCell->x != 1)
            mc_grid[mc_myCell->x - 1][mc_myCell->y]->isForbidden = true;
    }
    
    void setMyCell(int p_x, int p_y)
    {
        mc_myCell = mc_grid[p_x][p_y];
    }
    
    void resetEnnemies()
    {
        for(int i = 1; i <= m4_dim; i++)
        {
            for(int j = 1; j <= m4_dim; j++)
            {
                mc_grid[i][j]->isEnnemy = false;
            }
        }
    }
    
    void setEnnemy(int p_x, int p_y)
    {
        mc_grid[p_x][p_y]->isEnnemy = true;
    }
};
 
int main()
{
    int firstInitInput;
    cin >> firstInitInput; cin.ignore();
    int secondInitInput;
    cin >> secondInitInput; cin.ignore();
    int thirdInitInput;
    cin >> thirdInitInput; cin.ignore();
    cerr << firstInitInput << " " << secondInitInput << " " << thirdInitInput << endl;
    int count;
    Map* mc_map = new Map(firstInitInput, secondInitInput);
    // game loop
    while (1) {
        count++;
        string firstInput;
        cin >> firstInput; cin.ignore();
        string secondInput;
        cin >> secondInput; cin.ignore();
        string thirdInput;
        cin >> thirdInput; cin.ignore();
        string fourthInput;
        cin >> fourthInput; cin.ignore();
        cerr << firstInput << secondInput << thirdInput << fourthInput << endl;
        for (int i = 0; i < thirdInitInput; i++) {
            int fifthInput;
            int sixthInput;
            mc_map->resetEnnemies();
            cin >> fifthInput >> sixthInput; cin.ignore();
            cerr << fifthInput << " " << sixthInput << endl;
            if (i != 4)
                mc_map->setEnnemy(fifthInput, sixthInput);
            else
                mc_map->setMyCell(fifthInput, sixthInput);
        }
        mc_map->updateForbidden(firstInput, thirdInput, fourthInput, secondInput);
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if (count % 2 != 0 && fourthInput == "_")
        cout << "E" << endl;
        else if (count % 3 != 0 && firstInput == "_")
        cout << "C" << endl;
        else if (count % 5 != 0 && secondInput == "_")
        cout << "A" << endl;
        else
        cout << "D" << endl;
         
    }
}
