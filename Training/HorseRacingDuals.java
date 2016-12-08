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
        List<Integer> horses = new ArrayList<Integer>();
        int result = 10000000;
        int N = in.nextInt();
        for (int i = 0; i < N; i++) {
            int pi = in.nextInt();
            horses.add(pi);
        }
        
        Collections.sort(horses);
        for (int i = 1; i < horses.size(); i++) {
            if (Math.abs(horses.get(i) - horses.get(i - 1)) < result)
                result = Math.abs(horses.get(i) - horses.get(i - 1));
        }

        // Write an action using System.out.println()
        // To debug: System.err.println("Debug messages...");

        System.out.println(result);
    }
}
