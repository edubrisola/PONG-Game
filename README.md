# Pong Game

### Video  URL: https://youtu.be/PR1Gg_2VoR4

## Description

Hello, my name is Eduardo Brisola de Araújo and I am a student at UTFPR in Computer Engineering. Now, I am working in this Final Project for the conclusion of Harvard’s CS50 course.

In this program, I have created the game Pong. The premise of this game is that two players continuously prevent the ball from crossing the boundary of the grid. If the ball crosses the boundary of one player's side, the other player receives 1 point. The first player to reach a pre-determined number of points, wins.


## Building

To build the program, follow these steps:

 1. Ensure the PDCurses library is included. The necessary files are included in the project.
 2. Open the file main.c located in the PongGame folder to open the command line program in Visual Studio Code.
 3. Compile and run the main.c file.
 4. The build process is now complete, and you should be able to play the game.

## Controls

The game uses the following controls for player paddles and game adjustments:

- 'W': Player 1 Paddle Up

- 'S': Player 1 Paddle Down

- 'I': Player 2 Paddle Up

- 'K': Player 2 Paddle Down

- 'KEY_UP': Increases Game Speed (Decrease Delay by 5000 microseconds = 0.005s)

- 'KEY_DOWN': Decreases Game Speed (Increase Delay by 5000 microseconds = 0.005s)

- 'Q': Exits the Program

- 'P': Increases Points to Win

- 'L': Decreases Points to Win

## Game Mechanics

The game is designed for two players who control paddles on opposite sides of the screen. The paddles are moved up and down to intercept a ball that bounces around the screen. The objective is to prevent the ball from passing beyond the paddle. If the ball crosses the boundary behind a player's paddle, the opposing player scores a point. The first player to reach the pre-determined number of points wins the game.

The game also includes speed adjustments that allow players to make the game faster or slower using the arrow keys. The game speed affects the delay of the ball's movement, making it more challenging as the speed increases.

## Game Screens and Flow

### Initial Screen

When the game starts, the initial screen displays the title "PONG" along with credits and instructions to press 'ENTER' to start the game or 'O' to enter the options menu. The game will wait for the player to press the appropriate key to proceed.

### Options Menu

In the options menu, players can see the controls and the instructions for the game. They can also adjust game parameters such as the number of points required to win and the game speed. Players navigate the menu using the  'KEY_RIGHT' key and the 'BACKSPACE' key to go the next menu page or back to the previous menu.

###  Game Play Screen

Once the game starts, players control their paddles using the designated keys. The ball moves around the screen, and players must prevent it from passing their paddles. The score is displayed on the screen, along with the current speed setting.

###  End Game Screen

When a player wins, the game displays a screen announcing the winner. The game will log the result in a file called historicWin.txt.

This file keeps a record of all game results, including the winner and the final scores.

## historicWin.txt

This file stores the scores and victories of the matches. The format is as follows:

Winner: Player X

 || Score: Y X Y

Where:

- X: 1 or 2

- Y: Any non-negative integer

The file allows players to keep track of their performance over multiple games.

## Command Prompt Settings

###  *Important Note:

For some computers, the command prompt window size may differ from the one the game was designed for. To fix this, set the height to 32 and the width to 123. The 32x123 format is the original format of the game.

"BUGS" may occur if this adjustment is not made. Adjusting the window size ensures that the game display is as intended, providing the best gaming experience.

## Conclusion

This Pong game project is a simple yet enjoyable way to demonstrate the use of the curses library for creating a text-based user interface. It involves fundamental programming concepts such as handling user input, managing game state, and rendering graphics in the terminal.

The project was developed as part of the CS50 course and serves as an excellent example of how classic games can be implemented using modern programming techniques. By following the instructions in this README, you can build, customize, and play the game, making adjustments to game parameters to enhance your experience.

Feel free to explore the code and make modifications to further understand how the game works and possibly extend its functionality. Happy gaming!

