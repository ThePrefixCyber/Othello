#include <iostream>
#include <algorithm>
using namespace std;

void initiate_board(char board[8][8]);
bool game_over(char board[8][8]);
void print_board(char board[8][8]);
bool are_legal_moves(char board[8][8], char player);
char opponent(char player);
bool is_legal_move(char board[8][8], int row, int col, char player);
void update_board(char board[8][8], int row, int col, char player);
void print_score(char board[8][8]);

int main()
{
    
    char board[8][8];
    initiate_board(board);
    
    int row, col;
    char player = 'X';
    while(!game_over(board)) {
        print_board(board);
        print_score(board);
        cout<<"\nIt is Player "<<player<<"\'s turn.\n\n";
        if(!are_legal_moves(board, player)) {
            cout<<"Player "<<player<<" has no legal moves.\n";
            player = opponent(player);
            cout<<"\nIt is Player "<<player<<"\'s turn.\n\n";
        }
        cout<<"Select row: \n";
        cin>>row;
        cout<<"Select col: \n";
        cin>>col;
        cin.clear();
        cin.ignore();
        if(!is_legal_move(board, row, col, player)) {
            cout<<"\nNot a legal move!\n\n";
        } else {
            update_board(board, row, col, player);
            player = opponent(player);
        }
    }
    
    if(game_over(board)) {
        cout<< "\nGAME OVER!\n";
        print_score(board);
    }
    
    return 0;
    
}

void initiate_board(char board[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if((i == 3 && j == 3) || (i == 4 && j == 4)) {
                board[i][j] = 'X';
            } else if((i == 3 && j == 4) || (i == 4 && j == 3)) {
                board[i][j] = 'O';
            } else {
                board[i][j] = '_';
            }
        }
    }
    return;
}

void print_board(char board[8][8]) {
    cout<<"  0 1 2 3 4 5 6 7 \n";
    for(int i = 0; i < 8; i++) {
        cout<<i<<'|';
        for(int j = 0; j < 8; j++) {
            cout<<board[i][j]<<'|';
        }
        cout<<endl;
    }
}

int score(char board[8][8], char player) {
    int score = 0;
    if(player == 'X') {
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(board[row][col] == 'X') {
                    score += 1;
                }
            }
        }
    } else if(player == 'O') {
        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(board[row][col] == 'O') {
                    score += 1;
                }
            }
        }
    }
    return score;
}

void print_score(char board[8][8]) {
    cout<<"\nSCORE:\n";
    cout<<"Player X: "<<score(board,'X')<<"\n";
    cout<<"Player O: "<<score(board,'O')<<"\n";
}

char opponent(char player) {
    if(player == 'X') {
        return 'O';
    }
    if(player == 'O') {
        return 'X';
    }
    return '!'; // ERROR
}

bool check_n(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row-1][col]=='_' || board[row-1][col]==player) {
        return 0;
    } else {
        for(int i = 2; i <= row; i++) {
            // open-faced sandwich, no bun
            if(board[row-i][col]=='_') {
                return 0;
            }
            // found the bun
            if(board[row-i][col]==player){
                return 1;
            }
        }
    }
    return 0;
}
    
bool check_ne(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row-1][col+1]=='_' || board[row-1][col+1]==player) {
        return 0;
    } else {
        for(int i = 2; i <= min(row,7-col); i++) {
            // open-faced sandwich, no bun
            if(board[row-i][col+i]=='_') {
                return 0;
            }
            // found the bun
            if(board[row-i][col+i]==player){
                return 1;
            }
        }
    }
    return 0;
}

bool check_e(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row][col+1]=='_' || board[row][col+1]==player) {
        return 0;
    } else {
        for(int i = 2; i <= 7-col; i++) {
            // open-faced sandwich, no bun
            if(board[row][col+i]=='_') {
                return 0;
            }
            // found the bun
            if(board[row][col+i]==player){
                return 1;
            }
        }
    }
    return 0;
}
    
bool check_se(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row+1][col+1]=='_' || board[row+1][col+1]==player) {
        return 0;
    } else {
        for(int i = 2; i <= min(7-row,7-col); i++) {
            // open-faced sandwich, no bun
            if(board[row+i][col+i]=='_') {
                return 0;
            }
            // found the bun
            if(board[row+i][col+i]==player){
                return 1;
            }
        }
    }
    return 0;
}

bool check_s(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row+1][col]=='_' || board[row+1][col]==player) {
        return 0;
    } else {
        for(int i = 2; i <= 7-row; i++) {
            // open-faced sandwich, no bun
            if(board[row+i][col]=='_') {
                return 0;
            }
            // found the bun
            if(board[row+i][col]==player){
                return 1;
            }
        }
    }
    return 0;
}
    
bool check_sw(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row+1][col-1]=='_' || board[row+1][col-1]==player) {
        return 0;
    } else {
        for(int i = 2; i <= min(7-row,col); i++) {
            // open-faced sandwich, no bun
            if(board[row+i][col-i]=='_') {
                return 0;
            }
            // found the bun
            if(board[row+i][col-i]==player){
                return 1;
            }
        }
    }
    return 0;
}

bool check_w(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row][col-1]=='_' || board[row][col-1]==player) {
        return 0;
    } else {
        for(int i = 2; i <= col; i++) {
            // open-faced sandwich, no bun
            if(board[row][col-i]=='_') {
                return 0;
            }
            // found the bun
            if(board[row][col-i]==player){
                return 1;
            }
        }
    }
    return 0;
}
    
bool check_nw(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row-1][col-1]=='_' || board[row-1][col-1]==player) {
        return 0;
    } else {
        for(int i = 2; i <= min(row,col); i++) {
            // open-faced sandwich, no bun
            if(board[row-i][col-i]=='_') {
                return 0;
            }
            // found the bun
            if(board[row-i][col-i]==player){
                return 1;
            }
        }
    }
    return 0;
}

bool is_legal_move(char board[8][8], int row, int col, char player) {
    if(board[row][col]=='_' &&
        (
         check_n(board, row, col, player) ||
         check_ne(board, row, col, player) ||
         check_e(board, row, col, player) ||
         check_se(board, row, col, player) ||
         check_s(board, row, col, player) ||
         check_sw(board, row, col, player) ||
         check_w(board, row, col, player) ||
         check_nw(board, row, col, player) 
        )
      ) {
        return 1;
    } else {
        return 0;
    }
}

bool are_legal_moves(char board[8][8], char player) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            if(is_legal_move(board, row, col, player)) {
                return 1;
            }
        }
    }
    return 0;
}

bool game_over(char board[8][8]) {
    if(!are_legal_moves(board, 'X') && !are_legal_moves(board, 'O')) {
        return 1;
    } else {
        return 0;
    }
}

void update_n(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row-1][col]=='_' || board[row-1][col]==player) {
        return;
    } else {
        for(int i = 2; i <= row; i++) {
            // open-faced sandwich, no bun
            if(board[row-i][col]=='_') {
                return;
            }
            // found the bun
            if(board[row-i][col]==player){
                for(int j = 1; j < i; j++) {
                    board[row-j][col] = player;
                };
            }
        }
    }
    return;
}
    
void update_ne(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row-1][col+1]=='_' || board[row-1][col+1]==player) {
        return;
    } else {
        for(int i = 2; i <= min(row,7-col); i++) {
            // open-faced sandwich, no bun
            if(board[row-i][col+i]=='_') {
                return;
            }
            // found the bun
            if(board[row-i][col+i]==player){
                for(int j = 1; j < i; j++) {
                    board[row-j][col+j] = player;
                };
            }
        }
    }
    return;
}

void update_e(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row][col+1]=='_' || board[row][col+1]==player) {
        return;
    } else {
        for(int i = 2; i <= 7-col; i++) {
            // open-faced sandwich, no bun
            if(board[row][col+i]=='_') {
                return;
            }
            // found the bun
            if(board[row][col+i]==player){
                for(int j = 1; j < i; j++) {
                    board[row][col+j] = player;
                };
            }
        }
    }
    return;
}
    
void update_se(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row+1][col+1]=='_' || board[row+1][col+1]==player) {
        return;
    } else {
        for(int i = 2; i <= min(7-row,7-col); i++) {
            // open-faced sandwich, no bun
            if(board[row+i][col+i]=='_') {
                return;
            }
            // found the bun
            if(board[row+i][col+i]==player){
                for(int j = 1; j < i; j++) {
                    board[row+j][col+j] = player;
                };
            }
        }
    }
    return;
}

void update_s(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row+1][col]=='_' || board[row+1][col]==player) {
        return;
    } else {
        for(int i = 2; i <= 7-row; i++) {
            // open-faced sandwich, no bun
            if(board[row+i][col]=='_') {
                return;
            }
            // found the bun
            if(board[row+i][col]==player){
                for(int j = 1; j < i; j++) {
                    board[row+j][col] = player;
                };
            }
        }
    }
    return;
}
    
void update_sw(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row+1][col-1]=='_' || board[row+1][col-1]==player) {
        return;
    } else {
        for(int i = 2; i <= min(7-row,col); i++) {
            // open-faced sandwich, no bun
            if(board[row+i][col-i]=='_') {
                return;
            }
            // found the bun
            if(board[row+i][col-i]==player){
                for(int j = 1; j < i; j++) {
                    board[row+j][col-j] = player;
                };
            }
        }
    }
    return;
}

void update_w(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row][col-1]=='_' || board[row][col-1]==player) {
        return;
    } else {
        for(int i = 2; i <= col; i++) {
            // open-faced sandwich, no bun
            if(board[row][col-i]=='_') {
                return;
            }
            // found the bun
            if(board[row][col-i]==player){
                for(int j = 1; j < i; j++) {
                    board[row][col-j] = player;
                };
            }
        }
    }
    return;
}
    
void update_nw(char board[8][8], int row, int col, char player) {
    // is there meat in the sandwich?
    if(board[row-1][col-1]=='_' || board[row-1][col-1]==player) {
        return;
    } else {
        for(int i = 2; i <= min(row,col); i++) {
            // open-faced sandwich, no bun
            if(board[row-i][col-i]=='_') {
                return;
            }
            // found the bun
            if(board[row-i][col-i]==player){
                for(int j = 1; j < i; j++) {
                    board[row-j][col-j] = player;
                };
            }
        }
    }
    return;
}

void update_board(char board[8][8], int row, int col, char player) {
    board[row][col] = player;
    update_n(board, row, col, player);
    update_ne(board, row, col, player);
    update_e(board, row, col, player);
    update_se(board, row, col, player);
    update_s(board, row, col, player);
    update_sw(board, row, col, player);
    update_w(board, row, col, player);
    update_nw(board, row, col, player);
    return;
}
