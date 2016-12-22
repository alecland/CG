import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player {
    public static int m4_exitFloor;
    public static int m4_exitPos;
    public static int m4_highestFloor;
    public static Integer[] mt4_elevatorList;
    public static Map<Integer, Integer> mm44_blockedFloors;
    
    public static int getTarget(int p4_currentFloor) {        
        int l4_targetPos = -1;

        if (p4_currentFloor == m4_exitFloor)
            l4_targetPos = m4_exitPos;
        else if (p4_currentFloor > -1)
            l4_targetPos = mt4_elevatorList[m4_highestFloor];
        
        return l4_targetPos;
    }
    
    public static void updateHighestFloor(int p4_currentFloor) {
        if (p4_currentFloor > m4_highestFloor)
            m4_highestFloor = p4_currentFloor;
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int nbFloors = in.nextInt(); // number of floors
        int width = in.nextInt(); // width of the area
        int nbRounds = in.nextInt(); // maximum number of rounds
        m4_exitFloor = in.nextInt(); // floor on which the exit is found
        m4_exitPos = in.nextInt(); // position of the exit on its floor
        int nbTotalClones = in.nextInt(); // number of generated clones
        int nbAdditionalElevators = in.nextInt(); // ignore (always zero)
        int nbElevators = in.nextInt(); // number of elevators
        System.err.println(nbElevators);
        
        mt4_elevatorList = new Integer[nbElevators];
        mm44_blockedFloors = new HashMap<Integer, Integer>();        
        m4_highestFloor = 0;
        
        for (int i = 0; i < nbElevators; i++) {
            int elevatorFloor = in.nextInt(); // floor on which this elevator is found
            int elevatorPos = in.nextInt(); // position of the elevator on its floor
            System.err.println(elevatorFloor);
            System.err.println(elevatorPos);
            mt4_elevatorList[elevatorFloor] = elevatorPos;
        }
        
        for (int i = 0; i < nbFloors; i++) {
            mm44_blockedFloors.put(i, -1);
        }

        // game loop
        while (true) {
            int cloneFloor = in.nextInt(); // floor of the leading clone
            int clonePos = in.nextInt(); // position of the leading clone on its floor
            String direction = in.next(); // direction of the leading clone: LEFT or RIGHT
            
            updateHighestFloor(cloneFloor);
            int l4_targetPos = getTarget(cloneFloor);
            System.err.println(l4_targetPos);           

                
            if (direction.charAt(0) == 'L') {
                if (clonePos >= l4_targetPos  || mm44_blockedFloors.get(cloneFloor) != -1)
                    System.out.println("WAIT");
                else {
                    System.out.println("BLOCK");
                    mm44_blockedFloors.put(cloneFloor, clonePos);
                }
            }
            else if (direction.charAt(0) == 'R') {
                if (clonePos <= l4_targetPos || mm44_blockedFloors.get(cloneFloor) != -1)                    
                    System.out.println("WAIT");
                else {
                    System.out.println("BLOCK");
                    mm44_blockedFloors.put(cloneFloor, clonePos);
                }
            }

            // No clone on board, WAIT
            System.out.println("WAIT");
        }
    }
}
