#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
void lowerCase(string& pString)
{
    string result;
    for (int i = 0; i < pString.length(); i++)
    {
        char myChar;
        if (pString.at(i) < 'a')
            myChar = 'a' + pString.at(i) - 'A';
        else
            myChar = pString.at(i);
        result.append(1, myChar);
    }
    pString = result;
}
 
int main()
{
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    cerr << N << endl;
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    cerr << Q << endl;
    map<string, string> myMap;
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        lowerCase(EXT);

        myMap[EXT] = MT;
    }
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        getline(cin, FNAME);
        
        int dotPos = FNAME.rfind(".");
        string extension;
        if (dotPos != string::npos)  
        {
            extension = FNAME.substr(dotPos + 1);
            lowerCase(extension);
        }        
    
        string result = myMap[extension];
        if (!result.empty())
            cout << result << endl;
        else
            cout << "UNKNOWN" << endl;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
    //cout << "UNKNOWN" << endl;
}
