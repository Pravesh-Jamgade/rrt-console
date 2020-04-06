# rrt-console

Implementation of Rapidly exploring random trees.
![RRT Paper](https://en.wikipedia.org/wiki/Rapidly-exploring_random_tree)

Description:

1. main.cpp  contains example to add obstacle and run algorithm.
2. class Cobs- defines obstacle
Parameters required - startx, starty, width of obstacle, height of obstacle

3. class RRTMain - contains rrt implementation
Parameters required - vector contaning all the of obstacles, width of cspace, height cspace  

4. to run algorithm, fisrt need to call init() method using RRTMain object.
   Parameters - start location, goal location, step size and maxIteration
   
5. Call run() method using RRTMain object
6. Call save() methos using RRTMain object.
7. Path.txt, Obstacles.txt and Branches.txt will be generated, containing x,y co-ordinate's
Path.txt contains out main route.
Obstacle.txt contains x,y,width,height of obstacle
Branches.txt contains other explored branches

Environment:

Algorithm written in c++. Output is plotted with python3 and pygame.
Set python environment with given requirements.txt file in plotter/ folder.

Plot Result:

1. compile and run main.cpp. 
2. python plotter will ask for whether to plot "Branch.txt", provide 'y' or 'n'  -- prefer 'n', as when iterations are large whole scrren will become cloudy with other branches. For small number of iterations it's okay.


![](https://github.com/Pravesh-Jamgade/rrt-console/blob/master/img/Screenshot%20from%202020-03-26%2018-46-55.png)
![](https://github.com/Pravesh-Jamgade/rrt-console/blob/master/img/Screenshot%20from%202020-04-01%2021-46-31.png)
![](https://github.com/Pravesh-Jamgade/rrt-console/blob/master/img/Screenshot%20from%202020-04-04%2023-28-15.png)
