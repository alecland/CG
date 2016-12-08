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
    char board[8][8];
    board['8']['a'] = '.';
    string B;
    getline(cin, B);
    
    string line;
    size_t sepPos = B.find("/");
    char lineIndex = '8';
    
    while (lineIndex > '0') {
      line = B.substr(0, sepPos);
      if (sepPos != string::npos)
        B = B.substr(sepPos + 1);
      char colIndex = 'a';
      cerr << line << endl;
      for (int i = 0; i < line.length(); i++) {
        if (line.at(i) > '0' && line.at(i) < '9') {
          for (char idx = colIndex; idx < colIndex + line.at(i) - '0'; idx++)
            board[lineIndex][idx] = '.';
          colIndex += line.at(i) - '0' - 1;
        }
        else {
          board[lineIndex][colIndex] = line.at(i);
        }
        colIndex++;
      }
      sepPos = B.find("/");      
      lineIndex--;
      colIndex = 'a';
    }    
    
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string M;        
        getline(cin, M);
        cerr << M << endl;
        if ((board[M.at(1)][M.at(0)] == 'k' || board[M.at(1)][M.at(0)] == 'K') && abs(M.at(2) - M.at(0)) > 1) {
            // Castling
            cerr << "Castling" << endl;
            if (M.at(2) - M.at(0) > 0) {
                cerr << "To the right" << endl;
                board[M.at(1)]['h'] = '.';
                board[M.at(1)][M.at(2) - 1] = board[M.at(1)][M.at(0)] + 7;
            }
            if (M.at(2) - M.at(0) < 0) {
                cerr << "To the left" << endl;
                board[M.at(1)]['a'] = '.';
                board[M.at(1)][M.at(2) + 1] = board[M.at(1)][M.at(0)] + 7;
            }
        }
        if ((board[M.at(1)][M.at(0)] == 'p' || board[M.at(1)][M.at(0)] == 'P') && abs(M.at(2) - M.at(0)) == 1 && board[M.at(3)][M.at(2)] == '.') {
            // Castling
            cerr << "En passant" << endl;
            if (M.at(3) - M.at(1) > 0) {
                cerr << "To the up" << endl;
                board[M.at(3) - 1][M.at(2)] = '.';
            }
            if (M.at(3) - M.at(1) < 0) {
                cerr << "To the down" << endl;
                board[M.at(3) + 1][M.at(2)] = '.';
            }
        }
        board[M.at(3)][M.at(2)] = board[M.at(1)][M.at(0)];
        board[M.at(1)][M.at(0)] = '.';
        if (M.length() == 5)
          board[M.at(3)][M.at(2)] = M.at(4);
        for (char i = '8'; i > '0'; i--) {
          for (char j = 'a'; j < 'i'; j++) {
            cerr << board[i][j] << " ";
          }
          cerr << endl;
        }
    }

    string result;
    for (char i = '8'; i > '0'; i--) {
      for (char j = 'a'; j < 'i'; j++) {
        char lc_count = '0';
        while (board[i][j] == '.' && j < 'i') {
          lc_count++;
          j++;
        }
        if (lc_count != '0') {
          result.append(1, lc_count);
          j--;          
        }
        else
          result.append(1, board[i][j]);
      }
      if (i != '1')
        result.append("/");
    }
    

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << result << endl;
}
