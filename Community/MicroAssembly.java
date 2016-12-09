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
        Map<Character, Integer> l_register = new HashMap<Character, Integer>();
        l_register.put('a', in.nextInt());
        l_register.put('b', in.nextInt());
        l_register.put('c', in.nextInt());
        l_register.put('d', in.nextInt());
        int n = in.nextInt();
        in.nextLine();
        Map<Integer, String> l_map = new HashMap<Integer, String>();
        Map<Integer, String> l_instruction = new HashMap<Integer, String>();
        for (int i = 0; i < n; i++) {
            String instruction = in.nextLine();
            l_map.put(i, instruction);
        }
        
        for (int i = 0; i < n; i++) {
            int index = 0;
            for (String retval:  l_map.get(i).split(" ")) {
                l_instruction.put(index, retval);
                index++;
             }
             
             int value;
             int value2;
             Character l_char = l_instruction.get(2).charAt(0);
             Character l_char2;
             
             switch (l_instruction.get(0)) {
                case "MOV":                    
                    if (Character.isDigit(l_char) || l_char == '-')
                        value = Integer.parseInt(l_instruction.get(2));
                    else
                        value = l_register.get(l_char);
                    l_register.put(l_instruction.get(1).charAt(0), value);
                    break;
                case "ADD":
                    l_char2 = l_instruction.get(3).charAt(0); 
                    if (Character.isDigit(l_char) || l_char == '-')
                        value = Integer.parseInt(l_instruction.get(2));
                    else
                        value = l_register.get(l_char);
                    if (Character.isDigit(l_char2) || l_char2 == '-')
                        value2 = Integer.parseInt(l_instruction.get(3));
                    else
                        value2 = l_register.get(l_char2);
                    l_register.put(l_instruction.get(1).charAt(0), value + value2);
                    break;
                case "SUB":
                    l_char2 = l_instruction.get(3).charAt(0);
                    if (Character.isDigit(l_char) || l_char == '-')
                        value = Integer.parseInt(l_instruction.get(2));
                    else
                        value = l_register.get(l_char);
                    if (Character.isDigit(l_char2) || l_char2 == '-')
                        value2 = Integer.parseInt(l_instruction.get(3));
                    else
                        value2 = l_register.get(l_char2);
                    l_register.put(l_instruction.get(1).charAt(0), value - value2);
                    break;
                case "JNE":
                    l_char2 = l_instruction.get(3).charAt(0);
                    if (Character.isDigit(l_char) || l_char == '-')
                        value = Integer.parseInt(l_instruction.get(2));
                    else
                        value = l_register.get(l_char);
                    if (Character.isDigit(l_char2) || l_char2 == '-')
                        value2 = Integer.parseInt(l_instruction.get(3));
                    else
                        value2 = l_register.get(l_char2);
                    if (value != value2)
                        i = Integer.parseInt(l_instruction.get(1)) - 1;
                    break;
             }
        }

        // Write an action using System.out.println()
        // To debug: System.err.println("Debug messages...");

        System.out.println(l_register.get('a') + " " + l_register.get('b') + " " + l_register.get('c') + " " + l_register.get('d'));
    }
}
