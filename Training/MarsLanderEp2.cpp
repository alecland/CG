#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define YMAX_SPEED 40.0
#define XMAX_SPEED 20.0
#define GRAVITY -3.711

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    int nextPower = 4;
    int nextAngle = 0;
    int landingAreaStart = 0;
    int landingAreaEnd = 0;
    int previousLandX = 0;
    int previousLandY = 0;
    cin >> surfaceN; cin.ignore();
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
        
        if (previousLandX != 0 && landingAreaStart == 0 && previousLandY == landY)
            landingAreaStart = previousLandX;
        if (landingAreaStart != 0 && landingAreaEnd == 0 && previousLandY != landY)
            landingAreaEnd = previousLandX;
            
        previousLandX = landX;
        previousLandY = landY;
    }
    cerr << landingAreaStart << " " << landingAreaEnd << endl;

    // game loop
    while (1) {
        int X;
        int Y;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        nextPower = 4;
        
        if(X < landingAreaStart - hSpeed) {
            if(hSpeed > 60)
                nextAngle = 30;
            else if(hSpeed > 45)
                nextAngle = 15;
            else if(hSpeed > 30) {
                if(vSpeed < 0)
                    nextAngle = 0;
                else {
                    nextAngle = 0;
                    nextPower = 0;
                }
            } else if(hSpeed > 20)
                nextAngle = -15;
            else
                nextAngle = -30;
        } else if(X > landingAreaEnd + hSpeed) {
            if(hSpeed < -60)
                nextAngle = -30;
            else if(hSpeed < -45)
                nextAngle = -15;
            else if(hSpeed < -30) {
                if(vSpeed < 0)
                    nextAngle = 0;
                else {
                    nextAngle = 0;
                    nextPower = 0;
                }
            } else if(hSpeed<-20)
                nextAngle = 15;
            else
                nextAngle = 30;
        } else if(hSpeed > 10)
            nextAngle = 40;
        else if(hSpeed < -10)
            nextAngle = -40;
        else if(vSpeed < -35)
            nextAngle = 0;
        else if(vSpeed < -20) {
            nextAngle = 0;
            nextPower = 3;
        } else if(vSpeed < -10) {
            nextAngle = 0;
            nextPower = 2;
        } else {
            nextAngle = 0;
            nextPower = 0; 
        }
        
        cout << nextAngle << " " << nextPower << endl;
        
    }
}
