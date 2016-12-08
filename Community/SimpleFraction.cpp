#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <sys/time.h>
#pragma GCC optimize("Ofast")

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 struct D2 {
     int x;
     int y;
 };
 
 int pgcd( int a, int b) {
  return a ? pgcd(b%a, a) : b;
};

unsigned int gcd(unsigned int u, unsigned int v)
{
  int shift;

  /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
  if (u == 0) return v;
  if (v == 0) return u;
 
  /* Let shift := lg K, where K is the greatest power of 2
        dividing both u and v. */
  for (shift = 0; ((u | v) & 1) == 0; ++shift) {
         u >>= 1;
         v >>= 1;
  }
 
  while ((u & 1) == 0)
    u >>= 1;
 
  /* From here on, u is always odd. */
  do {
       /* remove all factors of 2 in v -- they are not common */
       /*   note: v is not zero, so while will terminate */
       while ((v & 1) == 0)  /* Loop X */
           v >>= 1;

       /* Now u and v are both odd. Swap if necessary so u <= v,
          then set v = v - u (which is even). For bignums, the
          swapping is just pointer movement, and the subtraction
          can be done in-place. */
       if (u > v) {
         unsigned int t = v; v = u; u = t;}  // Swap u and v.
       v = v - u;                       // Here v >= u.
     } while (v != 0);

  /* restore common factors of 2 */
  return u << shift;
};
 
int main()
{
    int N;
    map<int, D2> myMap;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string xY;
        cin >> xY; cin.ignore();
        size_t slashPos = xY.find("/");
        myMap[i].x = stoi(xY.substr(0, slashPos + 1));
        myMap[i].y = stoi(xY.substr(slashPos + 1));
        cerr << xY << endl;
    }
    for (int i = 0; i < N; i++) {
        int result = 0;
        int space;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        if (myMap[i].y == 0) {
            cout << "DIVISION BY ZERO" << endl;
        }
        else if (myMap[i].x == 0) {
            cout << 0 << endl;
        }
        else {
            bool isNeg = false;
            if (myMap[i].x < 0 && myMap[i].y > 0 || myMap[i].x > 0 && myMap[i].y < 0)
                isNeg = true;
            myMap[i].x = abs(myMap[i].x);
            myMap[i].y = abs(myMap[i].y);
            //int min = (myMap[i].x < myMap[i].y) ? myMap[i].x : myMap[i].y;

            
                
            // result computation
            if (myMap[i].x >= myMap[i].y) {
                result = myMap[i].x / myMap[i].y;
                myMap[i].x = myMap[i].x - myMap[i].y * result;                
            }
            
            //struct timeval tbegin,tend;
            //double texec=0.;
            // fraction reduction
            //gettimeofday(&tbegin,NULL);
            int divisor = pgcd(myMap[i].x, myMap[i].y);
            //while (divisor != 1) {
                myMap[i].x = myMap[i].x / divisor;
                myMap[i].y = myMap[i].y / divisor;
            //gettimeofday(&tend,NULL);
            //texec=((double)(1000*(tend.tv_sec-tbegin.tv_sec)+((tend.tv_usec-tbegin.tv_usec)/1000)));
            //cerr << texec << endl;
            //    divisor = pgcd(myMap[i].x, myMap[i].y);;
            //}
            //for (int j = min; j > 1; j--) {
            //    if ((myMap[i].x % j == 0) && (myMap[i].y % j == 0)) {
            //        myMap[i].x = myMap[i].x / j;
            //        myMap[i].y = myMap[i].y / j;
            //        min = (myMap[i].x < myMap[i].y) ? myMap[i].x : myMap[i].y;
            //        j = min;
            //    }
            //}
            
            //cerr << isNeg << " " << result << endl;
            
            if (result == 0 && !isNeg)
                cout << myMap[i].x << "/" << myMap[i].y << endl;
            else if (result == 0 && isNeg)
                cout << "-" << myMap[i].x << "/" << myMap[i].y << endl;
            else if (myMap[i].x == 0 && isNeg)
                cout << "-" << result << endl;
            else if (myMap[i].x == 0 && !isNeg)
                cout << result << endl;
            else if (isNeg)
                cout << "-" << result << " " << myMap[i].x << "/" << myMap[i].y << endl;
            else
                cout << result << " " << myMap[i].x << "/" << myMap[i].y << endl;
        }    
    }
}
