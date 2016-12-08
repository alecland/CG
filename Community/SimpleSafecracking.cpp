#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string msg;
    getline(cin, msg);
    cerr << msg << endl;
    map<char, char> transMap;
    transMap['e'] = msg.at(2);
    transMap['f'] = msg.at(6);
    transMap['n'] = msg.at(14);
    transMap['o'] = msg.at(10);
    transMap['s'] = msg.at(4);
    transMap['t'] = msg.at(16);
    
    string code(msg.substr(25));
    string result;
    size_t sepPos = code.find("-");
    
    while (code.length() > 2) {
        cerr << code << endl;
        string digit = code.substr(0, sepPos);
        if (sepPos == string::npos)
            code.clear();
        else {
            code = code.substr(sepPos + 1);
            sepPos = code.find("-");
        }
        cerr << digit << endl;
        switch (digit.length()) {
            case 3:
                if (digit.at(0) == transMap['s'])
                    result.append(1, '6');
                else if (digit.at(0) == transMap['t'])
                    result.append(1, '2');
                else if (digit.at(0) == transMap['o'])
                    result.append(1, '1');
                break;
            case 4:
                if (digit.at(3) == transMap['o'])
                    result.append(1, '0');
                else if (digit.at(0) == transMap['n'])
                    result.append(1, '9');
                else if (digit.at(3) == transMap['e'])
                    result.append(1, '5');
                else 
                    result.append(1, '4');
                break;
            case 5:
                if (digit.at(0) == transMap['t'])
                    result.append(1, '3');
                else if (digit.at(0) == transMap['s'])
                    result.append(1, '7');
                else if (digit.at(0) == transMap['e'])
                    result.append(1, '8');
                break;
        }
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << result << endl;
}
