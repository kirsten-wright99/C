
#include <stdio.h>

#define TRUE (1==1)
#define FALSE (1==0)

#define SIZE 9
#define SUB_SIZE 3
#define EMPTY 0

int board[SIZE][SIZE];

void readBoard();
void printBoard();
int isValid();
int backTrack(int, int);

int main()
{
    readBoard();
    
    if (backTrack(0, 0))
    {
        printBoard();
    }
    else
    {
        printf("No Solution found.\n");
    }
    
    return 0;
}

int isValid()
{
    int row, col, subRow, subCol, value, r, c;
    
    // Check each row
    for (row = 0; row < SIZE; row++)
    {
        // Set that no value exists
        int contains[SIZE];
        for (value = 0; value < SIZE; value++)
        {
            contains[value] = FALSE;
        }
        
        // Loop through the row
        for (col = 0; col < 9; col++)
        {
            // Check if a value is present
            if (board[row][col] != EMPTY)
            {
                // Check if the value is already in the row
                if (contains[board[row][col] - 1])
                {
                    return FALSE;
                }
                
                // Set the value is in the row
                contains[board[row][col] - 1] = TRUE;
            }
        }
    }
    
    // Check each column
    for (col = 0; col < SIZE; col++)
    {
        // Set that no value exists
        int contains[SIZE];
        for (value = 0; value < SIZE; value++)
        {
            contains[value] = FALSE;
        }
        
        // Loop through the column
        for (row = 0; row < 9; row++)
        {
            // Check if a value is present
            if (board[row][col] != EMPTY)
            {
                // Check if the value is already in the row
                if (contains[board[row][col] - 1])
                {
                    return FALSE;
                }
                
                // Set the value is in the row
                contains[board[row][col] - 1] = TRUE;
            }
        }
    }

    // Check each nonet
    for (subRow = 0; subRow < SIZE; subRow += SUB_SIZE)
    {
        for (subCol = 0; subCol < SIZE; subCol += SUB_SIZE)
        {
            // Set that no value exists
            int contains[SIZE];
            for (value = 0; value < SIZE; value++)
            {
                contains[value] = FALSE;
            }
        
            // In the nonet loop through all values
            for (row = 0; row < SUB_SIZE; row++)
            {
                for (col = 0; col < SUB_SIZE; col++)
                {
                    
                    r = row + subRow;
                    c = col + subCol;
                    if (board[r][c] != EMPTY)
                    {
                        // Check if the value is already in the row
                        if (contains[board[r][c] - 1])
                        {
                            return FALSE;
                        }
                        
                        // Set the value is in the row
                        contains[board[r][c] - 1] = TRUE;
                    }
                }
            }
        }
    }
    
    // No invalid row, column, or nonet was found
    return TRUE;
}

int backTrack(int r, int c)
{
    // THIS IS BACKTRACKING : Check validity
    if (!isValid())
    {
        return FALSE;
    }
    
    // Check if col index (c) is off the board
    if (c == SIZE)
    {
        return backTrack(r + 1, 0);
    }
    
    // Check if row index (r) is off the board
    if (r == SIZE)
    {
        return TRUE;
    }
    
    // Check if forced
    if (board[r][c] != 0)
    {
        return backTrack(r, c + 1);
    }
    
    // Try all possible decisions
    int attempt;
    for (attempt = 1; attempt <= 9; attempt++)
    {
        board[r][c] = attempt;
        if (backTrack(r, c + 1))
            return TRUE;
        
        // Undo the choice
        board[r][c] = EMPTY;
    }
    
    // No solution found
    return FALSE;
}

void printBoard()
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            printf("%d ", board[i][j]); 
        printf("\n");
    }
}

void readBoard()
{
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            scanf("%d", &board[i][j]);
}

