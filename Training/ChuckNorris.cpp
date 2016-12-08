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
    string MESSAGE;
    getline(cin, MESSAGE);
    string binaryMessage;
    string chuckMessage;
    
    for (int i = 0; i < MESSAGE.length(); i++)
    {
        int curChar = MESSAGE.at(i);
        for (int j = 6; j >= 0; j--)
        {
            if (curChar >= pow(2, j))
            {
                binaryMessage.append("1");
                curChar -= pow(2, j);
            }
            else
            {
                binaryMessage.append("0");
            }
        }
    }
    cerr << binaryMessage << endl;
    int lastBinChar = -1;
    int curBinChar = 0;
    for (int i = 0; i < binaryMessage.length(); i++)
    {
        curBinChar = binaryMessage.at(i);
        cerr << "last bin: " << lastBinChar << endl;
        cerr << "Current bin: " << curBinChar << endl;
        if (curBinChar != lastBinChar)
        {
            if (!chuckMessage.empty())
            {
                chuckMessage.append(" ");
            }
            
            if (curBinChar == 48)
                chuckMessage.append("00 ");
            else
                chuckMessage.append("0 ");
                        
        }
        chuckMessage.append("0");
        cerr << chuckMessage << endl;
        lastBinChar = curBinChar;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << chuckMessage << endl;
}
