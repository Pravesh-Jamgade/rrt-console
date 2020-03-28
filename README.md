# rrt-console

Implementation of Rapidly exploring random trees.

Run:

1. main.cpp  contains example to add obstacle and run algorithm.
2. class Cobs- defines obstacle
Parameters required - startx, starty, width of obstacle, height of obstacle

3. class RRTMain - contains rrt implementation
Parameters required - vector contaning all the of obstacles, width of cspace, height cspace  

4. to run algorithm, fisrt need to call init() method using RRTMain object.
   Parameters - start location, goal location, step size and maxIteration
   
5. Call run() method using RRTMain object
6. Call save() methos using RRTMain object.
7. Path.txt and Obstacles.txt will be generated, containing x,y co-ordinate's.

Plot Result:

1. run plotter/Plotter.py - requires "Path.txt" and "Obstacles.txt" file in plotter folder

NOTE: Although application is written in qt, it is still a console application, not using any qt features. Improvements need to be added to make it fully functional qt application.
