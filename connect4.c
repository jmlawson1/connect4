#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int row;
	int col;
} Player;


int rows;
int columns;


void initialize(int board[rows][columns])
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            board[i][j] = 0;
        }
    }
}


void dropMove(int player, int board[rows][columns], int row, int column)
{
    board[row][column] = player;
}

int nextOpenRow(int board[rows][columns], int column)
{	
	int row = rows - 1
	while (board[rows][column - 1] != 0)
    {
        row -= 1;
    }
	return row;
}


void printBoard(int arr[rows][columns])
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//take out after getting minimax working
int checkForWin(int player, int board[rows][columns])
{
    // horizontalCheck
    for (int j = 0; j < columns - 3; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player)
            {
                printf("Horizontal Win");
                return 1;
            }
        }
    }
    // verticalCheck
    for (int i = 0; i < rows - 3; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player)
            {
                printf("Vertical Win");
                return 1;
            }
        }
    }
    // ascendingDiagonalCheck
    for (int i = 3; i < columns; i++)
    {
        for (int j = 0; j < rows - 3; j++)
        {
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player)
                return 1;
        }
    }
    // descendingDiagonalCheck
    for (int i = 3; i < columns; i++)
    {
        for (int j = 3; j < rows; j++)
        {
            if (board[i][j] == player && board[i - 1][j - 1] == player && board[i - 2][j - 2] == player && board[i - 3][j - 3] == player)
                return 1;
        }
    }
    return 0;
}

/*
int checkForWin(int player, int board[rows][columns], int lastMoveRow, int lastMoveCol)
{
	int count = 1;
	
	printf("last move location = (%d,%d), player = %d\n",lastMoveRow,lastMoveCol,player);
	//left check
	if((lastMoveCol - 3) >= 0)
	{
		for(int i = lastMoveCol - 1; i > lastMoveCol - 4; i--)
		{
			if(board[lastMoveRow][i] == player)
			{
				count++;
			}
			else break;
		}
	}
	if(count == 4) printf("check left win\n");
	//right check
	if(lastMoveCol < (columns - 3) && count != 4)
	{
		count = 1;
		for(int i = lastMoveCol + 1; i < lastMoveCol+4; i++)
		{
			if(board[lastMoveRow][i] == player)
			{
				count++;
			}
			else break;
		}
	}
	if(count == 4) printf("check right win\n");
	//check left/right case where winning move is the 2nd or 3rd piece in a row of 4
	if((lastMoveCol - 1) > 0 && (lastMoveCol + 1) < columns)
	{		
		if(board[lastMoveRow][lastMoveCol - 1] == player && board[lastMoveRow][lastMoveCol - 2] == player && board[lastMoveRow][lastMoveCol + 1] == player)
		{
			printf("horiztonal win - XX(X)X\n");
			return 1;
		}
	}
	else if((lastMoveCol - 1) >= 0 && (lastMoveCol + 2) < columns)
	{
		if(board[lastMoveRow][lastMoveCol - 1] == player && board[lastMoveRow][lastMoveCol + 1] == player && board[lastMoveRow][lastMoveCol + 2] == player)
		{
			printf("horiztonal win - X(X)XX\n");
			return 1;
		}
	}
	//vertical check
	if(lastMoveRow < (rows - 3) && count != 4)
	{
		count = 1;
		for(int i = lastMoveRow + 1; i < lastMoveRow + 4; i++)
		{
			if(board[i][lastMoveCol] == player)
			{
				count++;
			}
			else break;
		}
	}
	printf("vertical win\n");
	if(count == 4) return 1;	
	return 0;
}
*/

// Checks if the player's move is within the range of columns
// Also checks if the column chosen to insert into isn't full
int validMoveCheck(int board[rows][columns], int column)
{	
	if(column < 1 || column > columns)
	{
		printf("Invalid move: Enter a column (1 to %d)\n",columns);
		return 0;
	}
	else if(board[0][column - 1] != 0)
	{
		printf("Column is full choose another column (1 to %d)\n",columns);
		return 0;
	}
	else return 1;
}

int scoreMove(int board[rows][columns], int player, int lastMoveRow, int lastMoveCol)
{
	int score = 0;
	int count = 1;
	int count2 = 0;
	int count3 = 0;
	int shifted = 0;
	//left check
	if((lastMoveCol - 3) >= 0)
	{
		for(int i = lastMoveCol - 1; i > lastMoveCol - 4; i--)
		{
			if(board[lastMoveRow][i] == player)
			{
				count++;
			}		
			else if((count == 2) && (shifted == 1)
			{
				if((col + 1) < columns)
				{
					if((board[lastMoveRow][i] == 0) && (board[lastMoveRow][i+3] == 0))
					{
						count3++;
					}
				}
				else if((board[lastMoveRow][i] == 0) && (board[lastMoveRow][i - 1] == 0))
				{
					count2++;
				}
			}
			else if((count == 3) && (shifted == 2)
			{
				if(board[lastMoveRow][i] == 0)
				{
					count3++;
				}
				if((col + 1) < columns)
				{
					if(board[lastMoveRow][col + 1] == 0)
					{
						count3++;
					}
				}
			}
			shifted++;
		}
	}
	//if(count == 4) printf("check left win\n");
	//right check
	if(lastMoveCol < (columns - 3) && count != 4)
	{	
		shifted = 0;
		count = 1;
		for(int i = lastMoveCol + 1; i < lastMoveCol + 4; i++)
		{
			if(board[lastMoveRow][i] == player)
			{
				count++;
			}
			else if((count == 2) && (shifted == 1))
			{
				if((board[lastMoveRow][i+1] == 0) && (board[lastMoveRow][i+2] == 0))
				{
					count2++;
				}
			}
			else if((count == 3) && (shifted == 2))
			{
				if(board[lastMoveRow][i+1] == 0)
				{
					count3++;
				}
			}
			shifted++;
		}
	}
	//if(count == 4) printf("check right win\n");
	//check left/right case where winning move is the 2nd or 3rd piece in a row of 4
	if((lastMoveCol - 1) > 0 && (lastMoveCol + 1) < columns)
	{		
		if(board[lastMoveRow][lastMoveCol - 1] == player && board[lastMoveRow][lastMoveCol - 2] == player && board[lastMoveRow][lastMoveCol + 1] == player)
		{
			printf("horiztonal win - XX(X)X\n");
			return 1;
		}
	}
	else if((lastMoveCol - 1) >= 0 && (lastMoveCol + 2) < columns)
	{
		if(board[lastMoveRow][lastMoveCol - 1] == player && board[lastMoveRow][lastMoveCol + 1] == player && board[lastMoveRow][lastMoveCol + 2] == player)
		{
			printf("horiztonal win - X(X)XX\n");
			return 1;
		}
	
	
}

int chooseBestMove(int board[rows][columns], int player)
{
	int bestScore = 0;
	int i, j, k;
	int openSpots[columns];
	int newBoard[rows][columns];
	int row, column, bestMove;
	
	for(i = 0; i < columns; i++)
	{
		if(board[0][i] == 0)
		{
			openSpots[i] = 0;
		}
		else openSpots[i] = 1;
	}
	
	for(int k = 0; k < columns; k++)
	{
		if(openSpots[k] == 0)
		{
			row = nextOpenRow(board,k+1);
			for (i = 0; i < rows; i++)
			{
				for (j = 0; j < columns; j++)
				{
					newBoard[i][j] = board[i][j];
				}
			}
			dropMove(player, newBoard, row, k);
			score = scoreMove(newBoard, player, row, k)
			if(score > bestScore)
			{
				bestScore = score;
				bestMove = k;
			}
		}
	}
	return bestMove;
}

int playerTurn(int player, int board[rows][columns])
{
    int row = rows - 1;
    int column;
	int validMove = 0;
	
	while(validMove != 1)
	{
		printf("Player %d Turn\n", player);
		printf("Which column?\n");
		scanf("%d", &column);
		validMove = validMoveCheck(board,column);
	}
    while (board[row][column - 1] != 0)
    {
        row -= 1;
    }
	
    dropMove(player, board, row, column - 1);
	
    return checkForWin(player, board, row, column - 1);
}

int computerTurn(int board[rows][columns])
{
    int row = rows - 1;
	int validMove = 0;
	int column;
	
	while(validMove != 1)
	{
		column = rand() % (7 + 1 - 1) + 1;
		validMove = validMoveCheck(board,column);
	}

    while (board[row][column - 1] != 0)
    {
        row -= 1;
    }

    dropMove(2, board, row, column - 1);

    printf("Computer Turn\n");
	
    //return checkForWin(2, board, row, column - 1);
}

int gameStart()
{
    int gameType;
    printf("1. Player vs. Computer\n");
    printf("2. Player vs. Player\n");
    scanf("%d", &gameType);

    printf("What board size would you like?\n");
    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &columns);

    return gameType;
}

/*
int terminalCheck(int board[rows][columns])
{
	if(checkForWin(1, board) == 1 || checkForWin(2,board) == 1 || 
}
*/
/*
int minimax(int board[rows][columns], int depth, int maximizingPlayer)
{
	int openSpots[columns];
	if(depth == 0 || is_terminal) 
	{
		
	}
}
*/
int main()
{
	
    int gameType;
    int currentPlayer = 1;
    int gameOver = 0;
	int moveCounter = 0;
	int maxMoves;
	int rematch = 0;
	
    gameType = gameStart();
	
	Player moves[columns];
	
	for(int i = 0; i < columns; i++)
	{
		openMoves[i].row = -1;
		openMoves[i].col = -1;
	}
	
	maxMoves = rows * columns;

    int gameBoard[rows][columns];

    initialize(gameBoard);

	while(rematch == 0)
	{
		gameOver = 0;
		while (gameOver == 0)
		{
			gameOver = playerTurn(currentPlayer, gameBoard);
			moveCounter++;
			if (gameOver == 1)
			{
				printf("\nPlayer %d Wins!!!\n", currentPlayer);
				printBoard(gameBoard);
				break;
			}
			printBoard(gameBoard);

			if (currentPlayer == 1)
			{
				currentPlayer = 2;
				if (gameType == 1)
				{
					gameOver = computerTurn(gameBoard);
					moveCounter++;
					if (gameOver == 1)
					{
						printf("\nPlayer %d Wins!!!\n", currentPlayer);
						printBoard(gameBoard);
						break;
					}
					printBoard(gameBoard);
					currentPlayer = 1;
				}
			}
			else
			{
				currentPlayer = 1;
			}
			if(moveCounter == maxMoves)
			{
				gameOver = 1;
				printf("\nGame is a draw!\n");
				printBoard(gameBoard);
			}
		}
		printf("rematch? 0 for Yes, 1 for No\n");
		scanf("%d",&rematch);
	}

    return 0;
}
