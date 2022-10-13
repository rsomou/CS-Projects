/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;


int maze_search(char**, int, int);


int main(int argc, char* argv[]) {
  int rows, cols, result;
  char** mymaze=NULL;
  const char* invalid_char_message = "Error, invalid character.";
  const char* invalid_maze_message = "Invalid maze.";
  const char* no_path_message = "No path could be found!";

  if(argc < 2)
  {
      cout << "Please provide a maze input file" << endl;
      return 1;
  }
  
  //reads in maze from filename contained in argv[1]
  mymaze=read_maze(argv[1], &rows, &cols);


  int hasOneS=0;
  int hasOneF=0;
  
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      if(mymaze[i][j]=='S'){
        hasOneS++;
      }
      if(mymaze[i][j]=='F'){
        hasOneF++;
      }
      if(mymaze[i][j]!='S' && mymaze[i][j]!='.' && mymaze[i][j]!='F' && mymaze[i][j]!='#'){
        cout << invalid_char_message << endl;
        //deallocates maze if invalid chars exist
        for(int i=0; i<rows; i++){
          delete [] mymaze[i];
        }
        delete [] mymaze;
        return 0;
      }
    }
  }
  if(hasOneS!=1 || hasOneF!=1){
    //deallocates if more or less than one finish and start
    for(int i=0; i<rows; i++){
      delete [] mymaze[i];
    }
    delete [] mymaze;
    cout << invalid_maze_message << endl;
    return 0;
  }

    
    //performs breath first search and computes edge cases if invalid maze is given
    result=maze_search(mymaze, rows, cols);
    
  if(result==1){
    print_maze(mymaze, rows, cols);
  } else if(result==0){
    cout << no_path_message << endl;
  } else if(result==-1){
    cout << invalid_maze_message << endl;
  }

  //deallocates maze after completetion

  for(int i=0; i<rows; i++){
      delete [] mymaze[i];
  }
  delete [] mymaze;

  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 * don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
  Queue q(rows*cols);

  Location loc;

  Location start;

  bool foundFinish=false;

  //dynamically allocates memory for Precursor and isExplored arrays

  bool** isExplored=new bool*[rows];
  for(int i=0; i<rows; i++){
    isExplored[i]=new bool[cols];
  }

  Location** Precursor=new Location*[rows];
  for(int i=0; i<rows; i++){
    Precursor[i]=new Location[cols];
  }

  // finds start and initializes Precursor and isExplored arrays
  for(int i=0; i<rows;i++){
    for(int j=0; j<cols;j++){
      if(maze[i][j]=='S'){
        start.col=j;
        start.row=i;
        q.add_to_back(start);
        isExplored[i][j]=true;
      }
      isExplored[i][j]=false;
      Precursor[i][j].row=-1;
      Precursor[i][j].col=-1;
    }
  }

  if(start.row==-1 && start.col==-1){
    return -1;
  }
  
  // BFS algorithm
  while(!q.is_empty()){
    loc=q.remove_from_front();
    
    if(loc.row!=0 && maze[loc.row-1][loc.col]!='#' && isExplored[loc.row-1][loc.col]!=true){
      if(maze[loc.row-1][loc.col]=='F'){
        foundFinish=true;
        break;
      }
      Location N;
      N.row=loc.row-1;
      N.col=loc.col;
      isExplored[N.row][N.col]=true;
      Precursor[N.row][N.col]=loc;
      q.add_to_back(N);
    }

    if(loc.row!=rows-1 && maze[loc.row+1][loc.col]!='#' && isExplored[loc.row+1][loc.col]!=true){
      if(maze[loc.row+1][loc.col]=='F'){
        foundFinish=true;
        break;
      }
      Location S;
      S.row=loc.row+1;
      S.col=loc.col;
      isExplored[S.row][S.col]=true;
      Precursor[S.row][S.col]=loc;
      q.add_to_back(S);
    }

    if(loc.col!=0 && maze[loc.row][loc.col-1]!='#' && isExplored[loc.row][loc.col-1]!=true){
      if(maze[loc.row][loc.col-1]=='F'){
        foundFinish=true;
        break;
      }
      Location W;
      W.row=loc.row;
      W.col=loc.col-1;
      isExplored[W.row][W.col]=true;
      Precursor[W.row][W.col]=loc;
      q.add_to_back(W);
    }
    
    if(loc.col!=cols-1 && maze[loc.row][loc.col+1]!='#' && isExplored[loc.row][loc.col+1]!=true){
      if(maze[loc.row][loc.col+1]=='F'){
        foundFinish=true;
        break;
      }
      Location E;
      E.row=loc.row;
      E.col=loc.col+1;
      isExplored[E.row][E.col]=true;
      Precursor[E.row][E.col]=loc;
      q.add_to_back(E);
    }

  }

  //return 0 if no finish is found
  if(!foundFinish){
  //deallocates arrays if no finish (prevents memory leak)
    for(int i=0; i<rows;i++){
      delete [] isExplored[i];
      delete [] Precursor[i];
    }
    delete [] isExplored;
    delete [] Precursor;

    return 0;
  }

  //backtrack maze and fill in correct path with stars
  while(loc.col!=start.col || loc.row!=start.row){
    maze[loc.row][loc.col]='*';
    loc=Precursor[loc.row][loc.col];
  }
  //deallocate arrays
  for(int i=0; i<rows;i++){
    delete [] isExplored[i];
    delete [] Precursor[i];
  }
  delete [] isExplored;
  delete [] Precursor;

  return 1;
}
