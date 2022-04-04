//MAT - I → Connect 4

#include <iostream>
#include <array>
using namespace std;

char position[6][7]; // available for whole program

void welcome()
{
    system("cls");
    cout << "------------------------------\n\n"
        << "\t  CONNECT 4\t\n\n"
        << "------------------------------\n";

    cout << "\nRULES:\n"
        << "1. Two-player (X) and (O) game.\n"
        << "2. Board size is 6 rows and 7 columns.\n"
        << "3. A player wins if he/she is able to connect 4 dots horizontally or vertically or diagonally.\n"
        << "4. Draw when the matrix is fully filled.\n";

    cout << "\nHOW TO PLAY:\n"
        << "1. Game always starts with player - X\n"
        << "2. In each step choose the column number in which you want to drop\n"
        << "3. Rows will be filled from bottom to top in any column\n\n";

    cout << "------------------------------\n"
        << "\t  GAME STARTS\t\n"
        << "------------------------------\n";
}

void printBoard()
{
    system("cls");
    cout << "  1   2   3   4   5   6   7\n";
    for (int a = 0; a <= 5; a++)
    {
        for (int b = 0; b <= 6; b++)
            cout << "| " << position[a][b] << " ";

        cout << '\n';
    }
}

int push(int b, char player)
{
    if (b >= 0 && b <= 6)
    {
        if (position[0][b] == ' ')
        {
            int i;
            for (i = 0; position[i][b] == ' '; i++)
                if (i == 5)
                {
                    position[i][b] = player;
                    return i;
                }
            i--;
            position[i][b] = player;
            return i;
        }
        else
            return -1;
    }
    else
        return -1;
}

bool check(int a, int b)
{
    int vertical = 1;   //(|)
    int horizontal = 1; //(-)
    int diagonal1 = 1;  //(\)
    int diagonal2 = 1;  //(/)
    char player = position[a][b];
    int i;  // vertical
    int ii; // horizontal

    // check for vertical(|)
    for (i = a + 1; position[i][b] == player && i <= 5; i++, vertical++)
        ; // Check down
    for (i = a - 1; position[i][b] == player && i >= 0; i--, vertical++)
        ; // Check up
    if (vertical >= 4)
        return true;

    // check for horizontal(-)
    for (ii = b - 1; position[a][ii] == player && ii >= 0; ii--, horizontal++)
        ; // Check left
    for (ii = b + 1; position[a][ii] == player && ii <= 6; ii++, horizontal++)
        ; // Check right
    if (horizontal >= 4)
        return true;

    // check for diagonal 1 (\)
    for (i = a - 1, ii = b - 1; position[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--)
        ; // up and left
    for (i = a + 1, ii = b + 1; position[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++)
        ; // down and right
    if (diagonal1 >= 4)
        return true;

    // check for diagonal 2(/)
    for (i = a - 1, ii = b + 1; position[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++)
        ; // up and right
    for (i = a + 1, ii = b - 1; position[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--)
        ; // up and left
    if (diagonal2 >= 4)
        return true;

    // if none matches
    return false;
}

int main()
{
    for (int a = 0; a <= 5; a++)
    { // fill place with whitespace
        for (int b = 0; b <= 6; b++)
            position[a][b] = ' ';
    }
    welcome();
    char playChoice;
    cout << "Enter Y/y to continue or N/n to close the game\n";
    cin >> playChoice;

    if (playChoice == 'Y' || playChoice == 'y')
    {
        int rowChoice;
        int columnChoice = 0;
        int cellsOccupied = 0;
        char player = 79;
        bool isGameOver = false;

        printBoard();
        while (!isGameOver)
        {
            if (columnChoice != -1) // check for errors in last push
            {
                if (player == 79) //'O'
                {
                    cout << "Player 1's turn : ";
                    player = 88; // player 1's character 'X'
                }
                else //'X'
                {
                    cout << "Player 2's turn : ";
                    player = 79; // player 2's character 'O'
                }
            }

            while (true)
            {
                // all cells occupied which means draw condition
                if (cellsOccupied == 42)
                    break;

                cin >> rowChoice;
                rowChoice -= 1;

                if (rowChoice <= 6 && rowChoice >= 0)
                    break;
                else
                    cout << "\nPlease enter a value between 1 and 7 : ";

                if (cin.fail())
                {
                    cin.clear();
                    char c;
                    cin >> c;
                }
            }

            if (cellsOccupied == 42)
                break;

            // push values to board
            columnChoice = push(rowChoice, player);

            if (columnChoice == -1)
                cout << "Column is full\nPlease enter another value between 1 and 7 : ";
            else
            {
                isGameOver = check(columnChoice, rowChoice);
                cellsOccupied += 1;
                printBoard();
            }
        }

        // displaying draw
        if (cellsOccupied == 42)
        {
            cout << "Game is draw!\n";
            system("pause");
            return 0;
        }

        // displaying winner
        if (player == 79)
            cout << "\nPlayer 2 won!!\n";
        else
            cout << "\nPlayer 1 won!!\n";
    }
    else
    {
        cout << "Exiting...\n";
    }
    system("pause");
    return 0;
}