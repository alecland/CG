import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Solution {
    
    public static void updateCounters(char p_char, Map<Character, Integer> p_map) {
      switch (p_char) {
          case 'R':
              
              p_map.put('L', p_map.get('L') + p_map.get('R'));
              p_map.put('U', 2 * p_map.get('U'));
              p_map.put('D', 2 * p_map.get('D'));
              p_map.put('R', 1);
              break;
          case 'L':
              
              p_map.put('R', p_map.get('R') + p_map.get('L'));
              p_map.put('U', 2 * p_map.get('U'));
              p_map.put('D', 2 * p_map.get('D'));
              p_map.put('L', 1);
              break;
          case 'U':
              p_map.put('L', 2 * p_map.get('L'));
              p_map.put('R', 2 * p_map.get('R'));
              p_map.put('D', p_map.get('D') + p_map.get('U'));
              p_map.put('U', 1);
              break;
          case 'D':
              
              p_map.put('L', 2 * p_map.get('L'));
              p_map.put('U', p_map.get('U') + p_map.get('D'));
              p_map.put('R', 2 * p_map.get('R'));
              p_map.put('D', 1);
              break;
      }
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        String order = in.nextLine();
        String side = in.nextLine();
        Map l_map = new HashMap<Character, Integer>();
        l_map.put('R', 1);
        l_map.put('L', 1);
        l_map.put('U', 1);
        l_map.put('D', 1);
 
        
        for (int i = 0; i < order.length(); i++) {
            updateCounters(order.charAt(i), l_map);
        }

        // Write an action using System.out.println()
        System.err.println(order);
        System.err.println(side);

        System.out.println(l_map.get(side.charAt(0)));
    }
}
