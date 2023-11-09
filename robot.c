#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Point
{
    int x;
    int y;
} Point;

Point Markers[] = {{0,7}, {7,2}, {8,8}};

//used if one of the markers coincide with home
Point substituteMarker = {3,1};

//counter of which matker is being processed
int counter =0;

Point Blockers[] = {{2,4}, {4,6},{9,3}, {6,9}};

//used if one of blockers coincide with home
Point substituteBlocker = {5,5};

//limit the range to get to each marker
int xMin, xMax, yMin, yMax;

/*
path[] records the path of the robot
-2: right()
-1: unsigned
0: left()
other: number of times of forward() is called
*/
int path[100];
int path_len = -1;

bool comparePoint(Point a, Point b)
{
    bool result = false;
    if ((a.x == b.x) && (a.y == b.y))
    {
        result = true;
    }
    return result;
}

typedef struct Robot
{
    Point homePoint;
    Point currentPoint;
    char *direction;
    bool pickUpMarker;
} Robot;

Robot robot;

void drawGrid()
{
    background();
    setColour(black);

    for (int i = 0; i < 11; i++)
    {
        drawLine(50, 50 + i * 50, 550, 50 + i * 50);
        drawLine(50 + i * 50, 50, 50 + i * 50, 550);
    }
}

//returns the top left coordinate of the point in the canvas
Point getTopLeft(Point p)
{
    p.x = 50 + 50 * p.x;
    p.y = 50 + 50 * p.y;
    return p;
}

void drawHome()
{
    background();
    setColour(blue);

    Point home = getTopLeft(robot.homePoint);
    fillRect(home.x, home.y, 50, 50);
}

void drawRobot()
{
    foreground();
    setColour(green);

    int x = robot.currentPoint.x;
    int y = robot.currentPoint.y;

    if (strcmp(robot.direction, "north") == 0)
    {
        int xCoords[] = {50 + x * 50, 75 + x * 50, 100 + x * 50};
        int yCoords[] = {100 + y * 50, 50 + y * 50, 100 + y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    else if (strcmp(robot.direction, "east") == 0)
    {
        int xCoords[] = {50 + x * 50, 50 + x * 50, 100 + x * 50};
        int yCoords[] = {50 + y * 50, 100 + y * 50, 75 + y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    else if (strcmp(robot.direction, "south") == 0)
    {
        int xCoords[] = {50 + x * 50, 100 + x * 50, 75 + x * 50};
        int yCoords[] = {50 + y * 50, 50 + y * 50, 100 + y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    else if (strcmp(robot.direction, "west") == 0)
    {
        int xCoords[] = {50 + x * 50, 100 + x * 50, 100 + x * 50};
        int yCoords[] = {75 + y * 50, 50 + y * 50, 100 + y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    
}

void drawMarker()
{
    background();
    setColour(gray);

    for(int i=0; i<3; i++)
    {
        Point marker = getTopLeft(Markers[i]);
        fillRect(marker.x, marker.y, 50, 50);

    }

}

void drawBlocker()
{
    background();
    setColour(black);

    for(int i=0; i<4; i++)
    {
        Point blocker = getTopLeft(Blockers[i]);
        fillRect(blocker.x, blocker.y, 50,50);
    }
}

void drawBackground()
{
    drawGrid();
    drawBlocker();
    drawMarker();
    drawHome();
}

void left()
{
    foreground();
    clear();
    if (strcmp(robot.direction, "north") == 0)
    {
        robot.direction = "west";
        drawRobot();
    }
    else if(strcmp(robot.direction, "west") == 0)
    {
        robot.direction = "south";
        drawRobot();
    }
    else if(strcmp(robot.direction, "south") == 0)
    {
        robot.direction = "east";
        drawRobot();
    }
    else
    {
        robot.direction = "north";
        drawRobot();
    }
}

void right()
{
    foreground();
    clear();
    if (strcmp(robot.direction, "north") == 0)
    {
        robot.direction = "east";
        drawRobot();
    }
    else if(strcmp(robot.direction, "west") == 0)
    {
        robot.direction = "north";
        drawRobot();
    }
    else if(strcmp(robot.direction, "south") == 0)
    {
        robot.direction = "west";
        drawRobot();
    }
    else
    {
        robot.direction = "south";
        drawRobot();
    }
}

//returns the expected next point if forward() is called
// east, south: positive direction
// west, north: negative direction
Point nextPosition()
{
    Point result = robot.currentPoint;
    if (strcmp(robot.direction, "north") == 0)
    {
        result.y -=1;
    }
    else if(strcmp(robot.direction, "south") == 0)
    {
        result.y +=1;
    }
    else if(strcmp(robot.direction, "west") == 0)
    {
        result.x -= 1;
    }
    else
    {
        result.x += 1;
    }
    return result;

}

bool canMoveForward()
{
    Point next = nextPosition();

    //the robot should not exceed the range
    if ((next.x <xMin) || (next.x > xMax))
    {
        return false;
    }
    else if ((next.y <yMin) || (next.y > yMax))
    {
        return false;
    }

    for (int i=0; i<4; i++)
    {
        if(comparePoint(Blockers[i], next) == true)
        {
            return false;
        }
    }

    return true;
}

bool atMarker(Point marker)
{
    return comparePoint(robot.currentPoint, marker);
}

bool atHome()
{
    return comparePoint(robot.homePoint, robot.currentPoint);
}

void forward()
{
    
    foreground();
    clear();
    robot.currentPoint = nextPosition();
    if(robot.pickUpMarker)
    {
        Markers[counter] = robot.currentPoint;
    }
    drawRobot();
    
}

void returnHome()
{
    //turn around
    left();
    sleep(500);
    left();
    sleep(500);

    for(int i=path_len; i >= 0; i--)
    {
        if(atHome())
        {
            return;
        }

        //opposite direction of the recorded path
        if (path[i] == 0)
        {
            right();
            sleep(500);
        }
        else if (path[i] == -2)
        {
            left();
            sleep(500);
        }
        
        else
        {
            for(int j=0; j< path[i]; j++)
            {
                forward();

                background();
                clear();
                drawBackground();
                sleep(500);
            }
        }
    }
}

int main(int argc, char **argv)
{
    setWindowSize(600, 600);

    robot.homePoint.x = 6;
    robot.homePoint.y = 5;
    robot.direction = "north";
    robot.pickUpMarker = false;

    if (argc == 4)
    {
        robot.homePoint.x = atoi(argv[1]);
        robot.homePoint.y = atoi(argv[2]);
        robot.direction = argv[3];
    }
    robot.currentPoint = robot.homePoint;

    drawRobot();
    
    for (int i=0; i<3; i++)
    {
        if (comparePoint(Markers[i], robot.homePoint) == true)
        {
            Markers[i] = substituteMarker;
        }
    }

    for (int i=0; i<4; i++)
    {
        if(comparePoint(Blockers[i], robot.homePoint) == true)
        {
            Blockers[i] = substituteBlocker;
        }
    }

    drawBackground();

    //process each marker
    for(counter=0; counter <3; counter++)
    {
        robot.pickUpMarker = false;

        //home and the marker are two diagonal corners of the rectangle range
        if(robot.currentPoint.x < Markers[counter].x)
        {
            xMin = robot.currentPoint.x;
            xMax = Markers[counter].x;
        }
        else
        {
            xMin = Markers[counter].x;
            xMax = robot.currentPoint.x;
        }

        //let the robot facing the correct vertical direction to the marker
        if(robot.currentPoint.y < Markers[counter].y)
        {
            yMin = robot.currentPoint.y;
            yMax = Markers[counter].y;
            robot.direction = "south";
            foreground();
            clear();
            drawRobot();
        }
        else
        {
            yMin = Markers[counter].y;
            yMax = robot.currentPoint.y;
            robot.direction = "north";
            foreground();
            clear();
            drawRobot();
        }

        for(int i=0; i< 100; i++)
        {
            path[i] = -1;
        }
        path_len = -1;

        while(!atMarker(Markers[counter]))
        {

            sleep(500);
            
            /*
            Both the robot and the marker are at the corner of the rectangle range.

            If the robot always moves next to the wall of the range, 
            it will definitely get to the marker.

            Let the robot's right hand side always be the wall (or the blocker).
            */

            //check if can move in right direction
            right();

            if(canMoveForward())
            {
                path_len += 1;
                path[path_len] = -2;

                forward();
                path_len += 1;
                path[path_len] = 1;
            }
            else
            {
                //return to original directon
                left();

                //check if can move forward
                if(canMoveForward())
                {
                    forward();
                    switch(path[path_len])
                    {
                    //open a new path
                    case -1:
                        path_len += 1;
                        path[path_len] = 1;
                        break;
                    
                    //the last action is left()
                    //record a new distance in a new int element
                    case 0:
                        path_len += 1;
                        path[path_len] = 1;
                        break;

                    //the last action is right()
                    //record a new distance in a new int element
                    case -2:
                        path_len += 1;
                        path[path_len] = 1;
                        break;

                    //the last action is forward()
                    //increment the distance
                    default:
                        path[path_len] += 1;
                        break;
                    }
                }
                else
                {
                    //check if can move in left direction
                    left();
                    path_len += 1;
                    path[path_len] = 0;

                    if(canMoveForward())
                    {
                        forward();
                        path_len += 1;
                        path[path_len] = 1;
                    }
                    
                    //all three directions are unavailable, turn around
                    else
                    {
                        left();
                        path_len += 1;
                        path[path_len] = 0;
                    }

                }
            }
            
        }
        robot.pickUpMarker = true;

        sleep(500);
        returnHome();

    }

    return 0;
}
