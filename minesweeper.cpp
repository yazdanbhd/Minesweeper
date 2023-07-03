#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// Global variables
struct Player
{
    string name;
    int score = 0;
}player;

// function prototypes
void displayBoard(vector<vector<char>>& , int, int);
void initializeBoard(vector<vector<char>>& ,int, int);
void placeMines(vector<vector<char>>& ,int ,int , int);
void placeNumbers(vector<vector<char>> &, int, int);
void playGame(vector<vector<char>>& , vector<vector<char>>& , int, int, int);
bool comparePlayers(Player , Player );


int main()
{

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
        cout << "Enter player name: ";
        cin >> player.name;
        system ("cls");
        // display menu
        cout << "Choose a difficulty level:" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            cout << player.name << player.score;
            // declare variables
            vector<vector<char>> boardEasyMode(6, vector<char>(6));
            vector<vector<char>> hiddenBoardEasyMode(6, vector<char>(6));
            int rowsEasyMode = 6;
            int columnsEasyMode = 6;
            int minesEasyMode = 10;
            // initialize boards
            initializeBoard(boardEasyMode,rowsEasyMode, columnsEasyMode);
            initializeBoard(hiddenBoardEasyMode,rowsEasyMode, columnsEasyMode);

            // place mines
            placeMines(hiddenBoardEasyMode, rowsEasyMode,columnsEasyMode ,minesEasyMode);

            // place numbers
            placeNumbers(hiddenBoardEasyMode, rowsEasyMode, columnsEasyMode);

            // play game
            playGame(boardEasyMode, hiddenBoardEasyMode, rowsEasyMode, columnsEasyMode,choice);

        }
        if (choice == 2)
        {
            // declare variables
            vector<vector<char>> boardMediumMode(8, vector<char>(8));
            vector<vector<char>> hiddenBoardMediumMode(8, vector<char>(8));
            int rowsMediumMode = 8;
            int columnsMediumMode = 8;
            int minesMediumMode = 12;
            // initialize boards
            initializeBoard(boardMediumMode,rowsMediumMode, columnsMediumMode);
            initializeBoard(hiddenBoardMediumMode,rowsMediumMode, columnsMediumMode);

            // place mines
            placeMines(hiddenBoardMediumMode,rowsMediumMode,columnsMediumMode, minesMediumMode);

            // place numbers
            placeNumbers(hiddenBoardMediumMode, rowsMediumMode, columnsMediumMode);

            // play game
            playGame(boardMediumMode, hiddenBoardMediumMode, rowsMediumMode, columnsMediumMode,choice);
        }
        if (choice == 3)
        {
            // declare variables
            vector<vector<char>> boardHardMode(10, vector<char>(10));
            vector<vector<char>> hiddenBoardHardMode(10, vector<char>(10));
            int rowsHardMode = 10;
            int columnsHardMode = 10;
            int minesHardMode = 16;
            // initialize boards
            initializeBoard(boardHardMode,rowsHardMode, columnsHardMode);
            initializeBoard(hiddenBoardHardMode,rowsHardMode, columnsHardMode);

            // place mines
            placeMines(hiddenBoardHardMode,rowsHardMode,columnsHardMode, minesHardMode);

            // place numbers
            placeNumbers(hiddenBoardHardMode, rowsHardMode, columnsHardMode);

            // play game
            playGame(boardHardMode, hiddenBoardHardMode, rowsHardMode, columnsHardMode,choice);
        }

    }

    // exit game
    else
    {
        cout << "Thanks for playing!" << endl;
        play = false;
    }

    return 0;
}
bool comparePlayers(Player player1, Player player2)
{
    return player1.score > player2.score;
}
// function definitions
void displayBoard(vector<vector<char>>& board, int rows, int columns)
{
    system("cls");

    // read players' data from file
    vector<Player> players;
    ifstream informationFile;
    informationFile.open("information.txt");
    if (informationFile.is_open())
    {
        while (!informationFile.eof())
        {
            Player tempPlayer;
            informationFile >> tempPlayer.name >> tempPlayer.score;
            players.push_back(tempPlayer);
        }
    }

    // sort players by score
    sort(players.begin(), players.end(), comparePlayers);

    // display top 3 players
    cout << "Best players:" << endl;
    for (int i = 0; i < min((int)players.size(), 3); i++) {
        cout << i+1 << ". " << players[i].name << " : " << players[i].score << endl;
    }

    // display current player
    cout << "current player:\n " << player.name << " : " << player.score << endl;

    //display column numbers
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

void initializeBoard(vector<vector<char>>& board,int rows, int columns)
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

void placeMines(vector<vector<char>>& board,int rows,int columns, int mines)
{
    int row, column;

    // place mines
    for (int i = 0; i < mines; i++)
    {
        row = rand() % rows;
        column = rand() % columns;

        // check if mine is already placed
        while (board[row][column] == '*')
        {
            row = rand() % rows;
            column = rand() % columns;
        }

        // place mine
        board[row][column] = '*';
    }
}

void placeNumbers(vector<vector<char>>& board, int rows, int columns)
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
                if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == '*')
                {
                    count++;
                }
                if (i - 1 >= 0 && board[i - 1][j] == '*')
                {
                    count++;
                }
                if (i - 1 >= 0 && j + 1 < columns && board[i - 1][j + 1] == '*')
                {
                    count++;
                }
                if (j - 1 >= 0 && board[i][j - 1] == '*')
                {
                    count++;
                }
                if (j + 1 < columns && board[i][j + 1] == '*')
                {
                    count++;
                }
                if (i + 1 < rows && j - 1 >= 0 && board[i + 1][j - 1] == '*')
                {
                    count++;
                }
                if (i + 1 < rows && board[i + 1][j] == '*')
                {
                    count++;
                }
                if (i + 1 < rows && j + 1 < columns && board[i + 1][j + 1] == '*')
                {
                    count++;
                }
                board[i][j] = count + '0';
                count = 0;
            }
        }
    }
}

void playGame(vector<vector<char>>& board, vector<vector<char>>& hiddenBoard, int rows, int columns,int difficultyChoice)
{
    // declare variables
    int row;
    int column;
    int count = 0;
    bool play = true;

    // play game
    while(play)
    {
        char choice;
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
            system("cls");
            displayBoard(hiddenBoard, rows, columns);
            fstream informationFile("information.txt");
            if (informationFile.is_open())
            {
                // write name and score to file
                informationFile << player.name << " " << player.score << endl;
                informationFile.close();
            }
            cout << "---------- You hit a mine! Game over! ----------\n\n" <<"Your Score: "<< player.score <<endl;
            play = false;

        }

            // check if number exists
        else if (hiddenBoard[row][column] != '#')
        {
            board[row][column] = hiddenBoard[row][column];
            count++;
            if (difficultyChoice == 1)
                player.score += 10;
            else if (difficultyChoice == 2)
                player.score += 20;
            else if (difficultyChoice == 3)
                player.score += 40;
        }

        // check if blank space exists
        else
        {
            board[row][column] = hiddenBoard[row][column];
            count++;
            if (difficultyChoice == 1)
                player.score += 10;
            else if (difficultyChoice == 2)
                player.score += 20;
            else if (difficultyChoice == 3)
                player.score += 40;
        }

        // check win condition
        if (count == 90)
        {
            cout << "---------- You win! ----------\n\n" <<"Your Score: "<< player.score <<endl;
            ofstream informationFile("information.txt");
            if (informationFile.is_open())
            {
                // write name and score to file
                informationFile << player.name << " " << player.score << endl;
                informationFile.close();
            }
            play = false;
        }
    }
}