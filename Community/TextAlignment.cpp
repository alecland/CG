#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int countSpaces(string& line)
{
    int spacePos = line.find(" ");
    if (spacePos != string::npos)
    {
        string input(line.substr(spacePos + 1));
        return 1 + countSpaces(input);
    }
    else
        return 0;
}

void printLeft(vector<string>& lines)
{
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        cout << lines[i] << endl;
    }
}

void printRight(vector<string>& lines)
{
    int maxLength = 0;
    string result;
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        if (lines[i].length() > maxLength)
            maxLength = lines[i].length();
    }
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        result.assign(maxLength - lines[i].length(), ' ');
        result.append(lines[i]);
        cout << result << endl;
    }
}

void printCenter(vector<string>& lines)
{
    int maxLength = 0;
    string result;
    int spaceNb = 0;
    int spaceBefore = 0;
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        if (lines[i].length() > maxLength)
            maxLength = lines[i].length();
    }
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        spaceNb = maxLength - lines[i].length();
        spaceBefore = spaceNb / 2;
        result.assign(spaceBefore, ' ');
        result.append(lines[i]);
        cout << result << endl;
    }
}

void printJustify(vector<string>& lines)
{
    int maxLength = 0;
    string result;
    string remainingLine;
    int spaceToAdd = 0;
    int spaceNb = 0;
    int spaceBySpace = 0;
    int remainingSpaces = 0;
    size_t spacePos = 0;
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        if (lines[i].length() > maxLength)
            maxLength = lines[i].length();
    }
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        spaceToAdd = maxLength - lines[i].length();
        spaceNb = countSpaces(lines[i]);        
        spaceBySpace = spaceToAdd/spaceNb;
        remainingSpaces = spaceToAdd - spaceBySpace * spaceNb;
        //cerr << spaceNb << " " << spaceToAdd << " " << spaceBySpace << " " << remainingSpaces << endl;
        spacePos = lines[i].find(" ");
        remainingLine = lines[i];
        result.clear();
        int count = 0;
        while (spacePos != string::npos)
        {
            result.append(remainingLine.substr(0, spacePos + 1));
            result.append(spaceBySpace, ' ');
            if (count >= spaceNb - remainingSpaces)
                result.append(1, ' ');
            remainingLine = remainingLine.substr(spacePos + 1);
            spacePos = remainingLine.find(" ");
            count++;
        }
        result.append(remainingLine);
        cout << result << endl;
    }
}

void printText(string alignment, vector<string>& lines)
{
    if (alignment.compare("LEFT") == 0)
        printLeft(lines);
    if (alignment.compare("RIGHT") == 0)
        printRight(lines);
    if (alignment.compare("CENTER") == 0)
        printCenter(lines);
    if (alignment.compare("JUSTIFY") == 0)
        printJustify(lines);        
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    vector<string> lines;
    string alignment;
    getline(cin, alignment);
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string text;
        getline(cin, text);
        lines.push_back(text);
    }
    
    printText(alignment, lines);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    
}
