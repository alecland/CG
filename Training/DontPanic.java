import java.util.*;
import java.io.*;
import java.math.*;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int nbFloors = in.nextInt(); // number of floors
        int width = in.nextInt(); // width of the area
        int nbRounds = in.nextInt(); // maximum number of rounds
        int exitFloor = in.nextInt(); // floor on which the exit is found
        int exitPos = in.nextInt(); // position of the exit on its floor
        int nbTotalClones = in.nextInt(); // number of generated clones
        int nbAdditionalElevators = in.nextInt(); // ignore (always zero)
        int nbElevators = in.nextInt(); // number of elevators
        System.err.println(nbElevators);
        Integer elevatorList[] = new Integer[nbElevators];
        Integer blockedClones[] = new Integer[nbTotalClones];
        for (int i = 0; i < nbTotalClones; i++) {
            blockedClones[i] = 0;
        }
        for (int i = 0; i < nbElevators; i++) {
            int elevatorFloor = in.nextInt(); // floor on which this elevator is found
            int elevatorPos = in.nextInt(); // position of the elevator on its floor
            System.err.println(elevatorFloor);
            System.err.println(elevatorPos);
            elevatorList[elevatorFloor] = elevatorPos;
        }

        // game loop
        while (true) {
            int cloneFloor = in.nextInt(); // floor of the leading clone
            int clonePos = in.nextInt(); // position of the leading clone on its floor
            String direction = in.next(); // direction of the leading clone: LEFT or RIGHT

            // Write an action using System.out.println()
            // To debug: System.err.println("Debug messages...");
            System.err.println(direction);
            System.err.println(clonePos);
            System.err.println(exitPos);
            System.err.println(cloneFloor);
            System.err.println(exitFloor);
            if (cloneFloor == exitFloor) {
                System.err.println("Exit floor reached");
                if (direction.charAt(0) == 'L') {
                    if (clonePos >= exitPos  || blockedClones[cloneFloor] != 0)
                        System.out.println("WAIT");
                    else {
                        System.out.println("BLOCK");
                        blockedClones[cloneFloor] = clonePos;
                    }
                }
                else if (direction.charAt(0) == 'R') {
                    if (clonePos <= exitPos || blockedClones[cloneFloor] != 0)                    
                        System.out.println("WAIT");
                    else {
                        System.out.println("BLOCK");
                        blockedClones[cloneFloor] = clonePos;
                    }
                }
            }
            else {
                if (direction.charAt(0) == 'L') {
                    if (clonePos >= elevatorList[cloneFloor]  || blockedClones[cloneFloor] != 0)
                        System.out.println("WAIT");
                    else {
                        System.out.println("BLOCK");
                        blockedClones[cloneFloor] = clonePos;
                    }
                }
                else if (direction.charAt(0) == 'R') {
                    if (clonePos <= elevatorList[cloneFloor]  || blockedClones[cloneFloor] != 0)
                        System.out.println("WAIT");
                    else {
                        System.out.println("BLOCK");
                        blockedClones[cloneFloor] = clonePos;
                    }
                }
            }
            
            // No clone on board, WAIT
            System.out.println("WAIT");
        }
    }
}
