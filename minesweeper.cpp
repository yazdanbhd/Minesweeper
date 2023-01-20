#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>

using namespace std;

// function prototypes
void displayBoard(char[][10], int, int);
void initializeBoard(char[][10], int, int);
void placeMines(char[][10], int, int);
void placeNumbers(char[][10], int, int);
void playGame(char[][10], char[][10], int, int);


int main()
{
    // declare variables
    char board[10][10];
    char hiddenBoard[10][10];
    int rows = 10;
    int columns = 10;
    int mines = 10;
    bool play = true;
    int choice;

    // seed random number generator
    srand(time(0));

    // display menu
    cout << "Welcome to Minesweeper!\n" << endl;
    cout << "1. Play Game" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    // validate input
    while (choice < 1 || choice > 2)
    {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin >> choice;
    }

    // play game
    if (choice == 1)
    {
        // initialize boards
        initializeBoard(board, rows, columns);
        initializeBoard(hiddenBoard, rows, columns);

        // place mines
        placeMines(hiddenBoard, rows, columns);

        // place numbers
        placeNumbers(hiddenBoard, rows, columns);

        // play game
        playGame(board, hiddenBoard, rows, columns);
    }

    // exit game
    else
    {
        cout << "Thanks for playing!" << endl;
        play = false;
    }

    return 0;
}


