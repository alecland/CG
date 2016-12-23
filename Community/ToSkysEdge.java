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
        int Y = in.nextInt();
        int C = in.nextInt();
        int N = in.nextInt();
        System.err.println(String.valueOf(Y) + " " + String.valueOf(C) + " " + String.valueOf(N));
        Map<Integer, Long> population;
        Map<Integer, Long> initialPop = new HashMap<Integer, Long>();
        for (int i = 0; i < 150; i++) {
            initialPop.put(i, 0L);
        }
        for (int i = 0; i < N; i++) {
            int AGE = in.nextInt();
            long NUMBER = (long)in.nextInt();
            initialPop.put(AGE, NUMBER);
            System.err.println(String.valueOf(AGE) + " " + String.valueOf(NUMBER));
        }
        
        int minAge = 0;
        int maxAge = 0;
        int testAge = 41;
        
        while (minAge == 0 || maxAge == 0) {
            // reset population
            population = new HashMap<Integer, Long>(initialPop); 
            long repCount = 0;
            
            for (int y = 0; y < Y; y++) {
                // Every crew member will get older by one year
                repCount = 0;
                for (int i = testAge; i > 0; i--) {
                    population.put(i, population.get(i-1));
                    if (i >= 20 && i <= testAge/2)
                        repCount += population.get(i);
                }
                population.put(0, (long)(repCount/10));
                //System.err.println(population.get(0));
            }
            
            long finalCount = 0;
            for (int i = testAge; i >= 0; i--) {
                finalCount += population.get(i);
            }
            
            
            if (minAge == 0 && finalCount >= 200 && finalCount <= C)
                minAge = testAge;
            if (maxAge == 0 && finalCount > C)
                maxAge = testAge -1;
            if (testAge == 150)
                maxAge = minAge;
            
            System.err.println(String.valueOf(testAge) + " " + String.valueOf(finalCount));
            testAge++;
            
        }

        // Write an action using System.out.println()
        // To debug: System.err.println("Debug messages...");
        
        System.out.println(String.valueOf(minAge) + " " + String.valueOf(maxAge));
    }
}
