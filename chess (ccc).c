#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 8
char board[SIZE][SIZE];

void initBoard() {
    char init[SIZE][SIZE] = {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    };
    memcpy(board, init, sizeof(init));
}

void printBoard() {
    printf("  a b c d e f g h\n");
    for(int i=0; i<SIZE; i++) {
        printf("%d ", SIZE-i);
        for(int j=0; j<SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", SIZE-i);
    }
    printf("  a b c d e f g h\n\n");
}

int notationToIndex(const char *pos, int *row, int *col) {
    if(strlen(pos)!=2) return 0;
    *col = pos[0]-'a';
    *row = SIZE-(pos[1]-'0');
    if(*row<0||*row>=SIZE||*col<0||*col>=SIZE) return 0;
    return 1;
}

int pathClear(int r1,int c1,int r2,int c2) {
    int dr = (r2>r1)?1:(r2<r1?-1:0);
    int dc = (c2>c1)?1:(c2<c1?-1:0);
    int r=r1+dr, c=c1+dc;
    while(r!=r2 || c!=c2) {
        if(board[r][c]!=' ') return 0;
        r+=dr; c+=dc;
    }
    return 1;
}

int validMove(char piece,int r1,int c1,int r2,int c2) {
    int dr=abs(r2-r1), dc=abs(c2-c1);
    switch(tolower(piece)) {
        case 'p': return (c1==c2 && ((isupper(piece)&&r2==r1-1)||(islower(piece)&&r2==r1+1)));
        case 'r': return (r1==r2||c1==c2) && pathClear(r1,c1,r2,c2);
        case 'b': return (dr==dc) && pathClear(r1,c1,r2,c2);
        case 'q': return ((r1==r2||c1==c2||dr==dc) && pathClear(r1,c1,r2,c2));
        case 'n': return (dr==2&&dc==1)||(dr==1&&dc==2);
        case 'k': return dr<=1 && dc<=1;
    }
    return 0;
}

int makeMove(const char *from,const char *to,int turn) {
    int r1,c1,r2,c2;
    if(!notationToIndex(from,&r1,&c1)||!notationToIndex(to,&r2,&c2)) {
        printf("Invalid input!\n"); return 0;
    }
    char piece=board[r1][c1];
    if(piece==' ') { printf("No piece at %s!\n",from); return 0; }
    if(turn==0 && !isupper(piece)) { printf("White must move White pieces!\n"); return 0; }
    if(turn==1 && !islower(piece)) { printf("Black must move Black pieces!\n"); return 0; }
    if(!validMove(piece,r1,c1,r2,c2)) { printf("Illegal move!\n"); return 0; }
    board[r2][c2]=piece;
    board[r1][c1]=' ';
    return 1;
}

int main() {
    char from[3],to[3];
    int turn=0;
    initBoard();
    printBoard();
    while(1) {
        printf("%s's move (e.g., e2 e4): ",turn==0?"White":"Black");
        if(scanf("%2s %2s",from,to)!=2) break;
        if(makeMove(from,to,turn)) turn=1-turn;
        printBoard();
    }
    return 0;
}
