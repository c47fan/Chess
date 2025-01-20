# Chess
This is a C++ implementation of Chess that adheres to standard chess rules and includes features like move validation, check, checkmate, and stalemate detection. 

It allows two-player human modes as well as the ability to play against a computer with three varying levels of difficulty. Players can begin a new game or set up a custom initial board configuration. 

There is a text-based display provided in the console as well as a graphical interface created using Xlib.

## Building the game 
Prerequisites:
- A C++ compiler that supports C++14 or later (e.g. GCC or Clang). 
- The project uses a Makefile to simplify the build process, ensure that `make` is installed. 

Compiling the game: 
```
make
```
This creates an executable named `chess`. 

Run the game: 
```
./chess
```


## Gameplay 
View all possible commands: 
```
c
```

Start a new game: 
```
game <white player> <black player>
```
Where the parameters `white player` and `black player` can be `human`, `computer1`, `computer2` or `computer3`. The computer levels increase in difficulty with `computer1` being the easiest and `computer3` being the most difficult. 

Start a game with a custom initial configuration:
```
setup
```
Within setup, the user can create a unique board using the commands 
- `+ <piece> <square>` to place a piece on a square
- `- <square>` to remove a piece from a square
- `= <colour>` to make the colour's turn next
- `done` to leave setup mode. 

Move pieces (when a game is in progress):
```
move <origin square> <destination square>
```

Resign (when a game is in progress):
```
resign
```
