// NxN tic-tac-toes
#include <iostream>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to 
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/** 
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 * 
 */
 
int checkForWinner(char grid[], int dim);


/** 
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 * 
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current 
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);


/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    return grid[c + dim*r];
}

int idxToRow(int idx, int dim)
{
    return idx/dim /* Add Expression here to convert idx to appropriate row */ ;
}

int idxToCol(int idx, int dim)
{
    return idx%dim /* Add Expression here to convert idx to appropriate column */;
}

void printTTT(char grid[], int dim)
{
  //Prints out rows
  for(int i=0; i<dim; i++){
    cout << " ";
    for(int j=0; j<dim; j++){
      cout << getEntryAtRC(grid,dim,i,j);
      if(j!=dim-1){
        cout << " | ";
      }
    }
    cout <<endl;
    //Draws lines between rows
    if(i!=dim-1){
        for(int k=0; k < 3*dim+dim-1; k++){
          cout << "-";
      }
        cout << endl;
    }
  }
}

int checkForWinner(char grid[], int dim)
{
  bool temp=true;
  char p;
  //Check rows
  for(int i=0; i<dim;i++){
    p=getEntryAtRC(grid,dim,i,0);
    for(int j=0; j<dim;j++){
      //if element is anything other than the first letter of row flags false
      if(p != getEntryAtRC(grid,dim,i,j)){
          temp =false;
      }
    }

    //if all the elements in a row are a certain char outputs associated return statement
    
    if(temp){
      if(p=='X'){
        return 1;
      }else if(p=='O'){
        return 2;
      }
      
    }
    //resets flag
    temp=true;
  }

  //check columns (mostly same logic as checking rows)

  for(int i=0; i<dim;i++){
    p=getEntryAtRC(grid,dim,0,i);
    for(int j=0; j<dim;j++){
      if(p != getEntryAtRC(grid,dim,j,i)){
          temp =false;
      }
    }
    if(temp){
      if(p=='X'){
        return 1;
      } else if(p=='O'){
        return 2;
      }
    }
    temp=true;
  }
  //check diagonals separately

  //front diagonal check
  for(int i=0; i<dim;i++){
    p=getEntryAtRC(grid,dim,0,0);
    if(p!=getEntryAtRC(grid,dim,i,i)){
      temp=false;
    }
  }
  if(temp){
      if(p=='X'){
        return 1;
      } else if(p=='O'){
        return 2;
      }
    }
  temp=true;

  //back diagonal check
  for(int i=0; i<dim;i++){
    p=getEntryAtRC(grid,dim,0,dim-1);
    if(p!=getEntryAtRC(grid,dim,i,dim-(i+1))){
      temp=false;
    }
  }
  if(temp){
      if(p=='X'){
        return 1;
      } else if(p=='O'){
        return 2;
      }
    }
  //if no returns anywhere else continues game
  return 0;
}

bool checkForDraw(char grid[], int dim)
{
  //rowIsXandO and colIsXandO are temp arrays meant
  //to store a "1" in a given index if that row/col
  //contains a X and a O for given row/col
  //Ex. row 0 has a X and a O so rowIsXandO[0]=1

  int rowIsXandO[dim];
  int colIsXandO[dim];

  //Flags

  bool isX=false;
  bool isO=false;

  //Draw flag for comparison

  bool isDraw=true;

  //iterates row then individual elements to see if X and O exist

  for(int i=0; i<dim;i++){
    for(int j=0; j<dim;j++){
      if(getEntryAtRC(grid,dim,i,j)=='X'){
        isX=true;
      }
      if(getEntryAtRC(grid,dim,i,j)=='O'){
        isO=true;
      }
      if(isO && isX){
        rowIsXandO[i]=1;
      }
        
    }
    isO=false;
    isX=false;
      
  }

  //iterates column then individual elements to see if X and O exist

  for(int i=0; i<dim;i++){
    for(int j=0; j<dim;j++){
      if(getEntryAtRC(grid,dim,j,i)=='X'){
        isX=true;
      }
      if(getEntryAtRC(grid,dim,j,i)=='O'){
        isO=true;
      }
      if(isO && isX){
        colIsXandO[i]=1;
      }
        
    }
    isO=false;
    isX=false;
  }
  //checks if every row and column  doesnt have a X and O
  for(int i=0; i<dim;i++){
    if(!(rowIsXandO[i]==1 && colIsXandO[i]==1)){
        isDraw=false;
    }
  }
  return isDraw;
}



/**********************************************************
 *  Complete the indicated parts of main(), below. 
 **********************************************************/
int main()
{
  // This array holds the actual board/grid of X and Os. It is sized 
  // for the biggest possible case (11x11), but you should only 
  // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
  char tttdata[121];
    
  // dim stands for dimension and is the side length of the 
  // tic-tac-toe board i.e. dim x dim (3x3 or 5x5). 
  int dim;
  // Get the dimension from the user
  cin >> dim;
    
  int dim_sq = dim*dim;

  for(int i=0; i < dim_sq; i++){
    tttdata[i] = '?';
  }

  
  // Print one of these messages when the game is over
  // and before you quit
  const char xwins_msg[] = "X player wins!";
  const char owins_msg[] = "O player wins!";
  const char draw_msg[] =  "Draw...game over!";
  
  bool done = false;
  char player = 'X';
  // Show the initial starting board
  printTTT(tttdata, dim);
  int turn=0;
  while(!done){
    
    //**********************************************************
    // Get the current player's input (i.e. the location they want to
    // choose to place their mark [X or O]) and update the tttdata array.
    // Be sure to follow the requirements defined in the guide/writeup
    // for quitting immediately if the user input is out-of-bounds 
    // (i.e. not in the range 0 to dim_sq-1) as well as continuing to 
    // prompt for an input if the user chooses locations that have already
    // been chosen (already marked with an X or O).
    //**********************************************************

    // Add your code here for getting input

    //alternates turn

    if(turn%2==0){
      player = 'X';
    }else{
      player = 'O';
    }
    //initial input
    int loc;
    cout << "Player "<<player<<" enter your square choice [0-"<<dim_sq-1 <<"]: " << endl;
    cin >> loc;
    //error check for input
    while(loc>dim_sq-1 || loc<0 || tttdata[loc]!='?'){
      cout << "Error!" << endl;
      cout << "Player "<<player<<" enter your square choice [0-"<<dim_sq-1 <<"]: " << endl;
      cin >> loc;
    }
    
    tttdata[loc] = player;
    // Show the updated board if the user eventually chose a valid location
    // (i.e. you should have quit the loop and program by now without any 
    //  other output message if the user chosen an out-of-bounds input).
    printTTT(tttdata, dim);

    //**********************************************************
    // Complete the body of the while loop to process the input that was just
    //  received to check for a winner or draw and update other status, as 
    //  needed. 
    // 
    // To match our automated checkers' expected output, you must output 
    // one of the messages defined above using *one* of the cout commands 
    // (under the appropriate condition) below:
    //   cout << xwins_msg << endl;  OR
    //   cout << owins_msg << endl;  OR
    //   cout << draw_msg << endl;
    //
    // Note: Our automated checkers will examine a specific number of lines
    //  at the end of the program's output and expect to see the updated board
    //  and game status message.  You may certainly add some debug print  
    //  statements during development but they will need to be removed to 
    //  pass the automated checks.
    //**********************************************************
  
  //draw check

  if(checkForDraw(tttdata,dim)){
    done=true;
    cout<<draw_msg<<endl;
  }

  //check win

  int check = checkForWinner(tttdata, dim);

  if(check!=0){
    if(check ==1){
      cout <<xwins_msg<<endl;
      done=true;
    }
    if(check ==2){
      cout <<owins_msg<<endl;
      done=true;
    }
  }
  turn++;
  } // end while
  return 0;
}
