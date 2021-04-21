# Conway's Game of Life

## Description
This program is my own implementation of John Conway's Game of Life that uses the ncurses library for a text-based user interface. The game follows a set of rule to simulate cell automations throughout time to create complex shapes. This project was fun to work on, from learning the ncurses library to understanding the concept of the game and thinking of a design that replicates the cell automation process. It took a while for me to figure out how I should handle the interface update when it came to the simulation process, but having to play around with an online version of Conway's Game of Life helped me realize some changes that were needed to be changed, including the method of updating the cells on the interface.


## Instructions
* Arrow keys: move cursor around the interface
* Key 'X': clear/fill a cell on the interface
* Key 'P': start/pause simulation
* Key 'N': move one step forward in the simulation
* Key 'Q': quit the game


## Rules of the automation
* A cell follows the state "death" (cell removal) when the cell is surrounded by less than two or more than three "live cells" (filled cells)
* A cell stays "alive" if the cell is only surrounded by two or three live cells
* An empty cell can be "born" if three live cells surround it.
* The entire interface must be updated as a whole to simulate the changes


### Cell Vs Board Update
I've separated the counting of adjacent cells from the interface update in order to simulate the update as a whole unit. Having to combine the two processes would cause the interface to individually update the cells according to its updated interface, which would break some of the rules in the automation process. This separation would retain the rules of the automation and thus simulate the correct shapes according to the cell patterns made.
