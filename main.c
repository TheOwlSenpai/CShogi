#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <Windows.h>

/*
void setcolor (unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,color);
}
*/
// All te type of pieces
enum Pieces {
      n = 0,
      pawn, // done
      lance, // done
      knight, // done
      silver,  // done
      gold, // done
      rook, // done
      bishop, // done
      king, // done
      dragon,
      horse,
};

// The Two main color
enum Color {
      sente = 1,
      gote,
};

int moveCd[4], ch, tmp; // ch(current hand)

//bool ck_mate_sente, ck_mate_gote; // check mate //Work in progress...

bool ck_mate;

// Colors
void sente_c(void){ // change color to purple
      printf("\033[0;35m");
      //setcolor(5);
}

void gote_c(void){ // change color to green
      printf("\033[0;32m");
      //setcolor(10);
}

void reset_c(void){ // reset color
      printf("\033[0m");
      //setcolor(15);
}


// Pieces on the poard represented with a 2d array
int board[9][9] = {
      {2,3,4,5,8,5,4,3,2},
      {0,6,0,0,0,0,0,7,0},
      {1,1,1,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1},
      {0,7,0,0,0,0,0,6,0},
      {2,3,4,5,8,5,4,3,2},
};

// Color of the pieces on the poard represented with a 2d array
int color[9][9] = {
      {2,2,2,2,2,2,2,2,2},
      {0,2,0,0,0,0,0,2,0},
      {2,2,2,2,2,2,2,2,2},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {1,1,1,1,1,1,1,1,1},
      {0,1,0,0,0,0,0,1,0},
      {1,1,1,1,1,1,1,1,1},
};

/*
int board[9][9] = {
      {0,0,0,0,king,0,0,0,0},
      {0,0,rook,0,0,0,bishop,0,0},
      {0,lance,0,0,0,0,0,pawn,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,pawn,0,0,0,0,0,lance,0},
      {0,0,bishop,0,0,0,rook,0,0},
      {0,0,0,0,king,0,0,0,0},
};

int color[9][9] = {
      {0,0,0,0,2,0,0,0,0},
      {0,0,2,0,0,0,2,0,0},
      {0,1,0,0,0,0,0,1,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0},
      {0,2,0,0,0,0,0,2,0},
      {0,0,1,0,0,0,1,0,0},
      {0,0,0,0,1,0,0,0,0},
};

int promote[9][9] = {
    {},{},{},{},{},{},{},{},{}
};
*/

// Players tegoma
int sente_hand[7] = {};
int gote_hand[7] = {};

// Position of the two kings
int sente_king[2] = {9, 5};
int gote_king[2] = {1, 5};


// Find where the two kings are
void checkKings(void){
    int i, i2;
    
    for(i=0; i<9; i++){
        for(i2=0; i2<9; i2++){
            if(board[i][i2] == king && color[i][i2] == sente){
                sente_king[0] = i;
                sente_king[1] = i2;
            }
            if(board[i][i2] == king && color[i][i2] == gote){
                gote_king[0] = i;
                gote_king[1] = i2;
            }
        }
    }
}

// Transform char to int-1
int traslate(char ch){
      int c;

      switch (ch)
      {
            case '0':
                  c = 9;
                  break;
            case '1':
                  c = 1-1;
                  break;
            case '2':
                  c = 2-1;
                  break;
            case '3':
                  c = 3-1;
                  break;
            case '4':
                  c = 4-1;
                  break;
            case '5':
                  c = 5-1;
                  break;
            case '6':
                  c = 6-1;
                  break;
            case '7':
                  c = 7-1;
                  break;
            case '8':
                  c = 8-1;
                  break;
            case '9':
                  c = 9-1;
                  break;
          default:
              c = 9;
              break;
      }

      return c;
}

// Stamp the board V_2.2 in Japanese
void stampBoardJp(void){
      int i, i2;

      //printf("\033[2J\033[H"); // Refresh the Screen, DELETE IF YOU ARE ON WINDOWS!!!
      system("cls");

      printf(": ");
      for(i=0; i<4; i++){
            printf("%d", moveCd[i]+1);
      }

      if(ch == sente){
            for(i=0; i<9; i++){
                  if(i==0){
                        printf("\n\n");
                        for(i2=0; i2<9; i2++){
                              printf("  %d. ", i2+1);
                        }
                        printf("\n+----+----+----+----+----+----+----+----+----+\n");
                  }


                  for(i2=0; i2<9; i2++){
                        printf("|");
                        switch (board[i][i2])
                        {
                              case n:
                                    printf("    ");
                                    break;
                              case pawn:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ P\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ P/");
                                    }
                                    reset_c();
                                    break;
                              case lance:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ L\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ L/");
                                    }
                                    reset_c();
                                    break;
                              case knight:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ N\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ N/");
                                    }
                                    reset_c();
                                    break;
                              case silver:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ S\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ S/");
                                    }
                                    reset_c();
                                    break;
                              case gold:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ G\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ G/");
                                    }
                                    reset_c();
                                    break;
                              case rook:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ R\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ R/");
                                    }
                                    reset_c();
                                    break;
                              case bishop:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ B\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ B/");
                                    }
                                    reset_c();
                                    break;
                              case king:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ K\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ K/");
                                    }
                                    reset_c();
                                    break;
                              default:
                                    break;
                        }
                        if(i2==8){
                              printf("| %d.", i+1);
                        }
                  }

                  printf("\n+----+----+----+----+----+----+----+----+----+\n");

            }
      }
      if(ch == gote){
            for(i=8; i>=0; i--){
                  if(i==8){
                        printf("\n\n");
                        for(i2=0; i2<9; i2++){
                              printf("  %d. ", i2+1);
                        }
                        printf("\n+----+----+----+----+----+----+----+----+----+\n");
                  }


                  for(i2=0; i2<9; i2++){
                        printf("|");
                        switch (board[i][i2])
                        {
                        case n:
                              printf("    ");
                              break;
                        case pawn:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ P/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ P\\");
                              }
                              reset_c();
                              break;
                        case lance:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ L/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ L\\");
                              }
                              reset_c();
                              break;
                        case knight:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ N/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ N\\");
                              }
                              reset_c();
                              break;
                        case silver:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ S/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ S\\");
                              }
                              reset_c();
                              break;
                        case gold:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ G/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ G\\");
                              }
                              reset_c();
                              break;
                        case rook:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ R/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ R\\");
                              }
                              reset_c();
                              break;
                        case bishop:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ B/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ B\\");
                              }
                              reset_c();
                              break;
                        case king:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ K/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ K\\");
                              }
                              reset_c();
                              break;
                        default:
                              break;
                        }
                        if(i2==8){
                              printf("| %d.", i+1);
                        }
                  }

                  printf("\n+----+----+----+----+----+----+----+----+----+\n");
            }
      }
      printf("\nSENTE'S TEGOMA: ");
      sente_c();
      printf("%dP, %dL, %dN, %dS, %dG, %dR, %dB\n", sente_hand[pawn-1], sente_hand[lance-1], sente_hand[knight-1], sente_hand[silver-1], sente_hand[gold-1], sente_hand[rook-1], sente_hand[bishop-1]);
      reset_c();
      printf("\nGOTE'S TEGOMA:");
      gote_c();
      printf(" %dP, %dL, %dN, %dS, %dG, %dR, %dB\n", gote_hand[pawn-1], gote_hand[lance-1], gote_hand[knight-1], gote_hand[silver-1], gote_hand[gold-1], gote_hand[rook-1], gote_hand[bishop-1]);
      reset_c();
}

// Stamp the board V_2.2
void stampBoard(void){
      int i, i2;

      //printf("\033[2J\033[H"); // Refresh the Screen, DELETE IF YOU ARE ON WINDOWS!!!
		system("cls");
      printf("Last move: ");
      for(i=0; i<4; i++){
            printf("%d", moveCd[i]+1);
      }

      if(ch == sente){
            for(i=0; i<9; i++){
                  if(i==0){
                        printf("\n\n");
                        for(i2=0; i2<9; i2++){
                              printf("  %d. ", i2+1);
                        }
                        printf("\n+----+----+----+----+----+----+----+----+----+\n");
                  }


                  for(i2=0; i2<9; i2++){
                        printf("|");
                        switch (board[i][i2])
                        {
                              case n:
                                    printf("    ");
                                    break;
                              case pawn:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ P\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ P/");
                                    }
                                    reset_c();
                                    break;
                              case lance:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ L\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ L/");
                                    }
                                    reset_c();
                                    break;
                              case knight:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ N\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ N/");
                                    }
                                    reset_c();
                                    break;
                              case silver:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ S\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ S/");
                                    }
                                    reset_c();
                                    break;
                              case gold:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ G\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ G/");
                                    }
                                    reset_c();
                                    break;
                              case rook:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ R\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ R/");
                                    }
                                    reset_c();
                                    break;
                              case bishop:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ B\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ B/");
                                    }
                                    reset_c();
                                    break;
                              case king:
                                    if(color[i][i2] == sente){
                                          sente_c();
                                          printf("/ K\\");
                                    }
                                    if(color[i][i2] == gote){
                                          gote_c();
                                          printf("\\ K/");
                                    }
                                    reset_c();
                                    break;
                              default:
                                    break;
                        }
                        if(i2==8){
                              printf("| %d.", i+1);
                        }
                  }

                  printf("\n+----+----+----+----+----+----+----+----+----+\n");

            }
      }
      if(ch == gote){
            for(i=8; i>=0; i--){
                  if(i==8){
                        printf("\n\n");
                        for(i2=0; i2<9; i2++){
                              printf("  %d. ", i2+1);
                        }
                        printf("\n+----+----+----+----+----+----+----+----+----+\n");
                  }


                  for(i2=0; i2<9; i2++){
                        printf("|");
                        switch (board[i][i2])
                        {
                        case n:
                              printf("    ");
                              break;
                        case pawn:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ P/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ P\\");
                              }
                              reset_c();
                              break;
                        case lance:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ L/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ L\\");
                              }
                              reset_c();
                              break;
                        case knight:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ N/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ N\\");
                              }
                              reset_c();
                              break;
                        case silver:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ S/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ S\\");
                              }
                              reset_c();
                              break;
                        case gold:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ G/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ G\\");
                              }
                              reset_c();
                              break;
                        case rook:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ R/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ R\\");
                              }
                              reset_c();
                              break;
                        case bishop:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ B/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ B\\");
                              }
                              reset_c();
                              break;
                        case king:
                              if (color[i][i2] == sente)
                              {
                                    sente_c();
                                    printf("\\ K/");
                              }
                              if (color[i][i2] == gote)
                              {
                                    gote_c();
                                    printf("/ K\\");
                              }
                              reset_c();
                              break;
                        default:
                              break;
                        }
                        if(i2==8){
                              printf("| %d.", i+1);
                        }
                  }

                  printf("\n+----+----+----+----+----+----+----+----+----+\n");
            }
      }
      printf("\nSENTE'S TEGOMA: ");
      sente_c();
      printf("%dP, %dL, %dN, %dS, %dG, %dR, %dB\n", sente_hand[pawn-1], sente_hand[lance-1], sente_hand[knight-1], sente_hand[silver-1], sente_hand[gold-1], sente_hand[rook-1], sente_hand[bishop-1]);
      reset_c();
      printf("\nGOTE'S TEGOMA:");
      gote_c();
      printf(" %dP, %dL, %dN, %dS, %dG, %dR, %dB\n", gote_hand[pawn-1], gote_hand[lance-1], gote_hand[knight-1], gote_hand[silver-1], gote_hand[gold-1], gote_hand[rook-1], gote_hand[bishop-1]);
      reset_c();
}

// Automatic promote pieces
void auto_promote(void){
    int i, i2;
    
    for(i=0; i<9; i++){
        for(i2=0; i2<9; i2++){
            int pc[2] = {board[i][i2], color[i][i2]};
            
            switch (pc[0]) {
                case pawn:
                    if(pc[1] == sente){
                        if(i < 3){
                            board[i][i2] = gold;
                        }
                    }
                    if(pc[1] == gote){
                        if(i >= 6){
                            board[i][i2] = gold;
                        }
                    }
                case lance:
                    if(pc[1] == sente){
                        if(i < 3){
                            board[i][i2] = gold;
                        }
                    }
                    if(pc[1] == gote){
                        if(i >= 6){
                            board[i][i2] = gold;
                        }
                    }
                case knight:
                    if(pc[1] == sente){
                        if(i < 3){
                            board[i][i2] = gold;
                        }
                    }
                    if(pc[1] == gote){
                        if(i >= 6){
                            board[i][i2] = gold;
                        }
                    }
                case silver:
                    if(pc[1] == sente){
                        if(i < 3){
                            board[i][i2] = gold;
                        }
                    }
                    if(pc[1] == gote){
                        if(i >= 6){
                            board[i][i2] = gold;
                        }
                    }
                    break;
            }
        }
    }
}

// Validate Moves
bool Validate(int moveCk[4], int ck_h){
      int i;
      bool valid = false;

      int pc[2] = {board[moveCk[0]][moveCk[1]], color[moveCk[0]][moveCk[1]]};

      switch(pc[0]){
          case n:
              valid = false;
          case pawn:
                  if(pc[1] == sente){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && (moveCk[0]-moveCk[2]) == 1 && moveCk[1] == moveCk[3]){
                              valid = true;
                      }
                  }
                  if(pc[1] == gote){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && (moveCk[2]-moveCk[0]) == 1 && moveCk[1] == moveCk[3]){
                              valid = true;
                      }
                  }
                  break;
          case lance:
                  if(pc[1] == sente){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && (moveCk[0]-moveCk[2]) >= 1 && moveCk[1] == moveCk[3]){
                              valid = true;
                      }
                      for(i=moveCk[0]-1; i>moveCk[2]; i--){
                            if(color[i][moveCk[1]] == sente){
                                valid = false;
                            }
                            if(color[i][moveCk[1]] == gote && i>(moveCk[2]+1)){
                                valid = false;
                            }
                      }
                  }
                  if(pc[1] == gote){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && (moveCk[2]-moveCk[0]) >= 1 && moveCk[1] == moveCk[3]){
                              valid = true;
                      }
                      for(i=moveCk[0]+1; i<moveCk[2]; i++){
                            if(color[i][moveCk[1]] == gote){
                                valid = false;
                            }
                            if(color[i][moveCk[1]] == gote && i<(moveCk[2]-1)){
                                valid = false;
                            }
                      }
                  }
                  break;
          case rook:
                  if(pc[1] == sente){
                        if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && (moveCk[1] == moveCk[3] ||  moveCk[0] == moveCk[2])){
                              valid = true;
                        }
                        if(moveCk[1] == moveCk[3]){
                              if(moveCk[0] > moveCk[2]){
                                    for(i=moveCk[0]-1; i>moveCk[2]; i--){
                                        if(color[i][moveCk[1]] == sente){
                                            valid = false;
                                        }
                                        if(color[i][moveCk[1]] == gote && i>(moveCk[2]+1)){
                                            valid = false;
                                        }
                                    }
                              }
                              if(moveCk[0] < moveCk[2]){
                                    for(i=moveCk[0]+1; i<moveCk[2]; i++){
                                        if(color[i][moveCk[1]] == sente){
                                            valid = false;
                                        }
                                        if(color[i][moveCk[1]] == gote && i<(moveCk[2]-1)){
                                            valid = false;
                                        }
                                    }
                              }
                        }
                        if(moveCk[0] == moveCk[2]) {
                              if(moveCk[1] > moveCk[3]){
                                    for(i=moveCk[1]-1; i>moveCk[3]; i--){
                                        if(color[moveCk[0]][i] == sente){
                                              valid = false;
                                        }
                                        if(color[moveCk[0]][i] == gote && i>(moveCk[3]+1)){
                                            valid = false;
                                        }
                                    }
                              }
                              if(moveCk[1] < moveCk[3]){
                                    for(i=moveCk[1]+1; i<moveCk[3]; i++){
                                        if(color[moveCk[0]][i] == sente){
                                            valid = false;
                                        }
                                        if(color[moveCk[0]][i] == gote && i<(moveCk[3]-1)){
                                            valid = false;
                                        }
                                    }
                              }
                        }
                  }
                  if(pc[1] == gote){
                        if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && (moveCk[1] == moveCk[3] || moveCk[0] == moveCk[2])){
                              valid = true;
                        }
                        if(moveCk[1] == moveCk[3]){
                              if(moveCk[0] > moveCk[2]){
                                    for(i=moveCk[0]-1; i>moveCk[2]; i--){
                                        if(color[i][moveCk[1]] == gote){
                                            valid = false;
                                        }
                                        if(color[i][moveCk[1]] == sente && i>(moveCk[2]+1)){
                                            valid = false;
                                        }
                                    }
                              }
                              if(moveCk[0] < moveCk[2]){
                                    for(i=moveCk[0]+1; i<moveCk[2]; i++){
                                        if(color[i][moveCk[1]] == gote){
                                            valid = false;
                                        }
                                        if(color[i][moveCk[1]] == sente && i<(moveCk[2]-1)){
                                            valid = false;
                                        }
                                    }
                              }
                        }
                        if(moveCk[0] == moveCk[2]) {
                              if(moveCk[1] > moveCk[3]){
                                    for(i=moveCk[1]-1; i>moveCk[3]; i--){
                                        if(color[moveCk[0]][i] == gote){
                                            valid = false;
                                        }
                                        if(color[moveCk[0]][i] == sente && i>(moveCk[3]+1)){
                                            valid = false;
                                        }
                                    }
                              }
                              if(moveCk[1] < moveCk[3]){
                                    for(i=moveCk[1]+1; i<moveCk[3]; i++){
                                        if(color[moveCk[0]][i] == gote){
                                            valid = false;
                                        }
                                        if(color[moveCk[0]][i] == sente && i<(moveCk[3]-1)){
                                            valid = false;
                                        }
                                    }
                              }
                        }
                  }
                  break;
          case king:
                  if(pc[1] == sente){
                        if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && ((moveCk[0]+1 == moveCk[2] || moveCk[0]-1 == moveCk[2] || moveCk[0] == moveCk[2]) && (moveCk[1]+1 == moveCk[3] || moveCk[1]-1 == moveCk[3] || moveCk[1] == moveCk[3]))){
                              valid = true;
                        }
                  }
                  if(pc[1] == gote){
                        if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && ((moveCk[0]+1 == moveCk[2] || moveCk[0]-1 == moveCk[2] || moveCk[0] == moveCk[2]) && (moveCk[1]+1 == moveCk[3] || moveCk[1]-1 == moveCk[3] || moveCk[1] == moveCk[3]))){
                              valid = true;
                        }
                  }
                  break;
          case bishop:
                  if(pc[1] == sente){
                        if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && (moveCk[0] - moveCk[2] == moveCk[3] - moveCk[1] || moveCk[0] - moveCk[2] == moveCk[1] - moveCk[3] || moveCk[2] - moveCk[0] == moveCk[1] - moveCk[3] || moveCk[2] - moveCk[0] == moveCk[3] - moveCk[1])){
                              valid = true;
                        }
                        if(moveCk[0] > moveCk[2] || moveCk[1] < moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[0]-moveCk[2]); i++){
                                  if(color[moveCk[0]-1][moveCk[1]+1] == sente){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]-1][moveCk[1]+1] == gote && i<(moveCk[0]-moveCk[2]-1)){
                                          valid = false;
                                  }
                              }
                        }
                        if(moveCk[0] > moveCk[2] || moveCk[1] > moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[0]-moveCk[2]); i++){
                                  if(color[moveCk[0]-1][moveCk[1]-1] == sente){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]-1][moveCk[1]-1] == gote && i<(moveCk[0]-moveCk[2]-1)){
                                          valid = false;
                                  }
                              }
                        }
                        if(moveCk[0] < moveCk[2] || moveCk[1] > moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[2]-moveCk[0]); i++){
                                  if(color[moveCk[0]+1][moveCk[1]-1] == sente){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]+1][moveCk[1]-1] == gote && i<(moveCk[2]-moveCk[0]-1)){
                                          valid = false;
                                  }
                              }
                        }
                        if(moveCk[0] < moveCk[2] || moveCk[1] < moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[2]-moveCk[0]); i++){
                                  if(color[moveCk[0]+1][moveCk[1]+1] == sente){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]+1][moveCk[1]+1] == gote && i<(moveCk[2]-moveCk[0]-1)){
                                          valid = false;
                                  }
                              }
                        }
                  }
                  if(pc[1] == gote){
                        if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && (moveCk[0] - moveCk[2] == moveCk[3] - moveCk[1] || moveCk[0] - moveCk[2] == moveCk[1] - moveCk[3] || moveCk[2] - moveCk[0] == moveCk[1] - moveCk[3] || moveCk[2] - moveCk[0] == moveCk[3] - moveCk[1])){
                              valid = true;
                        }
                        if(moveCk[0] > moveCk[2] || moveCk[1] < moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[0]-moveCk[2]); i++){
                                  if(color[moveCk[0]-1][moveCk[1]+1] == gote){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]-1][moveCk[1]+1] == sente && i<(moveCk[0]-moveCk[2]-1)){
                                          valid = false;
                                  }
                              }
                        }
                        if(moveCk[0] > moveCk[2] || moveCk[1] > moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[0]-moveCk[2]); i++){
                                  if(color[moveCk[0]-1][moveCk[1]-1] == gote){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]-1][moveCk[1]-1] == sente && i<(moveCk[0]-moveCk[2]-1)){
                                          valid = false;
                                  }
                              }
                        }
                        if(moveCk[0] < moveCk[2] || moveCk[1] > moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[2]-moveCk[0]); i++){
                                  if(color[moveCk[0]+1][moveCk[1]-1] == gote){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]+1][moveCk[1]-1] == sente && i<(moveCk[2]-moveCk[0]-1)){
                                          valid = false;
                                  }
                              }
                        }
                        if(moveCk[0] < moveCk[2] || moveCk[1] < moveCk[3]){
                              for(i=moveCk[0]+1; i<(moveCk[2]-moveCk[0]); i++){
                                  if(color[moveCk[0]+1][moveCk[1]+1] == gote){
                                          valid = false;
                                  }
                                  if(color[moveCk[0]+1][moveCk[1]+1] == sente && i<(moveCk[2]-moveCk[0]-1)){
                                          valid = false;
                                  }
                              }
                        }
                  }
                  break;
          case knight:
                  if(pc[1] == sente){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && moveCk[2] == moveCk[0]-2 && (moveCk[3] == moveCk[1]-1 || moveCk[3] == moveCk[1]+1)){
                              valid = true;
                      }
                  }
                  if(pc[1] == gote){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && moveCk[0] == moveCk[2]-2 && (moveCk[3] == moveCk[1]-1 || moveCk[3] == moveCk[1]+1)){
                              valid = true;
                      }
                  }
                  break;
          case silver:
                  if(pc[1] == sente){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && ((moveCk[0]+1 == moveCk[2] || moveCk[0]-1 == moveCk[2]) && (moveCk[1]+1 == moveCk[3] || moveCk[1]-1 == moveCk[3] || moveCk[1] == moveCk[3]) && !(moveCk[2] == moveCk[0]+1 && moveCk[1] == moveCk[3]))){
                              valid = true;
                      }
                  }
                  if(pc[1] == gote){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && ((moveCk[0]+1 == moveCk[2] || moveCk[0]-1 == moveCk[2]) && (moveCk[1]+1 == moveCk[3] || moveCk[1]-1 == moveCk[3] || moveCk[1] == moveCk[3]) && !(moveCk[2] == moveCk[0]-1 && moveCk[1] == moveCk[3]))){
                              valid = true;
                      }
                  }
                  break;
          case gold:
                  if(pc[1] == sente){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == gote) && ck_h == sente && ((moveCk[0]+1 == moveCk[2] || moveCk[0]-1 == moveCk[2] || moveCk[0] == moveCk[2]) && (moveCk[1]+1 == moveCk[3] || moveCk[1]-1 == moveCk[3] || moveCk[1] == moveCk[3]) && !((moveCk[2] == moveCk[0]+1 && moveCk[3] == moveCk[1]+1) || (moveCk[2] == moveCk[0]+1 && moveCk[3] == moveCk[1]-1)))){
                              valid = true;
                      }
                  }
                  if(pc[1] == gote){
                      if((board[moveCk[2]][moveCk[3]] == n || color[moveCk[2]][moveCk[3]] == sente) && ck_h == gote && ((moveCk[0]+1 == moveCk[2] || moveCk[0]-1 == moveCk[2] || moveCk[0] == moveCk[2]) && (moveCk[1]+1 == moveCk[3] || moveCk[1]-1 == moveCk[3] || moveCk[1] == moveCk[3]) && !((moveCk[2] == moveCk[0]-1 && moveCk[3] == moveCk[1]+1) || (moveCk[2] == moveCk[0]-1 && moveCk[3] == moveCk[1]-1)))){
                              valid = true;
                      }
                  }
                  break;
            default:
                  break;
      }
    
    if(board[moveCk[0]][moveCk[1]] == n){
        valid = false;
    }
    
    if(moveCk[0] > 9 || moveCk[1] > 9 || moveCk[2] > 9 || moveCk[3] > 9){
        valid = false;
    }
      
    if(moveCk[0] == 9 && moveCk[1] == 9 && moveCk[2] == 9 && moveCk[3] == 9){
        valid = true;
    }

    return valid;
}

// Take enemy pieces
void attackPiece(void){
      int pc = board[moveCd[2]][moveCd[3]];
      if((Validate(moveCd, ch) == true) && (pc != 0)){
            switch (pc){
                  case pawn:
                        if(ch == sente){
                              sente_hand[pawn-1]++;
                        }
                        if(ch == gote){
                              gote_hand[pawn-1]++;
                        }
                        break;
                  case rook:
                        if(ch == sente){
                              sente_hand[rook-1]++;
                        }
                        if(ch == gote){
                              gote_hand[rook-1]++;
                        }
                        break;
                  case bishop:
                        if(ch == sente){
                              sente_hand[bishop-1]++;
                        }
                        if(ch == gote){
                              gote_hand[bishop-1]++;
                        }
                        break;
                  case gold:
                        if(ch == sente){
                              sente_hand[gold-1]++;
                        }
                        if(ch == gote){
                              gote_hand[gold-1]++;
                        }
                        break;
                  case silver:
                        if(ch == sente){
                              sente_hand[silver-1]++;
                        }
                        if(ch == gote){
                              gote_hand[silver-1]++;
                        }
                        break;
                  case knight:
                        if(ch == sente){
                              sente_hand[knight-1]++;
                        }
                        if(ch == gote){
                              gote_hand[knight-1]++;
                        }
                        break;
                  case lance:
                        if(ch == sente){
                              sente_hand[lance-1]++;
                        }
                        if(ch == gote){
                              gote_hand[lance-1]++;
                        }
                        break;
            }
      }
}

// Pieces Moving
void movePiece(void){
      int pc[2] = {board[moveCd[0]][moveCd[1]], color[moveCd[0]][moveCd[1]]};

      switch (pc[0])
      {
            case pawn:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = pawn;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case lance:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = lance;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case rook:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = rook;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case king:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = king;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case bishop:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = bishop;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case knight:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = knight;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case silver:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = silver;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
            case gold:
                  board[moveCd[0]][moveCd[1]] = n;
                  board[moveCd[2]][moveCd[3]] = gold;
                  color[moveCd[0]][moveCd[1]] = n;
                  if(ch == sente) color[moveCd[2]][moveCd[3]] = sente;
                  if(ch == gote) color[moveCd[2]][moveCd[3]] = gote;
                  break;
      }
}

// Drop pieces in your hand
bool dropPiece(void){
      int piece, cod[2], i; // piece, coordinates
      char cd[2]; // coordinates
      bool exit = false;

      stampBoard();

      printf("\nChose the piece that u want to drop: \n\n");
      printf("\t1. pawn\t\t2. lance\t3. knight\n\n\t4. silver general\t5. gold general\n\n\t6. rook\t\t7. bishop\t0. EXIT\n");
      do{
            printf("\nPiece code: ");
            scanf("%d", &piece);
            if(piece == 0){
                  exit = true;
            }
      } while((!(ch == sente && sente_hand[piece-1] > 0 && exit == false && piece > 0 && piece < 8) && !(ch == gote && gote_hand[piece-1] != 0 && exit == false && piece > 0 && piece < 8)) && exit == false);

      if(exit == false){
            do{
                  printf("\nPlacing coordinates('0' to exit): ");
                  scanf("%s", cd);
                  cod[0] = traslate(cd[0]);
                  cod[1] = traslate(cd[1]);
                  if(cod[0] == 9 && cod[1] == 9){
                        exit = true;
                  }
                if(piece == pawn){
                    for (i=0; i<9; i++) {
                        if (board[i][cod[1]] == pawn && color[i][cod[1]] == ch) {
                            exit = true;
                        }
                    }
                }
            } while((board[cod[0]][cod[1]] != 0 || cod[0] > 8 || cod[1] > 8) && exit == false);

            if(exit == false){
                board[cod[0]][cod[1]] = pawn;
                color[cod[0]][cod[1]] = ch;
                if (ch == sente) {
                      sente_hand[piece-1]--;
                }
                if (ch == gote) {
                      gote_hand[piece-1]--;
                }
                  
          }
      }

      return exit;
}

// Simple win algorithm
int simpleWin(void){
    int i, i2, wnnr = 0;
    bool iS = false, iG = false;
    
    for(i=0; i<9; i++){
        for(i2=0; i2<9; i2++){
            if(board[i][i2] == king && color[i][i2] == sente){
                iS = true;
            }
            if(board[i][i2] == king && color[i][i2] == gote){
                iG = true;
            }
        }
    }
    
    if(iS == false && iG == true){
        wnnr = gote;
        ck_mate = true;
    }
    if(iG == false && iS == true){
        wnnr = sente;
        ck_mate = true;
    }
    
    return wnnr;
}

// Sente wins banner
void senteWins(void){
      printf("\033[2J\033[H\n"); // Refresh the Screen, DELETE IF YOU ARE ON WINDOWS!!!

      printf("+-----------------------------------+\n");
      printf("|                                   |\n");
      printf("|    ");
      sente_c();
      printf("SENTE WINS, CONGRATULATION!    |\n");
      reset_c();
      printf("|                                   |\n");
      printf("+-----------------------------------+\n");
}

// Gote Wins Banner
void goteWins(void){
      printf("\033[2J\033[H\n"); // Refresh the Screen, DELETE IF YOU ARE ON WINDOWS!!!

      printf("+-----------------------------------+\n");
      printf("|                                   |\n");
      printf("|     ");
      gote_c();
      printf("GOTE WINS, CONGRATULATION!    |\n");
      reset_c();
      printf("|                                   |\n");
      printf("+-----------------------------------+\n");
}

// MAIN
int main(int argc, char *argv[]){

    char m[4];
    int i, wnnr;
    bool exit;

    ch = sente;
    bool smate = false;
    ck_mate = false;

    do{
        stampBoard();
        
        do{
            if(ch == sente){
                printf("\nSente Moves, your move is? ");
                scanf("%s", m);
            }
            if(ch == gote){
                printf("\nGote Moves, your move is? ");
                scanf("%s", m);
            }

            for(i=0; i<4; i++){
                moveCd[i] = traslate(m[i]);
            }
            
            if(Validate(moveCd, ch) == false){
                printf("\n\nIllegal_move(1)\n\n");
            }

        } while(Validate(moveCd, ch) == false || smate == true);
        
        
        if(moveCd[0] == 9 && moveCd[1] == 9 && moveCd[2] == 9 && moveCd[3] == 9){
            exit = dropPiece();
        }
        else{
            attackPiece();
            movePiece();
            exit = false;
        }
        if(exit == false){
            if(ch == sente) ch = gote;
            else ch = sente;
        }
        
        auto_promote();
        
        wnnr = simpleWin();

    } while (ck_mate == false);
    
    if (wnnr == sente) {
        senteWins();
    }
    if (wnnr == gote) {
        goteWins();
    }

    return 0;
}
