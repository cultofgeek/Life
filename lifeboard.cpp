#include "stdafx.h"
#include <memory.h>
#include "lifeboard.h"


LifeBoard::~LifeBoard() {}


/*Initialize the states of each cell randomly*/
void LifeBoard::initializeWorld(){

srand(time(0));  //seed using the current time

int randomizer=boundedRand(0, 1); 

           
	for (int i=0; i<nrow; i++){

		for (int j=0; j<ncol; j++){
		
   		   randomizer=boundedRand(0, 1); 
   		   
		   if (randomizer == 1)
			world[i][j] = ' ';
		   else
		    world[i][j] = '*';
		}

	}
}


/*/////////////////////////////////////////////////////////
Next State:   The transition of states is computed here.
              If there are exactly three adjacent 
			  cells that are alive then the cell under
			  consideration either remains alive or 
			  becomes alive.  In all other cases, it's dead
*//////////////////////////////////////////////////////////
char LifeBoard::nextState(int rowPos, int colPos)
{
  int i,j, count=0, state;

   //Rule1: The current cell is dead      		
   if (world[rowPos][colPos] == ' ')
	 state = 1;   

   //Rule2: The current cell is alive
   else if (world[rowPos][colPos] == '*')
     state = 2;

   else state = 0;
   
      //Examine each of its neighbors
  	 for(i=rowPos-1; i<=rowPos+1; i++){ 
		for (j=colPos-1; j<=colPos+1; j++){
		   
		   //Count the number of live neighbors
		   if (valid(i,j) && world[i][j]=='*'){
		      
		      if (i !=rowPos || j!=colPos)
		      ++count;
		   }

		}
        
	 }
//	 cout << "The count for" << rowPos <<","<< colPos <<"is " << count << endl;
	 if (state==1){ 
	    if (count==3) return '*';
 	    else return ' ';
 	 }   
     else if (state==2){
        if (count==2 || count==3) return '*';
        else return ' ';
     }
     else return '!';
     
     
}//end of nextState


void LifeBoard::setWorld()  
{
  char temp[N_ROWS_MAX][N_COLS_MAX];
  
   
    //for each cell, examine what its next state should be
    //then store that result into a temporary matrix
   	for (int i=0; i<nrow; i++){
   	
   		for (int j=0; j<ncol; j++){
   		
		    temp[i][j] = nextState(i,j); 
		}
	}

 	//Synchronize the temporary matrix with the regular matrix
   	for (int m=0; m<nrow; m++){
   	
   		for (int n=0; n<ncol; n++){
   		
		    world[m][n] = temp[m][n]; 
		}
	}


  
}//end of setWorld

/*///////////////////////////////////////////////////////
 Function: Toggle the state for the cell at the specified coordinate
		   This function provides an interface for the events that are 
           registered by the window
*////////////////////////////////////////////////////////
void LifeBoard::ToggleAt(int x, int y){

  if ( valid(x,y) ){
		if (world[x][y]=='*')
			world[x][y] = ' ';
		else
			world[x][y] = '*';
		}

}	

void LifeBoard::RestartGame() {

	m_iWinX1 = m_iWinY1 = -1;
	m_iWinDX = m_iWinDY = 10;

	for (int i=0; i<nrow; i++)
		for (int j=0; j<ncol; j++)
			world[i][j] = ' ';
}


