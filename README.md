Intermediate project for the programming course of electrical and computer engineering first year second semester
## Features
* You can only select dots with the same color
* Diagonals are not accepted
* If a square is selected it will remove all the dots that are the same color as the square from the board
* If there are any dots inside the square they will be removed too
* Updates the scores after each play
* When the key 'u' is pressed it will undo the current play and return to the last play
* When the key 'q' is pressed the game will close and generate a file with all the scores from that game
* When the key 'n' is pressed it will start a new game
* If no more moves are available, the colors on the board will shuffle randomly

## What you need to install
* SDL2
* SDL2_image
* SDL2_ttf

## For Ubuntu simply run:
```
$ sudo apt-get install libsdl2-dev
$ sudo apt-get install libsdl2-image-dev
$ sudo apt-get install libsdl2-ttf-dev
```

## To run the file run the command:
```
$ gcc main.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o ISTDots
$ ./ISTDots
```
