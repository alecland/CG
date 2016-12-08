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
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    string answer;
    
    for (int i = 0; i < H; i++) {
        string ROW;
        string line;
        getline(cin, ROW);
        //cerr << ROW << endl;
        for (int j = 0; j < T.length(); j++)
        {
            int pos = ROW.length() - L;
            
            if (T.at(j) >= 97)
                pos = (T.at(j) - 97) * L;
            else if (T.at(j) >= 65)
                pos = (T.at(j) - 65) * L;
          
            cerr << pos << endl;    
            line.append(ROW.substr(pos, L));
        }
        cerr << line << endl;
        answer.append(line);
        answer.append("\n");
    }
    
    cerr << L << endl;
    cerr << H << endl;
    cerr << T << endl;
  

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << answer << endl;
}
