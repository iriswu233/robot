#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// use depth first search
// east, south: positive direction
// west, north: negative direction

typedef struct Point
{
    int x;
    int y;
} Point;

Point Markers[] = {{0,7}, {7,2}, {8,8}};
Point substituteMarker = {4,3};
Point Blockers[] = {{1,2}, {2,4}, {4,6},{8,3}, {6,8}};
Point substituteBlocker = {7,7};

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

Point getTopLeft(Point p)
{
    p.x = 50 + 50 * p.x;
    p.y = 50 + 50 * p.y;
    return p;
}

void drawHome(Point home)
{
    background();
    setColour(blue);

    home = getTopLeft(home);
    fillRect(home.x, home.y, 50, 50);
}

void drawRobot(Point pos, const char *direction)
{
    foreground();
    setColour(green);

    if (strcmp(direction, "north") == 0)
    {
        int xCoords[] = {50 + pos.x * 50, 75 + pos.x * 50, 100 + pos.x * 50};
        int yCoords[] = {100 + pos.y * 50, 50 + pos.y * 50, 100 + pos.y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    else if (strcmp(direction, "east") == 0)
    {
        int xCoords[] = {50 + pos.x * 50, 50 + pos.x * 50, 100 + pos.x * 50};
        int yCoords[] = {50 + pos.y * 50, 100 + pos.y * 50, 75 + pos.y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    else if (strcmp(direction, "south") == 0)
    {
        int xCoords[] = {50 + pos.x * 50, 100 + pos.x * 50, 75 + pos.x * 50};
        int yCoords[] = {50 + pos.y * 50, 50 + pos.y * 50, 100 + pos.y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
    else if (strcmp(direction, "west") == 0)
    {
        int xCoords[] = {50 + pos.x * 50, 100 + pos.x * 50, 100 + pos.x * 50};
        int yCoords[] = {75 + pos.y * 50, 50 + pos.y * 50, 100 + pos.y * 50};
        fillPolygon(3, xCoords, yCoords);
    }
}

void drawMarker(Point marker)
{
    foreground();
    setColour(gray);

    marker = getTopLeft(marker);
    fillRect(marker.x, marker.y, 50, 50);
}

void drawBlocker(Point blocker)
{
    background();
    setColour(black);

    blocker = getTopLeft(blocker);
    fillRect(blocker.x, blocker.y, 50,50);
}

void left()
{
    
}

int main(int argc, char **argv)
{
    setWindowSize(600, 600);
    drawGrid();

    robot.homePoint.x = 6;
    robot.homePoint.y = 5;
    robot.currentPoint = robot.homePoint;
    robot.direction = "north";

    if (argc == 4)
    {
        robot.homePoint.x = atoi(argv[1]);
        robot.homePoint.y = atoi(argv[2]);
        robot.currentPoint = robot.homePoint;
        robot.direction = argv[3];
    }

    drawHome(robot.homePoint);
    drawRobot(robot.currentPoint, robot.direction);
    
    for (int i=0; i<3; i++)
    {
        if (comparePoint(Markers[i], robot.homePoint) == true)
        {
            Markers[i] = substituteMarker;
        }
        drawMarker(Markers[i]);
    }

    for (int i=0; i<5; i++)
    {
        if(comparePoint(Blockers[i], robot.homePoint) == true)
        {
            Blockers[i] = substituteBlocker;
        }
        drawBlocker(Blockers[i]);
    }

    for(int counter=0; counter<3; counter++)
    {
        int x_path = Markers[counter].x - robot.homePoint.x;
        int y_path = Markers[counter].y - robot.homePoint.y;


    }

    return 0;
}