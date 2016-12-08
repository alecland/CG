package main

import "fmt"
//import "os"

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

func main() {
    for {
        var currentHighestMountain int
        currentHighestMountain = 0
        var currentTarget int
        currentTarget = -1
        for i := 0; i < 8; i++ {
            // mountainH: represents the height of one mountain, from 9 to 0.
            var mountainH int
            fmt.Scan(&mountainH)
            if mountainH > currentHighestMountain {
                currentHighestMountain = mountainH
                currentTarget = i
            }
        }
        
        // fmt.Fprintln(os.Stderr, "Debug messages...")
        fmt.Println(currentTarget) // The number of the mountain to fire on.
    }
}
