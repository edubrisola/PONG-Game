#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Struct Type gameData
typedef struct gameData
{
    int lastch;

    unsigned int paddle1y;
    unsigned int paddle2x;

    unsigned int paddle1x;
    unsigned int paddle2y;

    unsigned int ballx;
    unsigned int bally;

    unsigned int points1;
    unsigned int points2;

    int pointstotal;
    int pointswin;

    int start;

    int velocity;
    int dial;

    int lock;

    int results;

    int directionx;
    int directiony;

} gameData;

void initScreen();
void handleInputs(gameData * game);
void InitialScreen(gameData * game);
void OptionsScreen(gameData * game);
void OptionsScreen2(gameData * game);
void drawScreen(gameData * game);
void BallMovement(gameData * game);
void FinalScreen1(gameData * game);
void FinalScreen2(gameData * game);
void historicWin(gameData * game);

// Main
int main(int argc, char *argv[])
{
    // Starting game with Data Type gameData
    gameData *game = malloc(sizeof(gameData));

    // Starting the screen and Variables
    initScreen();

    game->lastch = -1;

    // Player 1 Paddle Starting Position
    game->paddle1y = 15;
    game->paddle1x = 4;

    // Player 2 Paddle Starting Position
    game->paddle2y = 15;
    game->paddle2x = 96;

    // Ball's Starting Position
    game->bally = 15;
    game->ballx = 50;

    // Points from the Players
    game->points1 = 0;
    game->points2 = 0;

    game->pointstotal = 0;
    game->pointswin = 5;

    // Velocity
    game->velocity = 50000;

    // Results
    game->results = 0;

    // Lock
    game->lock = 0;

    // Direction
    time_t mytime = time(NULL);
    srand(mytime);

    game->directionx = rand() % 2;
    game->directiony = rand() % 2;

    // First Screen
    game->start = 0;
    InitialScreen(game);
    game->start = 0;

    game->lock = 1;

    // Function's Infinite Loop
    int a = 1;
    while(a)
    {
        handleInputs(game);
        drawScreen(game);
        BallMovement(game);

        // Stops Game
        if(game->points1 >= game->pointswin)
        {
            game->results = 1;
            a--;
        }

        else if(game->points2 >= game->pointswin)
        {
            game->results = 2;
            a--;
        }

    }

    // Finishes Program
    if(game->results == 1)
    {
        historicWin(game);
        FinalScreen1(game);
    }

    else if(game->results == 2)
    {
        historicWin(game);
        FinalScreen2(game);
    }

    // Finishes Program
    endwin();

    free(game);

    return 0;
}

void initScreen()
{
#ifdef XCURSES
    Xinitscr(argc, argv);
#else
    initscr();
#endif

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    timeout(0);
    keypad(stdscr, TRUE);
}

// Inputs
void handleInputs(gameData * game)
{
    (*game).lastch = getch();

    switch((*game).lastch)
    {
        // Player 1 Paddle Down
        case 's':
        case 'S':
            game->paddle1y = game->paddle1y + 2;
            break;
        // Player 1 Paddle Up
        case 'w':
        case 'W':
            game->paddle1y = game->paddle1y - 2;
            break;
        // Player 2 Paddle Down
        case 'k':
        case 'K':
            game->paddle2y = game->paddle2y + 2;
            break;
        // Player 2 Paddle Up
        case 'i':
        case 'I':
            game->paddle2y = game->paddle2y - 2;
            break;
        // Velocity +
        case KEY_UP:
            game->velocity = game->velocity - 5000;
            break;
        // Velocity -
        case KEY_DOWN:
            game->velocity = game->velocity + 5000;
            break;
        // BACKSPACE
        case '\b':
            if(game->start > 0 && game->start < 3)
                game->start--;
            break;
        // ENTER
        case '\n':
            if(game->start == 0)
                game->start = -1;
            break;
        // Screen OPTIONS
        case 'o':
        case 'O':
            game->start = 1;
            break;
        // KEY_RIGHT
        case KEY_RIGHT:
            if(game->start > 0 && game->start < 2)
                game->start++;
            break;
        // POINTS +
        case 'p':
        case 'P':
            if(game->lock == 0)
                game->pointswin++;
            break;
        // POINTS -
        case 'l':
        case 'L':
            if(game->pointswin > 0 && game->lock == 0)
                game->pointswin--;
            break;
        case 'q':
        case 'Q':
            endwin();
            exit(EXIT_SUCCESS);
            break;
    }

    // Limit for Paddle 1
    if(game->paddle1y <= 3)
        game->paddle1y = 3;
    if(game->paddle1y > 27)
        game->paddle1y = 28;

    // Limit for Paddle 2
    if(game->paddle2y <= 3)
        game->paddle2y = 3;
    if(game->paddle2y > 27)
        game->paddle2y = 28;

}

// InitialScreen
void InitialScreen(gameData * game)
{
    clear();

    while(1)
    {
        handleInputs(game);

        start_color();
        init_pair(1, COLOR_WHITE, COLOR_CYAN);

        attron(COLOR_PAIR(1));
        mvprintw(20, 40, "By: Eduardo Brisola de Araujo ");
        attroff(COLOR_PAIR(1));


        // ASCII Art PONG
        mvprintw(10, 41, " _____   ____  _   _  _____ ");
        mvprintw(11, 41, "|  __ \\ / __ \\| \\ | |/ ____|");
        mvprintw(12, 41, "| |__) | |  | |  \\| | |  __ ");
        mvprintw(13, 41, "|  ___/| |  | | . ` | | |_ |");
        mvprintw(14, 41, "| |    | |__| | |\\  | |__| |");
        mvprintw(15, 41, "|_|     \\____/|_| \\_|\\_____|");

        mvprintw(23, 50, "Press ENTER");
        mvprintw(26, 46, "Options (Press 'O')");

        if(game->start == 1)
        {
            while(1)
            {
                handleInputs(game);

                clear();
                OptionsScreen(game);
                refresh();

                if(game->start == 0)
                {
                    clear();
                    refresh();
                    break;
                }
            }
        }

        if(game->start == -1)
            break;
    }

    refresh();

}

// Tela OPTIONS
void OptionsScreen(gameData * game)
{
    // Controles
    mvprintw(1, 10, "CONTROLS");

    mvprintw(3, 12, "- 'W' = Paddle PLAYER 1 (UP)");
    mvprintw(3, 50, "- 'S' = Paddle PLAYER 1 (Down)");
    mvprintw(5, 12, "- 'I' = Paddle PLAYER 2 (UP)");
    mvprintw(5, 50, "- 'K' = Paddle PLAYER 2 (Down)");
    mvprintw(7, 12, "- 'KEY_UP' = Increases Velocity");
    mvprintw(7, 50, "- 'KEY_DOWN' = Decreases Velocity");
    mvprintw(9, 12, "- 'Q' = Leaves Program");

    // Instruções
    mvprintw(15, 10, "INSTRUCTIONS");
    mvprintw(17, 12, "The strategy of this game is based on the objective of two players that constantly avoid the");
    mvprintw(18, 12, "overtaking of the ball at the edge of the matrix.");
    mvprintw(20, 12, "If the ball goes beyond the limit of one player's matrix, the other will receive 1 point.");
    mvprintw(21, 12, "The player who reaches 5 points first wins.");
    mvprintw(23, 12, "Game records will be kept in the 'historicWin.txt' file.");

    mvprintw(29, 12, "- Go Back (PRESS 'BACKSPACE')");
    mvprintw(29, 70, "- Continue (PRESS 'KEY_RIGHT')");


    if(game->start == 2)
    {
        while(1)
        {
            handleInputs(game);

            clear();
            OptionsScreen2(game);
            refresh();

            if(game->start == 1)
            {
                clear();
                refresh();
                break;
            }
        }
    }

}

// Tela OPTIONS 2
void OptionsScreen2(gameData * game)
{
    // Histórico Win
    mvprintw(1, 10, "HISTORIC WIN");
    mvprintw(3, 12, "This is the file where the scores and victories of the matches will be stored.");
    mvprintw(4, 12, "Here's the model:");
    mvprintw(6, 12, "Winner: Player X");
    mvprintw(7, 12, " || Score: y X y");
    mvprintw(9, 12, "By which:");
    mvprintw(10, 12, "- X: 1 ou 2");
    mvprintw(11, 12, "- y: y >= 0");


    // Parameters 
    game->dial = (100000 - game->velocity)/1000;
    if(game->dial > 95)
    {
        game->dial = 95;
        game->velocity = 5000;
    }

    if(game->dial < 5)
    {
        game->dial = 5;
        game->velocity = 95000;
    }

    if(game->pointswin < 1)
        game->pointswin = 1;

    mvprintw(14, 10, "PARAMETERS");
    mvprintw(16, 12, "- 'P'(+) or 'L'(-) = Changes Points to Win");
    mvprintw(17, 14, "Poits To Win: %i", game->pointswin);
    mvprintw(16, 62, "- 'KEY_UP' or 'KEY_DOWN' = Changes Velocity");
    mvprintw(17, 64, "Velocity: %i", game->dial);

    // Créditos
    mvprintw(20, 10, "CREDITS");
    mvprintw(22, 12, "Name: Eduardo Brisola de Araujo");
    mvprintw(25, 12, "- CS50's Final Project");
    mvprintw(26, 12, "- Project: Pong Game");

    mvprintw(29, 12, "- Go Back (PRESS 'BACKSPACE')");
}

// drawScreen
void drawScreen(gameData * game)
{
    // Clear Tela
    clear();

    // Matriz
    for(int i = 0; i < 101; i++)
        printw("-");

    for(int i = 0; i < 30; i++)
        mvprintw(i + 1, 0, "|");

    for(int i = 0; i < 30; i++)
        mvprintw(i + 1, 100, "|");

    for(int i = 0; i < 101; i++)
        mvprintw(31, i, "-");

    for(int i = 0; i < 50; i++)
        mvprintw(i, 50, ":");

    // Paddle Player 1
    for(int i = 0; i < 5; i++)
        mvprintw(game->paddle1y - 2 + i, game->paddle1x, "|");

    // Paddle Player 2
    for(int i = 0; i < 5; i++)
        mvprintw(game->paddle2y - 2 + i, game->paddle2x, "|");

    mvprintw(game->bally, game->ballx, "O");

    // Pontuação
    mvprintw(10, 108, "SCORE");
    mvprintw(12, 103, "PLAYER 1: %i", game->points1);
    mvprintw(13, 103, "PLAYER 2: %i", game->points2);

    // velocity
    game->dial = (100000 - game->velocity)/1000;

    if(game->velocity > 95000)
        game->velocity = 95000;
    if(game->velocity < 5000)
        game->velocity = 5000;

    game->pointstotal = game->points1 + game->points2;

    if(game->pointstotal == 1 && game->velocity == 50000)
        game->velocity = 45000;
    else if(game->pointstotal == 2 && game->velocity == 45000)
        game->velocity = 40000;
    else if(game->pointstotal == 3 && game->velocity == 40000)
        game->velocity = 35000;
    else if(game->pointstotal == 4 && game->velocity == 35000)
        game->velocity = 30000;

    mvprintw(15, 103, "VELOCITY: %u", (game->dial));

    // Atualiza Tela
    refresh();
}

// Movimento Bola
void BallMovement(gameData * game)
{
    static int directionx = 1;
    static int directiony = 1;

    if(game->directionx == 0)
        directionx = -1;
    else if(game->directionx == 1)
        directionx = 1;

    if(game->directiony == 0)
        directiony = -1;
    else if(game->directiony == 1)
        directiony = 1;

    game->directionx = -1;
    game->directiony = -1;

    game->bally += directiony;
    game->ballx += directionx;

    // Checks whether the ball has reached the upper or lower limit
    if(game->bally <= 1 || game->bally >= 30)
        directiony = -directiony; // Inverte a direção

    // Check if the ball has reached the lateral limits
    else if(game->ballx <= 1)
    {
        directionx = -directionx; // Inverts Direction
        game->points2++;
        game->ballx = 50;
        game->bally = 15;
    }

    else if(game->ballx >= 98)
    {
        directionx = -directionx; // Inverts Direction
        game->points1++;
        game->ballx = 50;
        game->bally = 15;
    }

    // Inversion of the Ball in the Paddle
    else if(game->ballx == game->paddle1x + 1 && (game->bally == game->paddle1y || game->bally == game->paddle1y - 1 || game->bally == game->paddle1y - 2 || game->bally == game->paddle1y + 1 || game->bally == game->paddle1y + 2))
        directionx = -directionx;
    else if(game->ballx == game->paddle2x - 1&& (game->bally == game->paddle2y || game->bally == game->paddle2y - 1 || game->bally == game->paddle2y - 2 || game->bally == game->paddle2y + 1 || game->bally == game->paddle2y + 2))
        directionx = -directionx;

    // Delay tho control the ball's velocity
    usleep(game->velocity); // 100000 microseconds = 0.1 second // Standard 50000
    // When Smaller; The Bigger the Velocity

}

// FinalScreen1
void FinalScreen1(gameData * game)
{
    clear();

    while(1)
    {
        handleInputs(game);

        if(game->start == -1)
            return;

        start_color();
        init_pair(1, COLOR_WHITE, COLOR_CYAN);

        attron(COLOR_PAIR(1));
        attroff(COLOR_PAIR(1));

        // ASCII Art PLAYER 1 WINNER
        mvprintw(13, 10, " __        _____ _   _ _   _ _____ ____         ____  _        _ __   _______ ____        _");
        mvprintw(14, 10, " \\ \\      / /_ _| \\ | | \\ | | ____|  _ \\       |  _ \\| |      / \\\\ \\ / / ____|  _ \\      / |");
        mvprintw(15, 10, "  \\ \\ /\\ / / | ||  \\| |  \\| |  _| | |_) |      | |_) | |     / _ \\\\ V /|  _| | |_) |     | |");
        mvprintw(16, 10, "   \\ V  V /  | || |\\  | |\\  | |___|  _ <       |  __/| |___ / ___ \\| | | |___|  _ <      | |");
        mvprintw(17, 10, "    \\_/\\_/  |___|_| \\_|_| \\_|_____|_| \\_\\      |_|   |_____/_/   \\_\\_| |_____|_| \\_\\     |_|");

        mvprintw(23, 49, "Press ENTER");
    }

    refresh();

}

// FinalScreen2
void FinalScreen2(gameData * game)
{
    clear();

    while(1)
    {
        handleInputs(game);

        if(game->start == -1)
            return;

        start_color();
        init_pair(1, COLOR_WHITE, COLOR_CYAN);

        attron(COLOR_PAIR(1));
        attroff(COLOR_PAIR(1));

        // ASCII Art PLAYER 2 WINNER
        mvprintw(13, 10, " __        _____ _   _ _   _ _____ ____         ____  _        _ __   _______ ____        ____");
        mvprintw(14, 10, " \\ \\      / /_ _| \\ | | \\ | | ____|  _ \\       |  _ \\| |      / \\\\ \\ / / ____|  _ \\      |___ \\");
        mvprintw(15, 10, "  \\ \\ /\\ / / | ||  \\| |  \\| |  _| | |_) |      | |_) | |     / _ \\\\ V /|  _| | |_) |       __) |");
        mvprintw(16, 10, "   \\ V  V /  | || |\\  | |\\  | |___|  _ <       |  __/| |___ / ___ \\| | | |___|  _ <       / __/ ");
        mvprintw(17, 10, "    \\_/\\_/  |___|_| \\_|_| \\_|_____|_| \\_\\      |_|   |_____/_/   \\_\\_| |_____|_| \\_\\     |_____|");

        mvprintw(23, 50, "Press ENTER");
    }

    refresh();


}

// Arquivo 
void historicWin(gameData * game)
{
    // Opens File in a+
    FILE * file =fopen("historicWin.txt", "a+");

    // Prints Results and Score
    fprintf(file, "Winner: Player %i\n || Score: %i X %i\n", game->results, game->points1, game->points2);

    // Close File
    fclose(file);
}


