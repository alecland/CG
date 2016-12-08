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
    int width;
    int height;
    string output;
    string newline;
    cin >> width >> height; cin.ignore();
    cerr << width << endl;
    cerr << height << endl;
    vector<int> sharpCount(width);
    
    for (int i = 0; i < height; i++) {
        string line;
        cin >> line; cin.ignore();
        //cerr << line << endl;
        for (int j = 0; j < width; j++) {
            if (line.at(j) == '#')
            {
                sharpCount[j]++;
            }
        }        
    }
    for (int k = height; k > 0; k--) {
        for (int l = 0; l < width; l++)
        {
            if (sharpCount[l] >= k)
                newline.append("#");
            else
                newline.append(".");                
        }
        output.append(newline);
        output.append("\n");
        newline.clear();
    }
    

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << output ;
}
