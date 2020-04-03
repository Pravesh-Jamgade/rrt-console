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

1. run plotter/Plotter.py - requires "Path.txt", "Obstacles.txt" and less important "Branch.txt" file in plotter folder
2. provide 'y' or 'n' to plot include "Branch.txt" -- prefer 'n', whole scrren will become cloudy with other not traced points

![](https://github.com/Pravesh-Jamgade/rrt-console/blob/master/img/Screenshot%20from%202020-03-26%2018-46-55.png)
![](https://github.com/Pravesh-Jamgade/rrt-console/blob/master/img/Screenshot%20from%202020-04-01%2021-46-31.png)
