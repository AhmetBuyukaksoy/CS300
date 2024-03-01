
//  Created by Ahmet Büyükaksoy on 26.03.2023.
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include "Linkedliststack.h"
using namespace std;

struct Cell{
    bool visited = false;
    // x and y coordinates of the cell
    int x,y;
    // 1 means that there is a wall at that part of the cell
    int u = 1;
    int l = 1;
    int d = 1;
    int r = 1;
    bool wentLeft = false;
    bool wentRight = false;
    bool wentDown = false;
    bool wentUp = false;
    
    Cell(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int numofsides(){
        return u+l+d+r;
    }
    
    
    
};

std::ostream& operator<<(std::ostream& os, const Cell& c) {
    os << "x=" << c.x << " y=" << c.y << " l=" << c.l << " r=" << c.r << " u=" << c.u << " d=" << c.d;
    return os;
}
// creates a grid of size mxn
vector<Cell*> createVec(int m, int n){
    // maze is created here as a 1D vector, and its elements are reached through an index calculation formula, may change this to a 2D vector later  but its not necessary.
    vector<Cell*> maze;
    for (int i=0; i < m; i++){
        for (int j=0; j < n; j++){
             maze.push_back(new Cell(j,i));
        }
    }
    return maze;
}
bool allcellsvisited(vector<Cell*> maze){
    // checker for if all cell are visited
    bool all_visited = true;
    for (Cell* c: maze) {
        if (!c->visited){
            all_visited = false;
            break;
            }
    }
    return all_visited;
    
}

vector<Cell*> mazeGen(int m, int n){
    // initialize the cells in the maze as a 1d vector
    vector<Cell*>maze = createVec(m,n);
    // create a stack of cells
    Linkedliststack<Cell*> s;
    // push (0,0) cell to the stack
    maze[0]->visited = true;
    s.push(maze[0]);
    


    random_device rd;
    std::default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(1,4);

    // iterate until all cells are visited
    
    while(!allcellsvisited(maze)){

        bool foundValidCell = false;

        // case 1, if cell is on upper left corner and right & down are visited
        while(!foundValidCell){
            Cell *topElement = s.top();
            if(topElement->x == 0 && topElement->y ==m-1 && maze[n* topElement->y + topElement->x + 1]->visited && maze[n* (topElement->y - 1) + topElement->x]->visited) {
               // cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 2, if cell is on upper right corner and left & down are visited
            else if(topElement->x == n-1 && topElement->y == m-1 && maze[n* topElement->y + topElement->x - 1]->visited && maze[n* (topElement->y - 1) + topElement->x]->visited) {
             //   cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 3, if cell in on lower left corner and up & right are visited
            else if(topElement->x == 0 && topElement->y == 0 && maze[n* topElement->y + topElement->x + 1]->visited && maze[n* (topElement->y + 1) + topElement->x]->visited) {
              //  cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 4, if cell is on lower right corner and left & up are visited
            else if(topElement->x == n-1 && topElement->y == 0 && maze[n* topElement->y + topElement->x - 1]->visited && maze[n* (topElement->y + 1) + topElement->x]->visited) {
             //   cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 5, if cell is on left side and right & up & down are visited
            else if(topElement->x == 0 && topElement->y > 0 && topElement->y < m -1 && maze[n* topElement->y + topElement->x + 1]->visited && maze[n* (topElement->y + 1) + topElement->x]->visited && maze[n* (topElement->y - 1) + topElement->x]->visited) {
            //    cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 6, if cell is on upper side and left & right & down are visited
            else if(topElement->x >0 && topElement->x < n-1 && topElement->y == m-1 && maze[n* topElement->y + topElement->x + 1]->visited &&maze[n* topElement->y + topElement->x - 1]->visited && maze[n* (topElement->y - 1) + topElement->x]->visited) {
            //    cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 7, if cell is on right side and up & left & down are visited
            else if(topElement->x == n-1 && topElement->y > 0 && topElement->y < m-1 && maze[n* (topElement->y + 1) + topElement->x]->visited && maze[n* topElement->y + topElement->x - 1]->visited && maze[n* (topElement->y - 1) + topElement->x]->visited)  {
              //  cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            // case 8, if cell in on lower side and up & right & left are visited
            else if (topElement->x < n-1 && topElement->x > 0 && topElement->y == 0 && maze[n* (topElement->y + 1) + topElement->x]->visited && maze[n* topElement->y + topElement->x - 1]->visited && maze[n* topElement->y + topElement->x + 1]->visited) {
               // cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            //case 9, if element is in the middle and all neighbors are visited
            else if(topElement->x >0 && topElement->y > 0 && topElement->y < m-1 && topElement->x < n -1 &&maze[n* topElement->y + topElement->x - 1]->visited && maze[n* topElement->y + topElement->x + 1]->visited && maze[n* (topElement->y + 1) + topElement->x]->visited && maze[n* (topElement->y - 1) + topElement->x]->visited)  {
              //  cout << "Popped (" << topElement->x << "," <<topElement->y << ") from the stack!" << endl;
                s.pop();}
            else {foundValidCell = true;}
            
        }
        
        /* create a random number between 1-4 inclusive to determine the next cell to go, also check the validity of the random number to assure we are not going out of bounds (l=1, r=2, u=3, d=4)
        cout << "Current top element is: (" << s.top()->x << "," << s.top()->y << ")" ;
        */
        
            
            bool isRandomValid = false;
        // iterate until finding a valid (random) direction to advance
            while (!isRandomValid){
                
                Cell *topElement = s.top();

                int random_number = distribution(generator);
                // !! It may choose an invalid number one than once due to randomness, will deal with this later, but not that crucial.
                // The issue still exists , but I wont deal with it since even 100x100 mazes are generated really fast.
                // maze[x + n*y] = maze[x][y]
                
                switch (random_number) {
                    case 1:
                        if((topElement->x > 0 && topElement->l == 1 && !maze[n* topElement->y + topElement->x - 1]->visited)){
                            topElement->l = 0;
                            maze[n* topElement->y + topElement->x - 1]->r = 0;
                            maze[n* topElement->y + topElement->x - 1]->visited = true;
                            s.push(maze[n* topElement->y + topElement->x - 1]);
                            isRandomValid = true;
                          //  cout << " Going left from (" << topElement->x << "," << topElement->y <<")" << endl;
                        }
                        break;
                        
                        //else cout << "trying case 1  ";
                    case 2:
                        if(topElement->x < n-1 && topElement->r == 1 && !maze[n* topElement->y + topElement->x + 1]->visited){
                            topElement->r = 0;
                            maze[n* topElement->y + topElement->x + 1]->l = 0;
                            maze[n* topElement->y + topElement->x + 1]->visited = true;
                            s.push(maze[n* topElement->y + topElement->x + 1]);
                            isRandomValid = true;
                          //  cout << " Going right from (" << topElement->x << "," << topElement->y <<")" << endl;
                        }
                        
                        //else cout << "trying case 2 ";

                        break;
                    case 3:
                        if(topElement->y < m-1 && topElement->u == 1 && !maze[n* (topElement->y + 1) + topElement->x]->visited){
                            topElement->u = 0;
                            maze[n* (topElement->y + 1) + topElement->x]->d = 0;
                            maze[n* (topElement->y + 1) + topElement->x]->visited = true;
                            s.push(maze[n* (topElement->y + 1) + topElement->x]);
                            isRandomValid = true;
                         //   cout << " Going up from (" << topElement->x << "," << topElement->y <<")" << endl;
                        }
                        
                       // else cout << "trying case 3  ";

                        break;
                    case 4:
                        if(topElement->y > 0 && topElement->d == 1 && !maze[n* (topElement->y - 1) + topElement->x]->visited){
                            topElement->d = 0;
                            maze[n* (topElement->y - 1) + topElement->x]->u = 0;
                            maze[n* (topElement->y - 1) + topElement->x]->visited = true;
                            s.push(maze[n* (topElement->y - 1) + topElement->x]);
                            isRandomValid = true;
               //             cout << " Going down from (" << topElement->x << "," << topElement->y <<")" << endl;
                    }
                        
                       // else cout << "trying case 4  ";

                        break;
                        
                    default:
                        break;
                }
                }
        
    }
  //  cout << "Current top element is: (" << s.top()->x <<","<< s.top()->y << "), and the maze is complete" << endl;

    
    return maze;
// mazeGen ends
}

void writeMaze(vector<Cell*> maze,ostream& file){
    for(Cell* k : maze)
    file << "x=" << k->x <<" y=" << k->y <<" l=" << k->l << " r=" << k->r << " u=" << k->u << " d=" << k->d<< endl;

}
void resetVisits(vector<Cell*> maze){
    for (Cell* c: maze) {
        c->visited = false;
    }
}
bool isVisited(char side, vector<Cell*> maze, Cell* currCell,int n){
    if(side == 'l') return maze[n*(currCell->y) + currCell->x - 1]->visited;
    if(side == 'r') return maze[n*(currCell->y) + currCell->x + 1]->visited;
    if(side == 'u') return maze[n*(currCell->y + 1) + currCell->x]->visited;
    if(side == 'd') return maze[n*(currCell->y - 1) + currCell->x]->visited;


    return true;
        
}

Linkedliststack<Cell*> mazeSolve(vector<vector<Cell*>> mazeVec,int mazeID, int entryX, int entryY, int exitX, int exitY,int m, int n){
    Linkedliststack<Cell*>  pathStackInReverse;
    vector<Cell*> currMaze = mazeVec[mazeID-1];
    resetVisits(currMaze);
    Cell* currCell = currMaze[n* entryY + entryX];
    pathStackInReverse.push(currCell);
    while(pathStackInReverse.top() != currMaze[n* exitY + exitX]){
        currCell = pathStackInReverse.top();
        currCell->visited = true;

        
//         if all the sides on which there are no walls are visited, pop the cell off the stack
//         check validity of the cell
        if(currCell->l==1 && currCell->r==1 && currCell->u==1 && currCell->d==0 && isVisited('d', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==1 && currCell->r==1 && currCell->u==0 && currCell->d==1 && isVisited('u', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==1 && currCell->r==1 && currCell->u==0 && currCell->d==0 && isVisited('d', currMaze, currCell, n) && isVisited('u', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==1 && currCell->r==0 && currCell->u==1 && currCell->d==1 && isVisited('r', currMaze, currCell, n) )
            pathStackInReverse.pop();
        else if(currCell->l==1 && currCell->r==0 && currCell->u==1 && currCell->d==0 && isVisited('r', currMaze, currCell, n) && isVisited('d', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==1 && currCell->r==0 && currCell->u==0 && currCell->d==1 && isVisited('u', currMaze, currCell, n)&&isVisited('r', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==1 && currCell->r==0 && currCell->u==0 && currCell->d==0 && isVisited('u', currMaze, currCell, n) && isVisited('d', currMaze, currCell, n) && isVisited('r', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==1 && currCell->u==1 && currCell->d==1 && isVisited('l', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==1 && currCell->u==1 && currCell->d==0 && isVisited('l', currMaze, currCell, n) && isVisited('d', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==1 && currCell->u==0 && currCell->d==1 && isVisited('u', currMaze, currCell, n) && isVisited('l', currMaze, currCell, n))
            pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==1 && currCell->u==0 && currCell->d==0 && isVisited('u', currMaze, currCell, n) && isVisited('d', currMaze, currCell, n) && isVisited('l', currMaze, currCell, n))
                pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==0 && currCell->u==1 && currCell->d==1 && isVisited('l', currMaze, currCell, n)&&isVisited('r', currMaze, currCell, n))
                pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==0 && currCell->u==1 && currCell->d==0 && isVisited('r', currMaze, currCell, n) && isVisited('d', currMaze, currCell, n) && isVisited('l', currMaze, currCell, n))
                pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==0 && currCell->u==0 && currCell->d==1 && isVisited('l', currMaze, currCell, n) && isVisited('r', currMaze, currCell, n) && isVisited('u', currMaze, currCell, n))
                pathStackInReverse.pop();
        else if(currCell->l==0 && currCell->r==0 && currCell->u==0 && currCell->d==0 && isVisited('l', currMaze, currCell, n) && isVisited('r', currMaze, currCell, n) && isVisited('u', currMaze, currCell, n) && isVisited('d', currMaze, currCell, n))
            pathStackInReverse.pop();
        // can be moved from the cell
        else {
            if (currCell->l == 0 && !currCell->wentLeft && !isVisited('l', currMaze, currCell, n)){
                currCell->wentLeft = true;
               // cout << "Moving left from cell (" << currCell->x <<"," << currCell->y << ")" << endl;

                currCell = currMaze[n*(currCell->y) + currCell->x - 1];
                pathStackInReverse.push(currCell);
            }
            else if (currCell->r== 0 && !currCell->wentRight && !isVisited('r', currMaze, currCell, n)){
                currCell->wentRight = true;
               // cout << "Moving right from cell (" << currCell->x <<"," << currCell->y << ")" << endl;

                currCell = currMaze[n*(currCell->y) + currCell->x + 1];
                pathStackInReverse.push(currCell);
            }
            else if (currCell->u == 0 && !currCell->wentUp && !isVisited('u', currMaze, currCell, n)){
                currCell->wentUp = true;
              //  cout << "Moving up from cell (" << currCell->x<< "," << currCell->y << ")" << endl;

                currCell = currMaze[n*(currCell->y + 1) + currCell->x ];
                pathStackInReverse.push(currCell);
            }
            else if (currCell->d == 0 && !currCell->wentDown && !isVisited('d', currMaze, currCell, n)){
                currCell->wentDown = true;
             //   cout << "Moving down from cell (" << currCell->x<< "," << currCell->y << ")" << endl;

                currCell = currMaze[n*(currCell->y - 1) + currCell->x ];
                pathStackInReverse.push(currCell);
            }
                
        }
        
        
        
        
        
        
    }
    return pathStackInReverse;

}

int main() {
    // k num of mazes
    int k;
    // maze size rowxcol
    int m,n;
    cout << "Enter the number mazes: " ;
    cin >> k;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> m >> n;
   
    vector<vector<Cell*>> mazeVec;
    ofstream outfile;
    // open and write maze content into files ranging from 1 to k
    for (int i=1; i <= k ; i++){
        string maze_filename = "maze_" + to_string(i) + ".txt";
        outfile.open(maze_filename.c_str(), ios::out);
        
        if (!outfile) {
            cerr << "Failed to open file" << endl;
            return 1;
        }
        outfile << m << " " << n << endl;
        vector<Cell*>maze = mazeGen(m, n);
        mazeVec.push_back(maze);
        writeMaze(mazeVec[i-1], outfile);
        outfile.close();
    }
    cout << "All mazes are generated." << endl;
// ---------------------------- MAZE GENERATION IS DONE -------------------------------- //
    
    
    int mazeID, entryX, entryY, exitX,  exitY;

    cout << "Enter a maze ID between 1 and " << k << " inclusive to find a path: ";
    cin >> mazeID;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row) : ";
    cin >> entryX >> entryY;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row) : ";
    cin >> exitX >> exitY;

    
   // solver function (return the solution stack in reverse, may reverse it before mazeSolve returns or just reverse it in main?)
    Linkedliststack<Cell*> path = mazeSolve(mazeVec, mazeID, entryX, entryY, exitX, exitY, m, n);
    Linkedliststack<Cell*> a;
    // reverse the path stack into a dummy stack "a"
    while(!path.empty()){
        a.push(path.top());
        path.pop();
    }


    // write the path of the chosen maze to a file maze_mazeID_path_entryX_entryY_exitX_exitY.txt
    string solution_file = "maze_" + to_string(mazeID) + "_path_" + to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY) + ".txt";
    ofstream file;
    file.open(solution_file, ios::out);
        // print the content of stack "a" to the solution file
    while(!a.empty()) {
       file << a.top()->x << " " << a.top()->y << endl;
        a.pop();
   }
    cout << "Path written into file : " << solution_file << endl;
    
    // ---------------------------- MAZE SOLVING IS DONE -------------------------------- //

    
    return 0;
    

    

}


#include "Linkedliststack.cpp"


