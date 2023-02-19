# Part 2

## Video Demo

[Video Demo](https://youtu.be/TBZlNZmIsqg).

## Minimum Requirements

### Completed

1. Function for Main Menu
2. Function for Setting and display the Game Board
3. Game objects, attributes, movements and controls
4. Function for Save Game

## Additional Features

1. Main Menu
2. Can be played by more than one user.
3. Player can enter instructions many times if they mispell
4. Coordinates for Alien and Zombies
5. Game instructions 
6. Game auto-save when player exit mid-game

## Contributions

### MUHAMMAD ADAM BIN MAZLI ZAKUAN

1. Create funtion command, generateZombie, movePlayer, winCheck, alienDie, playAgain

### AHMAD NUR IKHWAN BIN HAMID

1. Create function movePlayer, moveZombies, encounterItem, changeDirection, generateObjects

### MUHAMMAD AL-AMIN BIN MOHD NORMARZUKI

1. Create struct myObj
2. Create function initload, displayloadBoard, resetAlien

## Problems Encountered & Solutions

1. Trouble with a lot of files. | Combine all files into one file.
2. During load game, Amin encountered problem where the value cannot pass to the variable. | He extract file in string form and converted to integer to match to parameter of displayBoard.
3. When Amin tried to take object from saved board in the saved file, he encounterd that the objects extracted was inclusive with separator ('|'). | He made a for loop and made a if-else statement which it only except everything except separator. Thus, converting from every object to char.
4. When Amin was trying to extract the value of constructor (health, attack, range ,x_axis, y_axis), he couldn't extract the value like he wanted. | Amin changed how the saved game saves the file by ending the statement and putting it in a new row.Thus it makes it more easier to extract the constructor.
5. When the zombie randomly moving, the zombie will move outside the board when at the corner of the board. | Ikhwan create vector int which will push_back the number of valid movement the zombie can go. So, zombie will get random number from the vector.
6. When generate zombies' attribute, sometimes the zombie stacked with other zombies' coordinate or stacked with alien' coordinate. | Make bool for the valid coordinate to spawn the zombie.  
