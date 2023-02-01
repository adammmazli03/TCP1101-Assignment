# Part 1

## Video Demo

[Video Demo](https://youtu.be/TBZlNZmIsqg).

## Minimum Requirements

### Completed

1. Function for Main Menu
2. Function for Setting and display the Game Board
3. Function for Save Game

### To Do

1. Game objects, attributes, movements and controls

## Additional Features

1. Can be played by more than one user.
2. Player can enter instructions many times if they mispell

## Contributions

### MUHAMMAD ADAM BIN MAZLI ZAKUAN

1. Create function for Main Menu

### AHMAD NUR IKHWAN BIN HAMID

1. Display and setting the Game Board

### MUHAMMAD AL-AMIN BIN MOHD NORMARZUKI

1. Function for save and load game

## Problems Encountered & Solutions

1. "redefinition of class Board" error appear when compile the main game file. | Remove "#include "boardDisplay.cpp"" from "newGame.cpp" file
2. "control reaches end of non-void function [-Wreturn-type]" error appear inside "newGame.cpp" and "loadGame.cpp" | remove 0 from "return 0;"
3. While making the Usr.txt loop to find if the Username input is incorrect, I could not find a way to make the " line " only read one value. | I decided to put the line outside the while loop and Filename.open(). Thus, the value return to it is " "(blank), then I use the if(usrtxt != line) outside the FileName.open(). Then it will return the value true to if and initiate the FileName2.open() and Thus creating a new user if the username has already been taken.
4. Input number less 0 and more 9 in number of zombies. | Create a do loop function to accept number 1<=x<=9.
5. Number of rows board and columns board display is not equal to what user input in settings. | Swap the dimX* and dimY* in for a loop of the building board.
