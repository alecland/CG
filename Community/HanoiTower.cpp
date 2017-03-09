#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class Disk {
    public:
    int radius;
    string display;
    
    Disk(int p_radius) : radius(p_radius) {
        display.append(2 * p_radius + 1, '#');
    }
};

class Axe {
    private:
    int size;
    int pos;
    stack<Disk*> tower;
    
    public:
    Axe(int p_pos, int p_size) : size(p_size), pos(p_pos) {}
    
    void push(Disk* p_disk) {
        tower.push(p_disk);
    }
    
    void pop() {
        tower.pop();
    }
    
    Disk* top() {
        return tower.top();
    }
    
    int getDiskCount() {
        return tower.size();
    }
    
    bool isEmpty() {
        return tower.empty();
    }
};

class Game {
    private:
    int diskCount;
    int displayTurn;
    int currentTurn;
    int turnsToComplete;
    bool isOutputDone;
    vector<Axe*> axes;
    
    public:
    Game (int p_count, int p_turn) : diskCount(p_count), displayTurn(p_turn), currentTurn(0), isOutputDone(false) {
        for (int i = 0; i < 3; i++) {
            Axe* l_axe = new Axe(i, p_count);
            axes.push_back(l_axe);
        }
        
        for (int i = diskCount; i > 0; i--) {
            axes[0]->push(new Disk(i));
        }
    }
    
    void play() {
        currentTurn++;
        cerr << "turn " << currentTurn << endl;
        int sourceAxe;
        int destAxe;
        // Odd turns, move the smallest disk
        if (currentTurn % 2 == 1) {
            sourceAxe = findSmallestDisk();            
            if (diskCount % 2 == 0)
                destAxe = (sourceAxe + 1) % 3;
            else
                destAxe = (sourceAxe + 2) % 3;            
            
        }
        else {
            sourceAxe = findAvailableDisk();
            destAxe = findAvailableAxe(sourceAxe);
        }
        
        Disk* l_disk = axes[sourceAxe]->top();
        axes[sourceAxe]->pop();
        axes[destAxe]->push(l_disk);
        
        if (currentTurn == displayTurn) {
            output();
        }
    }
    
    int findSmallestDisk() {
        cerr << "findSmallestDisk" << endl;
        for (int i = 0; i < 3; i++) {
            if (!axes[i]->isEmpty() && axes[i]->top()->radius == 1)
                return i;
        }
    }
    
    int findAvailableDisk() {
        cerr << "findAvailableDisk" << endl;
        int radius = 11;
        int result = -1;
        for (int i = 0; i < 3; i++) {
            if (!axes[i]->isEmpty() && axes[i]->top()->radius < radius && axes[i]->top()->radius != 1) {
                radius = axes[i]->top()->radius;
                result = i;
            }
        }
        
        return result;
    }
    
    int findAvailableAxe(int p_source) {
        cerr << "findAvailableAxe " << p_source << endl;
        for (int i = 0; i < 3; i++) {
            if (axes[i]->isEmpty() || axes[i]->top()->radius > axes[p_source]->top()->radius)
                return i;
        }
    }
    
    bool isFinished() {
        cerr << "isFinished ? " << axes[2]->getDiskCount() << endl;
        if (axes[2]->getDiskCount() == diskCount)
            cout << currentTurn << endl;
        return axes[2]->getDiskCount() == diskCount;
    }
    
    void output() {
        if (!isOutputDone) {
            string l_line;
            vector<Axe*> l_axes;
            for(int i = 0; i < 3; i++) {
                l_axes.push_back(new Axe(*axes[i]));
            }
            
            for (int i = 0; i < diskCount; i++) {
                l_line.clear();
                for (int j = 0; j < 3; j++) {
                    if (l_axes[j]->getDiskCount() < diskCount - i) {
                        l_line.append(diskCount, ' ');
                        l_line.append(1,'|');
                        
                        if (j != 2) {
                            l_line.append(diskCount, ' ');
                            l_line.append(1,' ');
                        }
                    }
                    else {
                        l_line.append(diskCount - l_axes[j]->top()->radius, ' ');
                        l_line.append(l_axes[j]->top()->display);
                        
                        
                        if (j != 2) {
                            l_line.append(diskCount - l_axes[j]->top()->radius, ' ');   
                            l_line.append(1,' ');
                        }
                        l_axes[j]->pop();
                    }
                }
                cout << l_line << endl;
            }
            isOutputDone = true;
        }
    }
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    int T;
    cin >> T; cin.ignore();
    
    Game* myGame = new Game(N, T);
    
    while (!myGame->isFinished()) {
        myGame->play();
    }
}
