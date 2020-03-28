#ifndef RRT_H
#define RRT_H
#include <bits/stdc++.h>
//#include<QJsonObject>
//#include<QJsonDocument>
//#include<QJsonArray>
//#include<QUuid>

using namespace std;

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

#include <sys/stat.h>
#include <fstream>

#ifndef CONSTANT
#define CONSTANT value
const double WIDTH = 400.0;
const double HEIGHT = 400.0;
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int TOP = 8;
const int BOTTOM = 4;
const double GOAL_THRESOLD = 5.0;
const char* RRT_PATH = "Path.txt";
const char* OBSTACLE_PATH = "Obstacle.txt";
#endif


namespace IRRT{
	class RRTMain;
	class Cobs;
}

typedef pair<double, double> vertex;

/*!
\class
The obstacle definition.
startx, starty, endx, endy, [optional = CoWidth], [optional = CoHeight]
CoWidth and CoHeight of obstacle will be set to default value (5.0)if not provided.
*/
class Cobs{

	public:
		vertex dStart;
		vertex dEnd;
        double CoWidth, CoHeight;
        double startx, starty, endx, endy;
        double xmin, xmax, ymin, ymax;
	private:
		
	public:

        Cobs(double startX, double startY, double CoWidth=5.0, double CoHeight=5.0):
		CoWidth(CoWidth), CoHeight(CoHeight){
			dStart = make_pair(startX, startY);
			dEnd = make_pair(startX + CoHeight, startY + CoWidth);
		};

		// check bbox of obstacle, adjust if goes beyond C-Space
		void ResetBoundingboxRange(){
			dStart.first = dStart.first< 0 ? 0: dStart.first; 
			dStart.first = (dStart.first >= WIDTH) ? WIDTH-1: dStart.first;

			dStart.second = dStart.second< 0 ? 0: dStart.second;
			dStart.second = dStart.second >= HEIGHT ? HEIGHT-1: dStart.second;

			dEnd.first = dEnd.first< 0 ? 0: dEnd.first;
			dEnd.first = dEnd.first >= WIDTH ? WIDTH-1: dEnd.first;

			dEnd.second = dEnd.second< 0 ? 0: dEnd.second;
			dEnd.second = dEnd.second>= HEIGHT ? HEIGHT-1: dEnd.second;
		}

        vector<vertex> getAllCorners(){
                vector<vertex> allCorners;
                allCorners.push_back(dStart);

                vertex rightOfStart = make_pair(dEnd.first, dStart.second);
                allCorners.push_back(rightOfStart);

                allCorners.push_back(dEnd);

                vertex leftOfEnd = make_pair(dStart.first, dEnd.second);
                allCorners.push_back(leftOfEnd);

                return allCorners;
         }

		vector<vertex> getBoundingbox(){
			dEnd.first = dStart.first + CoWidth;
			dEnd.second = dStart.second + CoHeight;

			vector<vertex> BoundingBox;
			BoundingBox.push_back(dStart);
			BoundingBox.push_back(dEnd);
			return BoundingBox;
		}

        double getPointOutCode(double x1, double y1){
			int ret = INSIDE;
			if(x1 < xmin){
				ret |= LEFT;
			}
			else if(x1 > xmax){
				ret |= RIGHT;
			}

			if(y1 < ymin){
				ret |= BOTTOM;
			}
			else if(y1 > ymax){	
				ret |= TOP;
			}
			return ret;
		}

        void getNewCo(int &op1, double& x, double& y, double x1, double y1, double x2, double y2){
			if(op1 & TOP){
				x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
				y = ymax;
			}
			else if(op1 & BOTTOM){
				x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
				y = ymin;
			}
			else if(op1 & RIGHT){
				y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
				x = xmax;
			}
			else if(op1 & LEFT){
				y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
				x = xmin;
			}
		}

        bool sutherLand(double x0, double y0, double x1, double y1){
            int op0 = getPointOutCode(x0, y0);
            int op1 = getPointOutCode(x1, y1);

            while(true){
                if(!(op0 | op1)){
                    // inside
                    return true;
                    break;
                }
                else if(op0 & op1){
                    // outside
                    return false;
                    break;
                }
                else {
                    double x,y;
                    int op = max(op0, op1);
                    if(op & TOP){
                        x = x0 + (x1-x0) * (ymax-y0)/(y0-y1);
                        y = ymax;
                    }
                    else if(op & BOTTOM){
                        x = x0 + (x1-x0)*(ymin-y0)/(y1-y0);
                        y = ymin;
                    }
                    else if(op & RIGHT){
                        y = y0 + (y1-y0)*(xmax-x0)/(x1-x0);
                        x = xmax;
                    }
                    else if(op & LEFT){
                        y = y0 + (y1-y0)*(xmin-x0)/(x1-x0);
                        x = xmin;
                    }

                    if(op == op0){
                        x0 = x;
                        y0 = y;
                        op0 = getPointOutCode(x0,y0);
                    }else{
                        x1 = x;
                        y1 = y;
                        op1 = getPointOutCode(x1, y1);
                    }
                }
            }
        }

        bool IsInPath(double x1, double y1, double x2, double y2){
			startx = dStart.first;
			starty = dStart.second;
			endx = dEnd.first;
			endy = dEnd.second;
			
			// cout<<startx<<" - "<<starty<<" - "<<endx<<" - "<<endy<<endl;
			// getting min and max of x and y for quadrilateral
			xmin = min(startx, endx);
			xmax = max(startx, endx);
			ymin = min(starty, endy);
			ymax = max(starty, endy);
            return sutherLand(x1,y1,x2,y2);
		}
};

ostream& operator<<(ostream& os, const Cobs co){
        os << '('<<co.startx<<','<<co.starty<<", "<<co.endx<<", "<<co.endy<<")"<<" ";
		return os;
	}

ostream& operator<<(ostream& os, const vertex v){
    os<< v.first<<" "<<v.second;
	return os;
}

class Node{
	public:
		Node* parent;
		vector<Node*> childrens;
		vertex position;

        Node(): parent(), childrens(), position() {};
};

    ostream& operator<<(ostream& os, const Node* a){
        os <<a->position.first<<' '<<a->position.second<<'\n';
		return os;
	}

/*!
\class RRTMain

*/
class RRTMain{
	public:	
		// @Param { width, height, no. of obstacles}
        RRTMain(vector<Cobs> &AllObstacles, double width = WIDTH, double height = HEIGHT):
		width(width), height(height), obstacles(AllObstacles), seenNodes(), path() {
			this->root = new Node; 
			this->goal = new Node;
            this->stepSize = 5.0;
			this->maxIterations = 1000;
			this->lastNode = new Node;
		};

	private:
        double width, height;
		vector<Cobs> obstacles;
		Node* root, *goal, *lastNode;
		vector<Node*> seenNodes;
		int maxIterations;
        double stepSize;
		vector<Node*> path;

	public:
		void welcome(){
            printf("\nC-Space Width- %.1lf,  Height- %.1lf, No. Of Obstacles- %.1d \n", width, height, int(obstacles.size()));
		}

		vertex getRandomPosition(){
            return make_pair( drand48() * width, drand48() * height );
            //return make_pair( (rand()% int(width)) * 1.0 + 1, (rand()% int(height)) * 1.0 + 1);
		}

		bool validVertex(vertex& point){
            return (point.first > 0 and point.first <= width) and (point.second > 0 and point.second <= height);
		}

		vertex getRandomNode(){
			vertex point = getRandomPosition();
            if(validVertex((point))){
               return point;
            }
            return make_pair(width, height);
        }

        void mul(vertex& a, double scalar){
            a.first = a.first * scalar;
            a.second = a.second * scalar;
		}

		vertex add(vertex a, vertex b){
            return make_pair(a.first + b.first, a.second + b.second);
		}

        void init(vertex start, vertex goal, double stepSize = 5, int maxIterations = 1000){
			if(!validVertex(start)) {
				cout<<"\nstart vertex not in range\n";
			}
			else {
				this->root->position = start;
				// adding to collection
				this->seenNodes.push_back(this->root);
			}

			if(!validVertex(goal)) {
				cout<<"\ngoal vertex not in range\n";
			}
			else {
				this->goal->position = goal;
			}

			this->stepSize = stepSize;
			this->maxIterations = maxIterations;
		}

        double getDistance(vertex& u, vertex& v){
            double a = u.first-v.first;
            double b = u.second-v.second;
			return (sqrt(a*a+b*b));
		}

		Node* getNearestNode(vertex& toPos){
            double minDistance = 1e+9;
            Node* node = new Node;
            for(int i=0; i< int(this->seenNodes.size()); i++){
				Node* fromNode = seenNodes[i];
				vertex fromPos = fromNode->position;
                double dist = getDistance(fromPos, toPos);
				if(dist < minDistance){
					node = fromNode;
					minDistance = dist;
				}
			}
			return node;
		}

        Node* getNewConfiguration(vertex& nearestVert, vertex& randVert){
            vertex vectorBetween = make_pair(randVert.first - nearestVert.first, randVert.second - nearestVert.second);
            double normalMagnitude = sqrt(vectorBetween.first * vectorBetween.first + vectorBetween.second * vectorBetween.second);
            vertex unitVector = make_pair(vectorBetween.first/normalMagnitude, vectorBetween.second/normalMagnitude);
            mul(unitVector, stepSize);
            vertex result = add(nearestVert, unitVector);
            Node *newConf = new Node;
			newConf->position = result;
			return newConf;
		}	

        bool IsThereObstacle(double x1, double y1, double x2, double y2){
			for(auto obstacle: this->obstacles){
                if(obstacle.IsInPath(x1, y1, x2, y2)) return true;
			}
			return false;
		}

		bool checkForObstacle(vertex& newConfPos, vertex& nearestPos){
            double ax, ay, bx, by;
			
			ax = newConfPos.first;
			ay = newConfPos.second;

			bx = nearestPos.first;
			by = nearestPos.second;

			return IsThereObstacle(ax, ay, bx, by);
		}

		void run(){
            cout<<"Source: "; cout<<this->root;
            cout<<"Destination: "; cout<<this->goal;
            cout<<'\n';

            int i=0;
            for(i=0; i< maxIterations; i++){

                // get Random Node
                vertex randomVertex = getRandomNode();
                if(randomVertex.first == width and randomVertex.second == height) continue;

                    // look for nearest node from randomNode, from seen nodes until now
                    Node* nearestNode = getNearestNode(randomVertex);
                    if(getDistance(nearestNode->position, randomVertex) > stepSize)
                    {
                        // if distance is greater than step size, go for new configuration
                        Node* newConfNode = getNewConfiguration(nearestNode->position, randomVertex);

                        if(! checkForObstacle(newConfNode->position, nearestNode->position)){

                            // if there's no obstacle, newConf becomes child of nearest
                            nearestNode->childrens.push_back(newConfNode);
                            newConfNode->parent = nearestNode;
                            this->seenNodes.push_back(newConfNode);
                            this->lastNode = newConfNode;
                        }else{

                        }
                    }

                    if(getDistance(this->lastNode->position, this->goal->position) < GOAL_THRESOLD){
                        cout<<"Reached\n";
                        break;
                    }

			}

            if(i == maxIterations){
                cout<<"Iterations done\n";
            }

			Node* traversalNode;
			if(getDistance(this->lastNode->position, this->goal->position) < GOAL_THRESOLD){
                traversalNode = this->lastNode;
			}
			else{
				// get nearest node to lastNode
				traversalNode= getNearestNode(this->lastNode->position);
			}

            // trace back path
            cout<<"Trace Path\n";
			while(traversalNode!=NULL){
                cout<<traversalNode; cout<<" \n";
                path.push_back(traversalNode);
				traversalNode = traversalNode->parent;
			}

		}

        void tracePath(){
            // cout<<this->obstacles[0];
            // cout<<this->obstacles[0].dStart.first<<" "<<this->obstacles[0].dStart.second<<endl;
            // cout<<this->obstacles[0].CoWidth<<" "<<this->obstacles[0].CoHeight<<endl;

            for(int i=0; i< int(this->seenNodes.size()); i++){
                Node* a = seenNodes[i];
                cout<<"Node: ";
                cout<<a;
                cout<<endl;

                cout<<"Childrens: ";
                for(auto b: a->childrens){
                    cout<<b; cout<<" ";
                }
            }
        }

        inline bool fileExists (const std::string& name) {
          struct stat buffer;
          return (stat (name.c_str(), &buffer) == 0);
        }

        void save(){
            char cCurrentPath[FILENAME_MAX];
            if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
            {
                cout<< errno;
                return;
            }
            cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

            // traced path to file
            cout<<"Path Write back to File: "<<this->path.size()<<endl;
            ofstream fileStream(RRT_PATH, ios::out | ios::trunc);
            fileStream<<this->goal;

            for(int i=0; i< int(path.size()); i++){
                   Node* cur = path[i];
                   fileStream<<cur;
            }
            fileStream.close();

            // input obstacles to file
            cout<<"Obstacles Write back to File: "<<this->obstacles.size()<<endl;
            fileStream.open(OBSTACLE_PATH, ios::out | ios::trunc);

            for(auto obstacle: obstacles){
                fileStream<<obstacle.dStart<<" "<<obstacle.CoWidth<<" "<<obstacle.CoWidth;
                fileStream<<'\n';
            }

            fileStream.close();
        }
};

#endif
