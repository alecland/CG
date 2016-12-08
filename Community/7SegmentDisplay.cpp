#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

void buildNumber(string& N, string& C)
{
    while (!N.empty())
    {
        
    }
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string N;
    cin >> N; cin.ignore();
    string C;
    getline(cin, C);
    if (C.length() == 2)
        C.assign(C.substr(C.length()));
    int S;
    cin >> S; cin.ignore();
    int width = S + 2;
    int height = 2 * S + 3;
    map<int, string> lines;
    bool isDotPresent = false;

    while (!N.empty())
    {
        for (int lineCount = 0; lineCount < height; lineCount++)
        {
            if (lineCount == 0)
            {              
                switch (N.at(0))
                {
                    case '1':                       
                        lines[lineCount].append(S + 2, ' ');
                        //lines[lineCount].append(C);
                        break;
                    case '4':
                        //lines[lineCount].append(C);
                        lines[lineCount].append(S + 2, ' ');
                        //lines[lineCount].append(C);
                        break;
                    default:
                        lines[lineCount].append(1, ' ');
                        lines[lineCount].append(S, C.at(0));
                        lines[lineCount].append(1, ' ');
                        break;
                }
                if (N.length() > 1)
                lines[lineCount].append(1, ' ');
            }
            else if (lineCount < S + 1)
            {
                switch (N.at(0))
                {
                    case '1':
                    case '2':
                    case '3':
                    case '7':
                        lines[lineCount].append(S + 1, ' ');
                        lines[lineCount].append(1, C.at(0));
                        break;
                    case '6':
                    case '5':
                        lines[lineCount].append(1, C.at(0));
                        lines[lineCount].append(S + 1, ' ');                        
                        break;
                    default:
                        lines[lineCount].append(1, C.at(0));
                        lines[lineCount].append(S, ' ');
                        lines[lineCount].append(1, C.at(0));
                        break;
                }
                if (N.length() > 1)
                lines[lineCount].append(1, ' ');
            }
            else if (lineCount == S + 1)
            {               
                switch (N.at(0))
                {
                    case '1':
                    case '7':
                    case '0':
                        lines[lineCount].append(S + 2, ' ');
                        //lines[lineCount].append(1, C.at(0));
                        break;
                    //case '0':
                    //    lines[lineCount].append(1, C.at(0));
                    //    lines[lineCount].append(S, ' ');
                    //    lines[lineCount].append(1, C.at(0));
                    //    break;
                    default:
                        lines[lineCount].append(1, ' ');
                        lines[lineCount].append(S, C.at(0));
                        lines[lineCount].append(1, ' ');
                        break;
                }
                if (N.length() > 1)
                lines[lineCount].append(1, ' ');
            }
            else if (lineCount < height - 1)
            {
                switch (N.at(0))
                {
                    case '2':
                        lines[lineCount].append(1, C.at(0));
                        lines[lineCount].append(S + 1, ' ');                        
                        break;
                    case '6':
                    case '0':
                    case '8':
                        lines[lineCount].append(1, C.at(0));
                        lines[lineCount].append(S, ' ');
                        lines[lineCount].append(1, C.at(0));                                                
                        break;
                    default:
                        lines[lineCount].append(S + 1, ' ');
                        lines[lineCount].append(1, C.at(0));
                        break;
                }
                if (N.length() > 1)
                lines[lineCount].append(1, ' ');
            }
            else if (lineCount == height - 1)
            {               
                switch (N.at(0))
                {
                    case '1':
                    case '7':
                    case '4':
                        lines[lineCount].append(S + 2, ' ');
                        //lines[lineCount].append(1, C.at(0));
                        break;
                    default:
                        lines[lineCount].append(1, ' ');
                        lines[lineCount].append(S, C.at(0));
                        lines[lineCount].append(1, ' ');
                        break;
                }
                if (N.length() > 1)
                lines[lineCount].append(1, ' ');
            }
            
        }
        
        N = N.substr(1);
    }
    
    //if (lines[0].at(0) == ' ')
    //    lines[0].replace(0, 1, ".");
    
    for (int i = 0; i < height; i++)
    {
        int end = lines[i].rfind(C);
        cout << lines[i].substr(0, end + 1) << endl;
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
}
