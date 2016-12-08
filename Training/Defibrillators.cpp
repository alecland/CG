#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Defib
{
    private:
        int number;        
        string address;
        string phone;
        double LAT;
        double LON;
    
    public:
        string name;
        Defib(const string& initString)
        {
            string StringToParse(initString);
            cerr << StringToParse << endl;
            
            int sepPos = StringToParse.find(";");
            number = stoi(StringToParse.substr(0, sepPos));
            StringToParse.assign(StringToParse.substr(sepPos + 1));
            
            sepPos = StringToParse.find(";");
            name = StringToParse.substr(0, sepPos);
            StringToParse.assign(StringToParse.substr(sepPos + 1));
            
            sepPos = StringToParse.find(";");
            address = StringToParse.substr(0, sepPos);
            StringToParse.assign(StringToParse.substr(sepPos + 1));
            
            sepPos = StringToParse.find(";");
            phone = StringToParse.substr(0, sepPos);
            StringToParse.assign(StringToParse.substr(sepPos + 1));
            
            sepPos = StringToParse.find(";");
            string strLON = StringToParse.substr(0, sepPos);
            int dotPos = strLON.find(",");
            strLON.replace(dotPos, 1, ".");
            LON = stod(strLON);
            StringToParse.assign(StringToParse.substr(sepPos + 1));
            
            sepPos = StringToParse.find(";");
            string strLAT = StringToParse.substr(0, sepPos);
            dotPos = strLAT.find(",");
            strLAT.replace(dotPos, 1, ".");
            LAT = stod(strLAT);
            StringToParse.assign(StringToParse.substr(sepPos + 1));
        }
        
        double getDistance(string lonStr, string latStr)
        {
            int dotPos = lonStr.find(",");
            lonStr.replace(dotPos, 1, ".");
            double lon = stod(lonStr);
            
            dotPos = latStr.find(",");
            latStr.replace(dotPos, 1, ".");
            double lat = stod(latStr);
            
            
            double x = (LON - lon) * cos((LAT + lat)/2.0);
            double y = LAT - lat;
            double dist = sqrt(x*x + y*y) * 6371.0;
            return dist;
        }
        
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string LON;
    cin >> LON; cin.ignore();
    string LAT;
    cin >> LAT; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    double minDist = 40000000;
    string result;
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        Defib tmpDefib = Defib(DEFIB);
        if (tmpDefib.getDistance(LON, LAT) < minDist)
        {
            minDist = tmpDefib.getDistance(LON, LAT);
            result.assign(tmpDefib.name);
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << result << endl;
}
