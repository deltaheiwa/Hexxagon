Hexxagon

Create a clone of the classic DOS game [Hexxagon](https://hexxagon.com/). The game involves placing and moving pawns on a hexagonal board made up of small hexagons. Two players by cloning and moving their pawns convert opponent pawns into their own. The player with more pawns at the end of the game wins. The game ends when one player has no pawns left or the board runs out of empty spaces.

The application should support:

- Basic menu that appears upon launching the application.
- Ability to play alternately (hot seat) or against the computer.
- Ability to save the game to a file.
- Ability to load the game from a file.
- Remembering details of several top games (the criteria of “better” is open to interpretation by the student).

The menu should allow:
- Starting the game:
    - Against the computer;
    - Against another player taking turns.

- Loading a saved game.
- Displaying details of “best” saved games.

The computer player mode should incorporate a form of artificial intelligence implemented as a non-trivial set of rules by which the computer chooses its next move.

Improper usage of the application should result in appropriate error messages (e.g., during illegal moves).

After the game ends, there should be a screen displaying a short summary of the game and which player won.

The application must be implemented using the SFML GUI library.

Saving and loading the game should support operating on different files (with names specified by the user).