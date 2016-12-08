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
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);
    cerr << temps << endl;
    
    int sepPos = temps.find(" ");
    string remainingTemps(temps);
    int result = atoi(remainingTemps.substr(0, sepPos).c_str());
    while (sepPos != string::npos)
    {
        int temp = atoi(remainingTemps.substr(0, sepPos).c_str());
        if (abs(temp) < abs(result))
        {
            result = temp;
        }
        else if (abs(temp) == abs(result)
        && temp > result)
        {
            result = temp;
        }
        remainingTemps.assign(remainingTemps.substr(sepPos + 1));
        sepPos = remainingTemps.find(" ");
        cerr << remainingTemps << endl;
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << result << endl;
}
