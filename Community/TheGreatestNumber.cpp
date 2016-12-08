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
    bool isNegative = false;
    bool hasDot = false;
    bool isZero = false;
    string lz_result;
    int N;
    cin >> N; cin.ignore();
    string input;
    getline(cin, input);
    cerr << input << endl;

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    size_t minusPos = input.find("-");
    if (minusPos != string::npos) {
        isNegative = true;
        input.erase(minusPos, 1);
        lz_result.append("-");
    }
    
    size_t dotPos = input.find(".");
    if (dotPos != string::npos) {
        hasDot = true;
        input.erase(dotPos, 1);
    }
    
    size_t notZeroPos = input.find_first_of("123456789");
    if (notZeroPos == string::npos) {
        isZero = true;
    }
    
    
    if (isZero) {
        lz_result = "0";
    }
    else if (isNegative) {
        for (char c = '0'; c <= '9'; c++) {
            size_t digitPos = input.find(c);
            int l4_digitCount = 0;
            while (digitPos != string::npos) {
                l4_digitCount++;
                input.erase(digitPos, 1);
                digitPos = input.find(c);
            }
            lz_result.append(l4_digitCount, c);
        }
        if (hasDot) {
            lz_result.insert(2, 1, '.');
        }
    }
    else {
        for (char c = '9'; c >= '0'; c--) {
            size_t digitPos = input.find(c);
            int l4_digitCount = 0;
            while (digitPos != string::npos) {
                l4_digitCount++;
                input.erase(digitPos, 1);
                digitPos = input.find(c);
            }
            lz_result.append(l4_digitCount, c);
        }
        if (hasDot) {
            //if (!lz_result.length() == 1) {
                size_t zeroPos = lz_result.find('0');
                if (zeroPos != string::npos) {
                    lz_result.assign(lz_result.substr(0, lz_result.length() -1));
                }
                else {
                    lz_result.assign(lz_result.substr(0, zeroPos));
                    lz_result.insert(lz_result.length() - 1, 1, '.');
                }
            //}
        }
    }
    cout << lz_result << endl;
}
