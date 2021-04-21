#include <ncurses.h>
#include <unistd.h>
#include <time.h>

// array of cell state and neighbor count
int** cells; int** neighs;   
// cursor location and terminal size
int curX, curY, maxX, maxY;
// starting time when in play mode
clock_t start;
// half second interval
const unsigned duration = 500;

int swapState(int x, int y, int swp);
int countNeigh(int x, int y);
void stepTime();
void mvCursor(int);

int main(){
	// start/stop simulation
	bool end = false;

	// start window
	initscr();

	// initialize board of cells
	cells = new int*[COLS];
	for(int i = 0; i < COLS; ++i)
		cells[i] = new int[LINES];
	neighs = new int*[COLS];
	for(int i = 0; i < COLS; ++i)
		neighs[i] = new int[LINES];
	maxX = COLS; maxY = LINES;

	// enable user inputs (opt = user choice)
	int opt;
	keypad(stdscr, true);
	noecho();

	// start the game
	while(!end){
		// get input from player
		switch((opt = getch())){

			// switch cell state
			case 'x':
				// clear cell
				if(cells[curX][curY] == 1){
					swapState(curX, curY, 0);
					mvaddch(curY, curX, ' ');
				}
				// fill cell
				else{
					swapState(curX, curY, 1);
					mvaddch(curY, curX, 'x');
				}
				break;

			// start looping board update
			case 'p':
				// prevent many user inputs
				nodelay(stdscr, true);
				keypad(stdscr, false);

				// set up starting time for duration
				start = clock();

				// commence play mode until player quits out
				while((opt = getch()) != 'p' && opt != 'q'){
					// update board in half second increments
					if((clock() - start)/(CLOCKS_PER_SEC / 1000) >= duration){
						stepTime();
						// reset starting time
						start = clock();
					}
				}

				// player wants to quit the game rather than pause
				if(opt == 'q')
					end = true;
				// stop looping the board and enable user inputs
				nodelay(stdscr, false);
				keypad(stdscr, true);
				break;

			// proceed one step in updating board
			case 'n':
				stepTime();
				break;

			// quit the game
			case 'q':
				end = true;
				break;

			// move or idle the cursor
			default:
				mvCursor(opt);
				break;
		}
		// update cursor on board
		move(curY, curX);

		refresh();
	}

	endwin();

	// deallocate board
	for(int i = 0; i < maxX; ++i){
		delete [] cells[i];
		delete [] neighs[i];
	}
	delete[] cells;
	delete[] neighs;

	return 0;
}

// swaps a cell state
int swapState(int x, int y, int swp){
	int state;

	// kill the cell
	if(swp == 0){
		cells[x][y] = 0;
		state = 0;
	}
	// birth a cell
	else if(swp == 1){
		cells[x][y] = 1;
		state = 1;
	}
	// error, wrong input
	else
		state = -1;

	return state;
}

// count # of living cells surrounding current cell
int countNeigh(int x, int y){
	int count = 0;

	// add left cell
	if((x - 1) >= 0)
	{
		count += cells[x - 1][y];

		// add upper left cell
		if((y - 1) >= 0)
			count += cells[x - 1][y - 1];
	}
	// add right cell
	if((x + 1) < maxX){
		count += cells[x + 1][y];

		// add lower right cell
		if((y + 1) < maxY)
			count += cells[x + 1][y + 1];
	}
	// add upper cell
	if((y - 1) >= 0){
		count += cells[x][y - 1];

		// add upper right cell
		if((x + 1) < maxX)
			count += cells[x + 1][y - 1];
	}
	// add bottom cell
	if((y + 1) < maxY){
		count += cells[x][y + 1];

		// add bottom left cell
		if((x - 1) >= 0)
			count += cells[x - 1][y + 1];
	}

	return count;
}

// update cells in board by one step
void stepTime(){
	// count neighbors for all cells
	for(int y = 0; y < maxY; ++y){
		for(int x = 0; x < maxX; ++x)
			neighs[x][y] = countNeigh(x, y);
	}

	// swap state of each cell
	for(int y = 0; y < maxY; ++y){
		for(int x = 0; x < maxX; ++x){
			// cell dies
			if(neighs[x][y] < 2 || neighs[x][y] > 3){
				swapState(x, y, 0);
				mvaddch(y, x, ' ');
			}
			// cell is born
			else if(neighs[x][y] == 3){
				swapState(x, y, 1);
				mvaddch(y, x, 'x');
			}
		}
	}

	return;
}

// update coordinate of cursor according to movement
void mvCursor(int opt){
	if(opt == KEY_LEFT && curX != 0)
		curX -= 1;
	else if(opt == KEY_RIGHT && curX != (maxX - 1))
		curX += 1;
	else if(opt == KEY_UP && curY != 0)
		curY -= 1;
	else if(opt == KEY_DOWN && curY != (maxY - 1))
		curY += 1;

	return;
}
