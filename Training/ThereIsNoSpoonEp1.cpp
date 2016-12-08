#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<sstream>
#include<iostream>

using namespace std;

string itos(int i)// convert int to string 
{ 
    stringstream s; 
    s << i; 
    return s.str(); 
} 

class Node
{
    public:
    int x;
    int y;
    bool isDone;
    
    Node(int p_x, int p_y)
    {
        x = p_x;
        y = p_y;
        isDone = false;
    }
};

class Grid
{
    public:
    vector<Node*> grid;
    int width;
    int heigth;
    int currentIndex;
    
    Grid(int p_width, int p_heigth)
    {
        width = p_width;
        heigth = p_heigth;
        grid.clear();
        currentIndex = -1;
    }
    
    void add(int p_x, int p_y)
    {
        grid.push_back(new Node(p_x, p_y));
    }
    
    void dump()
    {
        for (int i = 0; i < grid.size(); i++)
        {
            cerr << "(" << grid[i]->x << ", " << grid[i]->y << ")" << endl;
        }
    }
    
    Node* getBotClosest(int p_x, int p_y)
    {
        int closestY = heigth;
        int foundIndex = -1;
        for (int i = 0; i < grid.size(); i++)
        {
            if (grid[i]->x == p_x)
            {
                if (grid[i]->y - p_y < closestY && grid[i]->y - p_y > 0)
                {
                    closestY = grid[i]->y - p_y;
                    foundIndex = i;
                }
            }
        }
        
        if (foundIndex != -1)
            return grid[foundIndex];
        else
            return NULL;
    }
    
    Node* getRightClosest(int p_x, int p_y)
    {
        cerr << "getRightClosest" << endl;
        int closestX = width;
        int foundIndex = -1;
        for (int i = 0; i < grid.size(); i++)
        {            
            cerr << "my y = " << p_y << "tested y = " << grid[i]->y << endl;
            if (grid[i]->y == p_y)
            {
                cerr << "my x = " << p_x << "tested x = " <<grid[i]->x << endl;
                if (grid[i]->x - p_x < closestX && grid[i]->x - p_x > 0)
                {
                    cerr << "x dist = " << grid[i]->x - p_x << endl;
                    closestX = grid[i]->x - p_x;
                    foundIndex = i;
                }
            }
        }
        
        if (foundIndex != -1)
            return grid[foundIndex];
        else
            return NULL;
    }
    
    Node* getNextNode()
    {
        currentIndex++;
        
        if (currentIndex < grid.size())
            return grid[currentIndex];
        else
            return NULL;
    }   
};

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    Grid myGrid(width, height);
    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        cerr << line << endl;
        for (int j = 0; j < line.length(); j++) {
            if (line.at(j) == '0')
            {
                myGrid.add(j, i);
            }
        }
    }
    myGrid.dump();
    
    
    Node* currentNode;
    Node* closestBot = NULL;
    Node* closestRight = NULL;
    currentNode = myGrid.getNextNode();
    
    while (currentNode != NULL)
    {
        closestBot = myGrid.getBotClosest(currentNode->x, currentNode->y);
        closestRight = myGrid.getRightClosest(currentNode->x, currentNode->y);
        string result(itos(currentNode->x));
        result.append(" ");
        result.append(itos(currentNode->y));
        result.append(" ");
        if (closestRight == NULL)
        {
            result.append("-1 -1 ");
        }
        else
        {
            result.append(itos(closestRight->x));
            result.append(" ");
            result.append(itos(closestRight->y));
            result.append(" ");
        }
        if (closestBot == NULL)
        {
            result.append("-1 -1 ");
        }
        else
        {
            result.append(itos(closestBot->x));
            result.append(" ");
            result.append(itos(closestBot->y));
            result.append(" ");
        }
        cout << result << endl;
        currentNode = myGrid.getNextNode();
    }
}
