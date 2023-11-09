# robot

What the program does and the corresponding lines in the main():

1. Line 328 - 361
   Draws the 10*10 grid, 3 markers, 4 blockers, the home and the robot. The markers and blockers have no position restrictions. The position of the home and the initial direction of the robot can be inputted by the user.
   
2. Line 366-495
  The robot gets to the first marker. The path from home to marker is recorded.

3. Line 496-499
   The robot pick up the marker and bring it back to home following the recorded path.
   
4. Step 2 and 3 are repeated for each marker so that all the markers are collected.

The robot is able to collect all the markers back to home with any given home position, with a relatively short path.

To compile the program, enter the command line in the terminal:
gcc -o robot robot.c graphics.c

To run the compiled program without addition input, enter the command line in the terminal (the name of drawapp.jar depends on the version of your drawapp):
./robot | java -jar drawapp.jar

To run the compiled program with additional input, add x_coordinate, y_coordinate and direction after ./robot in the command line, for example:
./robot 9 5 north | java -jar drawapp.jar
./robot 3 0 east | java -jar drawapp.jar

Note: the x_coordinate and y_coordinate should be two integers that are in the range of 0-9 (inclusive). The direction can only be one of the following 4 options: north, south, east, west.
