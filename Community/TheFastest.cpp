#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Time
{
    string hours = "";
    string minutes = "";
    string seconds = "";
};
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    Time result;
    Time input;
    result.hours = "25";
    for (int i = 0; i < N; i++) {
        string t;
        cin >> t; cin.ignore();
        input.hours = t.substr(0, 2);
        input.minutes = t.substr(3, 2);
        input.seconds = t.substr(6);
        if (stoi(input.hours) < stoi(result.hours) ||
        (stoi(input.hours) == stoi(result.hours) && stoi(input.minutes) < stoi(result.minutes)) ||
        (stoi(input.hours) == stoi(result.hours) && stoi(input.minutes) == stoi(result.minutes) && stoi(input.seconds) < stoi(result.seconds)))
        {
            result = input;
        }        
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << result.hours << ":" << result.minutes << ":" << result.seconds << endl;
}
