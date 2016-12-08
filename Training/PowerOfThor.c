#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    char result[2];
    scanf("%d%d%d%d", &lightX, &lightY, &initialTX, &initialTY);

    // game loop
    while (1) {
        memset(result, 0, 2);
        if (lightY - initialTY > 0) {
            strcat(result,"S");
            initialTY++;
        } else if (lightY - initialTY < 0) {
            strcat(result,"N");
            initialTY--;
        }
        
        if (lightX - initialTX > 0) {
            strcat(result,"E");
            initialTX++;
        } else if (lightX - initialTX < 0) {
            strcat(result,"W");
            initialTX--;
        }

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");

        // A single line providing the move to be made: N NE E SE S SW W or NW
        printf("%s\n", result);
    }

    return 0;
}
