
#include <stdio.h>
#include <string.h>

void board(int grid[3][3]);
int winner(int grid[3][3]);
void Ai(int grid[3][3],int AiGrid[3][3]);
int minimax(int grid[3][3], int depth, int isMax);

int main(){

    int row;
    int col;
    int result = 0;

    int grid[3][3]= {{2,3,4}, {2,3,4}, {2,3,4}};
    int AiGrid[3][3] = {{2,3,4}, {2,3,4}, {2,3,4}};

    printf("___|___|___\n");
    printf("___|___|___\n");
    printf("   |   |   \n");

    printf("X starts first\n\n");

    while(1){

        // -------- PLAYER MOVE (X) --------
        printf("pick a row and column: ");
        scanf("%d %d",&row, &col);

        row -= 1;
        col -= 1;

        while(row < 0 || row > 2 || col < 0 || col > 2 ||
              grid[row][col] == 0 || grid[row][col] == 1){
            printf("Invalid or taken spot. Pick again: ");
            scanf("%d %d",&row, &col);
            row -= 1;
            col -= 1;
        }

        grid[row][col] = 0;

        board(grid);

        result = winner(grid);
        if(result != 0){
            break;
        }

        // -------- AI MOVE (O) --------
        Ai(grid, AiGrid);

        printf("AI move:\n");
        board(grid);

        result = winner(grid);
        if(result != 0){
            break;
        }
    }

    if(result == 1){
        printf("X won\n");
    }
    else if(result == 2){
        printf("O won\n");
    }
    else{
        printf("its a draw!!\n");
    }

    return 0;
}


void board(int grid[3][3]){
  char cOne[] = "___|";
  char cTwo[] = "___|";
  char cThree[] = "___";

  for(int r=0;r<3;r++){
    for(int c=0;c<3;c++){
      if(grid[r][c]== 0 || grid[r][c]== 1){
        if(grid[r][c]== 0){
          if(c==0 || c==1){
            printf("_X_|"); 
          }
          else if(c==2){
            printf("_X_"); 
          }
        }
        else if(grid[r][c]== 1){
           if(c==0 || c==1){
            printf("_O_|"); 
          }
          else if(c==2){
            printf("_O_"); 
          }
        }
        
      }
      else {
        if(grid[r][c]==2){
          printf("%s",cOne);
        }
        if(grid[r][c]==3){
          printf("%s",cTwo);
        }
        if(grid[r][c]==4){
          printf("%s",cThree);
        }
      }
      
    }
    printf("\n");
  }
  printf("\n");
}

int winner(int grid[3][3]){
  for (int i = 0; i < 3; i++) {
      if (grid[i][0] == 0 && grid[i][1] == 0 && grid[i][2] == 0) {
          //printf("X won\n");
          return 1;
          
      }
      if (grid[0][i] == 0 && grid[1][i] == 0 && grid[2][i] == 0) {
         // printf("X won\n");
          return 1;
          
          
      }
    } 
    if (grid[0][0] == 0 && grid[1][1] == 0 && grid[2][2] == 0) {
         // printf("X won\n");
          return 1;
      }
    if (grid[0][2] == 0 && grid[1][1] == 0 && grid[2][0] == 0) {
          //printf("X won\n");
          return 1;
      }
 
 for (int i = 0; i < 3; i++) {
      if (grid[i][0] == 1 && grid[i][1] == 1 && grid[i][2] == 1) {
          //printf("O won\n");
          
          return 2;
      }
      if (grid[0][i] == 1 && grid[1][i] == 1 && grid[2][i] == 1) {
          //printf("O won\n");
        
          return 2;
      }
    } 
    if (grid[0][0] == 1 && grid[1][1] == 1 && grid[2][2] == 1) {
         // printf("O won\n");
          return 2;
      }
    if (grid[0][2] == 1 && grid[1][1] == 1 && grid[2][0] == 1) {
         // printf("O won\n");
          return 2;
      }
    int draw = 1;

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (grid[i][j] != 0 && grid[i][j] != 1) {
            draw = 0;
            break;
        }
    }
    if (!draw){
        break;
    }
}

if (draw) {
    //printf("its a draw!!\n");
    return 3;
    
}
    return 0;
}

void Ai(int grid[3][3], int AiGrid[3][3]){
  int bestScore = -1000;
  int moveRow = -1;
  int moveCol = -1;

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(grid[i][j] != 0 && grid[i][j] != 1){

        int temp = grid[i][j];
        grid[i][j] = 1;  // AI is O

        int score = minimax(grid, 0, 0);

        grid[i][j] = temp;

        if(score > bestScore){
          bestScore = score;
          moveRow = i;
          moveCol = j;
        }
      }
    }
  }

  if(moveRow != -1 && moveCol != -1){
    grid[moveRow][moveCol] = 1;
  }
}

int minimax(int grid[3][3], int depth, int isMax){

  int result = winner(grid);

  if(result == 2){     // AI wins
    return 10 - depth;
  }
  if(result == 1){     // Player wins
    return depth - 10;
  }
  if(result == 3){     // Draw
    return 0;
  }

  if(isMax){  // AI turn
    int best = -1000;

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(grid[i][j] != 0 && grid[i][j] != 1){

          int temp = grid[i][j];
          grid[i][j] = 1;

          int score = minimax(grid, depth + 1, 0);

          grid[i][j] = temp;

          if(score > best){
            best = score;
          }
        }
      }
    }
    return best;
  }
  else{  // Player turn
    int best = 1000;

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        if(grid[i][j] != 0 && grid[i][j] != 1){

          int temp = grid[i][j];
          grid[i][j] = 0;

          int score = minimax(grid, depth + 1, 1);

          grid[i][j] = temp;

          if(score < best){
            best = score;
          }
        }
      }
    }
    return best;
  }
}


