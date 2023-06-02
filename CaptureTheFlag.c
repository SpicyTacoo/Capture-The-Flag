#include <stdio.h>
#include <stdlib.h>

void headerleft();
void headerright();
void RightLine();
void CenterLine();
void initializeBoard(int board[][5], int blackTiles[][5]);
void displayBoard(int board[][5], int alpha[][5], int beta[][5]);
void updateBoard(int board[][5], int alpha[][5], int beta[][5]);
void initializeAlphaBeta(int board[][5], int alpha[][5], int beta[][5]);
void nextPlayerMove(int ok, int aTurn, int alpha[][5], int beta[][5],int a, int b, int c, int d, int blackTiles[][5]);
int ifMoveIsInFree (int alpha[][5], int beta[][5], int nextRow, int nextColumn);
int ifNextMoveInBetaAlpha (int alpha[][5], int beta[][5], int nextRow, int nextColumn);
int ifNextMoveInBlackTile (int nextRow, int nextColumn, int blackTiles[][5]);
int gameOver(int over, int alpha[][5], int beta[][5]);
void Alpha();
void Beta();
void reset();

int main(){
    system("cls");
    int prevRow, prevColumn;
    int nextRow, nextColumn;

    int okPiece;
    int board[7][5];
    int alpha[2][5]; // integer pairs (row, col) // alpha = set E
    int beta[2][5]; // integer pairs (row, col) // beta = set Y
    int blackTiles[7][5];
    int free[7][5]; // integer pairs (row, col)

    int aTurn = 1, over = 0, ok = 0;

    int tempX;
    int tempY;

    headerleft();
    printf(" Game Start ");
    headerright();
    printf("\n\n\n");
    initializeBoard(board, blackTiles);
    initializeAlphaBeta(board, alpha, beta);
    displayBoard(board, alpha, beta);

    // for (int i = 0; i < 7; i++)
    // {
    //     for (int j = 0; j < 5; j++)
    //     {
    //         printf("%d ", blackTiles[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n\nblack tiles\n");
    
    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d %d\n", alpha[0][i], alpha[1][i]);
    //     printf("%d %d\n", beta[0][i], beta[1][i]);
    // }
    


    do{
        if (aTurn == 1)
            printf("Player (A)lpha's Turn!\n\n");

        if (aTurn == 0)
            printf("Player (B)eta's Turn!\n\n");

        do{
            okPiece = 0;
            tempX = -100;
            tempY = -100;

            printf("Which piece would you like to move? (row, column): ");
            scanf("%d %d", &prevRow, &prevColumn);
            prevRow--;
            prevColumn--;

            if (aTurn == 1){
                for(int i = 0; i < 5; i++){
                    if ((alpha[0][i] == prevRow) && alpha[1][i] == (prevColumn)){
                        tempX = alpha[0][i];
                        tempY = alpha[1][i];
                    }
                }
            }

            if (aTurn == 0){
                for(int i = 0; i < 5; i++){
                    if(beta[0][i] == prevRow && beta[1][i] == prevColumn){
                        tempX = beta[0][i];
                        tempY = beta[1][i];
                    }
                }
            }

            // printf("\n\n%d %d\n\n", prevRow, prevColumn); //checking
            // printf("\n\n%d %d\n\n", tempX, tempY); //checking
            // printf("\n\n%d %d\n\n", alpha[0][2], alpha[1][2]); //checking

            if (tempX != prevRow && tempY != prevColumn)
                printf("Invalid checker piece! Please choose a valid checker piece!\n\n");
            else 
                okPiece = 1;

        } while (okPiece == 0);
        
        do{
            printf("\n\nWhere would like to move your chosen checker piece? (row, column): ");
            scanf("%d %d", &nextRow, &nextColumn);
            nextRow--;
            nextColumn--;

            // printf("\n\n%d %d\n\n", nextRow, nextColumn); //checking

            if ((nextRow < 0 || nextRow > 6) || (nextColumn < 0 || nextColumn > 4))
                printf("Invalid coordinates! Please enter coordinates within the board! \n\n");
        } while ((nextRow < 0 || nextRow > 6) || (nextColumn < 0 || nextColumn > 4));

        nextPlayerMove(ok, aTurn, alpha, beta, prevRow, prevColumn, nextRow, nextColumn, blackTiles);
        over = gameOver(over, alpha, beta);

        if (over == 1)
            printf("Alpha Wins!");
        else if (over == 2)
            printf("Beta Wins!");

        system("cls");
        updateBoard (board, alpha, beta);
        displayBoard(board, alpha, beta);
        aTurn = !aTurn;

        // int i, j;
        // printf("row\n");
        // for (i = 0; i < 7; i++){
        //     printf(" %d ", i + 1);
        //     for (j = 0; j < 5; j++)
        //     printf("\t\t%d ", board[i][j]);
            
        //     printf("\n");
        // }
        // printf("\n\n");

    } while (over == 0);
    
    return 0;
}

// Header
void headerleft()
{
    printf("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
}
void headerright()
{
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9");
}

void RightLine()
{
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
}
void CenterLine()
{
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
}
void HeaderLine()
{
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
}

// Color for Red, Green and Reset
void Alpha() {
    printf("\033[1;31m");
    printf("\tA");  
    printf("\033[0m");
}

void Beta() {
    printf("\033[0;34m");
    printf("\tB");    
    printf("\033[0m");
}

void reset() {
    printf("\033[0m");
}

void initializeBoard(int board[][5], int blackTiles[][5])
{
    int i, j;

    for (i = 0; i < 7; i++){
        for (j = 0; j < 5; j++){
            board[i][j] = 0;
        }
    }

    for (i = 0; i < 7; i++){
        for (j = 0; j < 5; j++)
        {
            if (i < 2 || i > 4)
            {
                if (i % 2 == 0 && j % 2 == 0)
                    board[i][j] = 1;

                if (i % 2 == 1 && j % 2 == 1)
                    board[i][j] = 1;
            }
            
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
                blackTiles[i][j] = 1;
            else
                blackTiles[i][j] = 0;
        }
    }
}

void displayBoard(int board[][5], int alpha[][5], int beta[][5])
{
    int i, j, xr = 1, xb = 1, yr = 1, z;

    for (i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("\t");
        }
        else if (i == 6)
        {
            printf("\t");
        }
        else
        {
            printf("%d", i);
            printf("\t");
        }
    }
    printf("\n");

    for (i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("\xC9");
            RightLine();
        }
        else if (i == 6)
        {
            printf("\xBB");
        }
        else
        {
            printf("\xCD");
            CenterLine();
        }
    }
    printf("\n");

    for (i = 0; i < 7*2; i++)
    {
        if (i >= 0 && i < 7*2 - 1)
        {
            xb = 0;

            if (i % 2 == 0) // if i is even
            {
                printf("%d", xr);
                xr++;
                
                for (j = 0; j < 5; j++)
                {
                    xb = i / 2;

                    if (board[xb][j] == 1){
                        for (z = 0; z < 5; z++){
                            if (alpha[0][z] == xb && alpha[1][z] == j)
                                Alpha();
                            
                            if (beta[0][z] == xb && beta[1][z] == j)
                                Beta();
                        }
                    }

                    else
                        printf("\t ");
                    

                }
                printf("\t\xBA\n");
            }
            else // if i is odd
            {
                for (j = 0; j <= 5; j++)
                {
                    if (j == 0)
                    {
                        printf("\xCC");
                    }
                    else 
                    {
                        printf("\xBA");

                    }
                    RightLine();
                    
                }
                printf("\xBA\n");
            }
        }
    }

    for (i = 0; i < 7; i++)
    {
        if (i == 0)
        {
            printf("\xC8");
            RightLine();
        }
        else if (i == 6)
        {
            printf("\xBC");
        }
        else
        {
            printf("\xCD");
            CenterLine();
        }
    }

    printf("\n");
}

void initializeAlphaBeta(int board[][5], int alpha[][5], int beta[][5])
{
    int i, j, counterA = 0, counterB = 0;

    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (board[i][j] == 1)
            {
                if (i >= 5){
                    alpha[0][counterA] = i;
                    alpha[1][counterA] = j;
                    counterA++;
                }

                if (i < 2){
                    beta[0][counterB] = i;
                    beta[1][counterB] = j;
                    counterB++;
                }
            }
        }
    }
}

void updateBoard(int board[][5], int alpha[][5], int beta[][5])
{
    int i, j, k;

    for (i = 0; i < 7; i++){
        for (j = 0; j < 5; j++){
            board[i][j] = 0;
        }
    }

    for (k = 0; k < 5; k++)
    {
        if (alpha[0][k] != -1 && alpha[1][k] != -1){
            board[alpha[0][k]][alpha[1][k]] = 1;
            board[beta[0][k]][beta[1][k]] = 1;
        }
    }
}

void nextPlayerMove(int ok, int aTurn, int alpha[][5], int beta[][5], int a, int b, int c, int d, int blackTiles[][5])
{
    int i, j, k, condition5And7 = 0;

    //conditions 1 & 3 & 5 & 6
    //condition 1
    if (aTurn == 1){

        do{
            if (a == (c + 1) && ((d == b) || (d == b + 1) || (b == d + 1))){
                // printf("\n\n\n%d %d %d %d\n", a, b, c, d);
                ok = !ok; //ok = true
                }
            
            else{
                printf("\nInvalid move! Please move one step forward, one step left diagonal or one step right diagonal!\n\n");
                printf("Where would like to move your chosen checker piece? (row, column): ");
                scanf("%d %d", &c, &d);
                c--;
                d--;
                // printf("%d %d", c, d);
            }
        } while (ok != 1);

        do {
            //condition 3
            if (ok && ifMoveIsInFree(alpha, beta, c, d)){
                
                for (i = 0; i < 5; i++)
                {
                    if (alpha[0][i] == a && alpha[1][i] == b){
                        alpha[0][i] = c;
                        alpha[1][i] = d;
                    }
                }
                aTurn = !aTurn;
                ok = !ok; // ok = false
            
            }

            //condition 5
            if (ok && aTurn && ifNextMoveInBetaAlpha(alpha, beta, c, d) == 2 && ifNextMoveInBlackTile(c, d, blackTiles) == 0) {
                ok = !ok; // ok = false
                condition5And7 = 1;

                printf("Enemy piece cannot be captured because it is not in white tile!\n\n");
                printf("Where would like to move your chosen checker piece? (row, column): ");
                scanf("%d %d", &c, &d);
                c--;
                d--;
                // printf("%d %d", c, d);
            }

            //condition 6
            if (ok && aTurn && ifNextMoveInBetaAlpha(alpha, beta, c, d) == 2 && ifNextMoveInBlackTile(c, d, blackTiles) == 1) {
                aTurn = !aTurn;
                ok = !ok; // ok = false

                for (j = 0; j < 5; j++){
                    if (beta[0][j] == c && beta[1][j] == d){
                        beta[0][j] = -1;
                        beta[1][j] = -1;
                    
                        for (k = 0; k < 5; k++){
                            if (alpha[0][k] == a && alpha[1][k] == b){
                                alpha[0][k] = c;
                                alpha[1][k] = d;
                            }
                        }
                    }
                }
            }
        } while (condition5And7 == 1);
    }

    //conditions 2 & 4 & 7 & 8
    //condition 2
    else if (!aTurn == 1){

        do{
            if (c == (a + 1) && ((d == b) || (d == b + 1) || (b == d + 1))){

                ok = !ok; //ok = true
                }
            
            else{
                printf("\nInvalid move! Please move one step forward, one step left diagonal or one step right diagonal!\n\n");
                printf("Where would like to move your chosen checker piece? (row, column): ");
                scanf("%d %d", &c, &d);
                c--;
                d--;
                // printf("%d %d", c, d); //testing
            }
        } while (ok != 1);

        do{
            //condition 4
            if (ok && ifMoveIsInFree(alpha, beta, c, d)){
                for (i = 0; i < 5; i++)
                {
                    if (beta[0][i] == a && beta[1][i] == b){
                        beta[0][i] = c;
                        beta[1][i] = d;
                    }
                }
                aTurn = !aTurn;
                ok = !ok;
                
            }

            //condition 7
            if (ok && !aTurn == 1 && ifNextMoveInBetaAlpha(alpha, beta, c, d) == 1 && ifNextMoveInBlackTile(c, d, blackTiles) == 0) {
            ok = !ok;
            condition5And7 = 1;

            printf("Enemy piece cannot be captured because it is not in white tile!\n\n");
            printf("Where would like to move your chosen checker piece? (row, column): ");
            scanf("%d %d", &c, &d);
            c--;
            d--;
            // printf("%d %d", c, d); //testing
            }

            //condition 8
            if (ok && !aTurn == 1 && ifNextMoveInBetaAlpha(alpha, beta, c, d) == 1 && ifNextMoveInBlackTile(c, d, blackTiles) == 1) {
                aTurn = !aTurn;
                ok = !ok;

                for (j = 0; j < 5; j++){
                    if (alpha[0][j] == c && alpha[1][j] == d){
                        alpha[0][j] = -1;
                        alpha[1][j] = -1;

                        for (k = 0; k < 5; k++){
                            if (beta[0][k] == a && beta[1][k] == b){
                                beta[0][k] = c;
                                beta[1][k] = d;
                            }
                        }
                    }
                }
            }
        } while(condition5And7 == 1);
    }
}

int ifMoveIsInFree (int alpha[][5], int beta[][5], int nextRow, int nextColumn)
{
    int i;

    for (i = 0; i < 5; i++){
        if ((alpha[0][i] == nextRow && alpha[1][i] == nextColumn) || (beta[0][i] == nextRow && beta[1][i] == nextColumn))
            return 0;
    }
    return 1;
}

int ifNextMoveInBetaAlpha (int alpha[][5], int beta[][5], int nextRow, int nextColumn)
{
    int i;

    for (i = 0; i < 5; i++){
        if (nextRow == alpha[0][i] && nextColumn == alpha[1][i])
            return 1;
        if (nextRow == beta[0][i] && nextColumn == beta[1][i])
            return 2;
    }
    return 0;
}

int ifNextMoveInBlackTile (int nextRow, int nextColumn, int blackTiles[][5])
{
    int i, j;

    for (i = 0; i < 7; i++){
        for (j = 0; j < 5; j++){
            if (blackTiles[i][j] == 1)
            {
                if (nextRow == i && nextColumn == j)
                    return 1;
            }
        }
    }
    return 0;
}

int gameOver(int over, int alpha[][5], int beta[][5])
{
    int i, j, k, counterA = 0, counterB = 0;
    int winCounterA = 0, winCounterB = 0;

    for (i = 0; i < 5; i++){
        if (alpha[0][i] == -1 || alpha[1][i] == -1){
            counterA++;
        }

        if (beta[0][i] == -1 || beta[1][i] == -1){
            counterB++;
        }
    }



    for (i = 0; i < 7; i++){
        for (j = 0; j < 5; j++){
            if (i < 2)
            {
                if (i % 2 == 0 && j % 2 == 0)
                {
                    for (k = 0; k < 5; k++)
                    {
                        if (alpha[0][k] == i && alpha[1][k] == j)
                            winCounterA++;
                        else if (alpha[0][k] == -1 && alpha[1][k] == -1)
                            winCounterA++;
                    }
                }
            }
        }
    }

    for (i = 0; i < 7; i++){
        for (j = 0; j < 5; j++){
            if (i < 2)
            {
                if (i % 2 == 0 && j % 2 == 0)
                {
                    for (k = 0; k < 5; k++)
                    {
                        if (beta[0][k] == i && beta[1][k] == j)
                            winCounterB++;
                        else if (beta[0][k] == -1 && beta[1][k] == -1)
                            winCounterB++;
                    }
                }
            }
        }
    }
    
    if (counterB == 5 )
        over = 1; // Alpha wins.

    if (counterA == 5 )
        over = 2; //Beta wins

    // if (counterB == 5 && winCounterA != 5)
        

    return over;
}
