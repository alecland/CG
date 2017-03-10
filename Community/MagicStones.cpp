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
    map<int, int> stones;
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int level;
        cin >> level; cin.ignore();
        stones[level]++;
    }

    int sum = 0;
    for (int i = 1; i < 100; ++i) {
        stones[i+1] += stones[i] / 2;
        stones[i] = stones[i] % 2;
        sum += stones[i];
    }

    cout << sum << endl;
}
