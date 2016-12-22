#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getValue(string card)
{
    int value = 0;
    switch (card.at(0))
    {
        case '3':
        value = 1;
        break;
        case '4':
        value = 2;
        break;
        case '5':
        value = 3;
        break;
        case '6':
        value = 4;
        break;
        case '7':
        value = 5;
        break;
        case '8':
        value = 6;
        break;
        case '9':
        value = 7;
        break;
        case '1':
        value = 8;
        break;
        case 'J':
        value = 9;
        break;
        case 'Q':
        value = 10;
        break;
        case 'K':
        value = 11;
        break;
        case 'A':
        value = 12; 
        break;
    }
    return value;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string result;
    int n; // the number of cards for player 1
    string p1Hand;
    string p2Hand;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        p1Hand.append(cardp1);
        if (i != n-1)
            p1Hand.append(" ");
    }
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        p2Hand.append(cardp2);
        if (i != n-1)
            p2Hand.append(" ");
    }
    cerr << p1Hand << endl;
    cerr << p2Hand << endl;
    
    int turnsCount = 0;
    
    while (result.empty())
    {        
        int p1SepPos = p1Hand.find(" ");
        int p2SepPos = p2Hand.find(" ");
        string p1Card;
        string p2Card;
        
        if (p1SepPos != string::npos)
            p1Card.assign(p1Hand.substr(0, p1SepPos));
        else
            p1Card.assign(p1Hand);
            
        if (p2SepPos != string::npos)
            p2Card.assign(p2Hand.substr(0, p2SepPos));
        else
            p2Card.assign(p2Hand);
            
            
        string cardsToWin(" ");
        cardsToWin.append(p1Card).append(" ");
        cardsToWin.append(p2Card);
        
        while (getValue(p1Card) == getValue(p2Card) && result.empty())
        {
            cerr << "BATTLE" << endl;
            int index = 0;
            while (index <= 3 && result.empty())
            {
                p1SepPos = p1Hand.find(" ", p1SepPos + 1);
                p2SepPos = p2Hand.find(" ", p2SepPos + 1);
                if ((p1SepPos == string::npos || p2SepPos == string::npos) && index != 3)
                {
                    result = "PAT";
                }
                index++;
            }
            cardsToWin.assign(" ");
            cardsToWin.append(p1Hand.substr(0, p1SepPos));
            p1Card.assign(cardsToWin.substr(cardsToWin.rfind(" ") + 1));
            cardsToWin.append(" ");
            cardsToWin.append(p2Hand.substr(0, p2SepPos));
            p2Card.assign(cardsToWin.substr(cardsToWin.rfind(" ") + 1));
            cerr << "Cards to win: " << cardsToWin << endl;
        }
        cerr << p1Card << ": " << getValue(p1Card) << endl;
        cerr << p2Card << ": " << getValue(p2Card) << endl;
            
        if (result.empty())
        {
            if (getValue(p1Card) > getValue(p2Card))
            {
                if (p2SepPos != string::npos)
                {
                    // P1 wins
                    p1Hand.assign(p1Hand.substr(p1SepPos + 1));
                    p1Hand.append(cardsToWin);
                    // P2 loses
                    p2Hand.assign(p2Hand.substr(p2SepPos + 1));
                }
                else
                {
                    result.assign("1");
                }
            }
            else if (getValue(p1Card) < getValue(p2Card))
            {
                if (p1SepPos != string::npos)
                {
                    // P2 wins
                    p2Hand.assign(p2Hand.substr(p2SepPos + 1));
                    p2Hand.append(cardsToWin);
                    // P1 loses
                    p1Hand.assign(p1Hand.substr(p1SepPos + 1));
                }
                else
                {
                    result.assign("2");
                }
            }
        }
        turnsCount++;
        cardsToWin.clear();
        cerr << "End of turn n°" << turnsCount << endl;
        cerr << p1Hand << endl;
        cerr << p2Hand << endl;
        
    }

    if (result == "PAT")
        cout << result << endl;
    else
    {
        result.append(" ");
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
    
        cout << result << turnsCount << endl;
    }
}


