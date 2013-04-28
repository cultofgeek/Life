//////////////////////////////////////////////////////////////////
// LifeBoard class by Won You
//
// Implements Conway's rules 
// The bulk of the heart of the program is outlined by LifeBoard.cpp
// The class maintains an internal representation of all the 
// cell states in a matrix, which the window accesses in order to
// display in the Window
//
//////////////////////////////////////////////////////////////////

#ifndef _LIFEBOARD_H_
#define _LIFEBOARD_H_

#define NUM_CELLS       30   // This global variable specifies 
                             // the total number of cells 

#include <iostream>
#include <ctime>

using namespace std;

const int N_ROWS_MAX=50;
const int N_COLS_MAX=50;

class LifeBoard {
	public:
		LifeBoard(){
			/*These are the default values for the height and width*/
			nrow = NUM_CELLS;  
			ncol = NUM_CELLS;

			m_iWinX1 = m_iWinY1 = -1;
			m_iWinDX = m_iWinDY = 10;

			/*initialize the world matrix*/
			for (int i=0; i<nrow; i++)
				for (int j=0; j<ncol; j++)
					world[i][j]=' ';

		}
		~LifeBoard();

		//bool readWorld();
        void initializeWorld();
        char nextState(int x, int y); //calculate the next state for the given cell

        // Give the cell's state for the given coordinate
		char stateAt(int x, int y){ return world[x][y];	}

		// Toggles the state for the cell at the specified coordinate
        void ToggleAt(int x, int y);

		//Calls nextState for every cell in the world matrix
        void setWorld();
		void setGen( int g ) { gen = g; }       
		void RestartGame();				// Resets board and variables.

		int roundme( double x ){
			return  static_cast<int> ( x >= 0 ? x + 0.5 : x - 0.5 );
		}

		int boundedRand(int lower, int upper) {
		// Generates a random integer in the given interval [lower, upper]. 
		// Avoids using rand()%n, since the low-end bits of the 
		// output of rand() are often not reliably random; Stroustrup p.685.

			return roundme( (double(rand())/double(RAND_MAX))*(upper-lower) + lower);
		}

		bool valid(int i, int j)
		{
			return(i >= 0 && i < nrow && j >= 0 && j < ncol);
		}	


	protected:

		int		m_iWinX1, m_iWinY1;			// Coordinate of the win.
		int		m_iWinDX, m_iWinDY;			// Direction of the win.

		int		nrow;
		int		ncol;
		int		gen;						//the number of generations
		char	world[N_ROWS_MAX][N_COLS_MAX];	// The board.
 
};

#endif