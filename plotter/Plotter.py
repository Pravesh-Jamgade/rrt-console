import pygame
from random import *
pygame.init()

WIDTH = 400
HEIGHT = 400
offset = 30
DIM = WIDTH, HEIGHT

run = True

if __name__ == "__main__":

	print("Usage: press 'y' or 'Y' to plor Branches.txt\n\t Otherwise 'n' or 'N' \n")
	branchOption = str(input())
	allowBranch = False
	if branchOption == 'y' or branchOption == 'Y':
		allowBranch = True

	pathFile = open("Path.txt", "r")
	points = []
	for line in pathFile:
		s = line.split(" ")
		a = s[0].strip()
		b = s[1].strip()
		points.append((float(a) , float(b)))
	obstacleFile = open("Obstacle.txt", "r")
	
	obstacles = []
	for line in obstacleFile:
		all = []
		s = line.split(" ")
		x1 = s[0].strip()
		y1 = s[1].strip()
		w = s[2].strip()
		h = s[3].strip()
		all.append(float(x1))
		all.append(float(y1))
		all.append(float(w))
		all.append(float(h))
		obstacles.append(all)	

	try:
		if allowBranch:
			branchFile = open("Branches.txt")
			branches = []
			for line in branchFile:
				all = []
				s = line.split()
				for i in range(len(s)-1):
					all.append((float(s[i]), float(s[i+1])))

				branches.append(all)

			allowBranch = True
	except:
		allowBranch = False

	
	window = pygame.display.set_mode(DIM)
	pygame.display.set_caption("Plot")
	while run:
		pygame.time.delay(3000)
		
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				run = False
		red = (255,0,0)# destination
		blue = (0,0,255)# source
		green = (0,255,0)# path obtained

		pygame.draw.ellipse(window, red, (points[0][0], points[0][1], 10, 10 ))
		pygame.draw.ellipse(window, blue, (points[len(points)-1][0], points[len(points)-1][1], 10, 10))

		
		for i in range(len(points)-1):
			if i == 0:
				continue
			pygame.draw.line(window, green, points[i],points[i+1], 4)

		# plot obstacles
		yellow = (200,200,0)
		countObstacles = len(obstacles)
		xcx = (250, 250, 0)
		for i in range(countObstacles):
			obstacle = obstacles[i]
			pygame.draw.rect(window, xcx, pygame.Rect(obstacle[0], obstacle[1], obstacle[2], obstacle[3]))
			#print(i, obstacle[0], obstacle[1], obstacle[2], obstacle[3])
			

		#plot branches
		if allowBranch:
			white = (255,255,255)
			black = (0,0,0)
			for line in range(len(branches)):
				for point in range(len(branches[line])-1):
					# print(branches[line][point], branches[line][point+1])
					pygame.draw.ellipse(window, white, (branches[line][point][0], branches[line][point][1], 2, 2 ))
					pygame.draw.ellipse(window, white, (branches[line][point+1][0], branches[line][point+1][1], 2, 2))

					#pygame.draw.line(window, white, branches[line][point], branches[line][point+1], 2)
				# print('\n')

		
		pygame.display.update()

		# break
	pygame.quit()
		


