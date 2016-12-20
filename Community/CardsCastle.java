import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int H = in.nextInt();
        in.nextLine();
        Character[][] l_struct = new Character[H*2][H];
        for (int i = 0; i < H; i++) {
            String S = in.nextLine();
            for (int j = 0; j < H * 2; j++) {
                l_struct[j][i] = S.charAt(j);
            }
        }
        
        boolean isStable = true;
        
        for (int i = 0; i < H*2; i++) {
            for (int j = 0; j < H ; j++) {
                if (l_struct[i][j] == '/') {
                    if (i+1 < H*2 && l_struct[i+1][j] != '\\')
                        isStable = false;
                    if (j+1 < H && l_struct[i][j+1] != '\\')
                        isStable = false;                  
                }
                if (l_struct[i][j] == '\\') {
                    if (i-1 > 0 && l_struct[i-1][j] != '/')
                        isStable = false;
                    if (j+1 < H && l_struct[i][j+1] != '/')
                        isStable = false;                   
                }
            }
        }        

        if (isStable)
            System.out.println("STABLE");
        else
            System.out.println("UNSTABLE");
    }
}
