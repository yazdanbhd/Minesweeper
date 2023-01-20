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

// function definitions
void displayBoard(char board[][10], int rows, int columns)
{
    system("cls");

    //display column numbers
    cout << "  ";
    for (int i = 0; i < columns; i++)
    {
        cout << i << " ";
    }
    cout << endl;

    //display board
    for (int i = 0; i < rows; i++)
    {
        cout << i << " ";
        for (int j = 0; j < columns; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void initializeBoard(char board[][10], int rows, int columns)
{
    // initialize board
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            board[i][j] = '#';
        }
    }
}

void placeMines(char board[][10], int rows, int columns)
{
    // declare variables
    int row;
    int column;

    // place mines
    for (int i = 0; i < 10; i++)
    {
        row = rand() % 10;
        column = rand() % 10;
        board[row][column] = '*';
    }
}

void placeNumbers(char board[][10], int rows, int columns)
{
    // declare variables
    int count = 0;

    // place numbers
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board[i][j] != '*')
            {
                if (i > 0 && j > 0 && board[i - 1][j - 1] == '*')
                {
                    count++;
                }
                if (i > 0 && board[i - 1][j] == '*')
                {
                    count++;
                }
                if (i > 0 && j < 9 && board[i - 1][j + 1] == '*')
                {
                    count++;
                }
                if (j > 0 && board[i][j - 1] == '*')
                {
                    count++;
                }
                if (j < 9 && board[i][j + 1] == '*')
                {
                    count++;
                }
                if (i < 9 && j > 0 && board[i + 1][j - 1] == '*')
                {
                    count++;
                }
                if (i < 9 && board[i + 1][j] == '*')
                {
                    count++;
                }
                if (i < 9 && j < 9 && board[i + 1][j + 1] == '*')
                {
                    count++;
                }
                board[i][j] = count + '0';
                count = 0;
            }
        }
    }
}

void playGame(char board[][10], char hiddenBoard[][10], int rows, int columns)
{
    // declare variables
    int row;
    int column;
    int count = 0;
    bool play = true;

    // play game
    while(play)
    {
        system("cls");

        // display board
        displayBoard(board, rows, columns);

        // get row and column
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> column;

        // validate input
        while (row < 0 || row > 9 || column < 0 || column > 9)
        {
            cout << "Invalid input. Please enter a row and column between 0 and 9.\nrow: ";
            cin >> row;
            cout << "column: ";
            cin >> column;
        }

        // check if mine exists
        if (hiddenBoard[row][column] == '*')
        {
            cout << "---------- You hit a mine! Game over! ----------" << endl;
            getch();
            play = false;
        }

            // check if number exists
        else if (hiddenBoard[row][column] != '#')
        {
            board[row][column] = hiddenBoard[row][column];
            count++;
        }

        // check if blank space exists
        else
        {
            board[row][column] = hiddenBoard[row][column];
            count++;
        }

        // check win condition
        if (count == 90)
        {
            cout << "---------- You win! ----------" << endl;
            getch();
            play = false;
        }
    }
}