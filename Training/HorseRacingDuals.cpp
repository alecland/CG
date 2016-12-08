#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    set<int> horseSet;
    int result = 10000000;
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        if (horseSet.find(Pi) == horseSet.end())
            horseSet.insert(Pi);
        else
            result = 0;        
    }
    
    int prevValue = 0;
    set<int>::iterator it;
    for (it = horseSet.begin(); it != horseSet.end(); ++it)
    {        
        if (it != horseSet.begin())
        {
            int space = *it - prevValue;
            if (space < result)
            result = space;
        }
        prevValue = *it;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << result << endl;
}
