/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

char** read_maze(char* filename, int* rows, int* cols)
{

    
    ifstream ifile(filename);
    char buffer;
    ifile >> *rows;
    ifile >> *cols;
    char** maze=new char*[*rows];
    for(int i=0; i<*rows; i++){
      maze[i]=new char[*cols];
      for(int j=0; j<*cols;j++){
        ifile >> buffer;
        maze[i][j]=buffer;
      }
    }
    return maze;





}


void print_maze(char** maze, int rows, int cols)
{
    cout << rows << " " << cols << endl;
    // *** You complete **** CHECKPOINT 1
    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
        cout << maze[i][j];
      }
      cout << endl;
    }


}
