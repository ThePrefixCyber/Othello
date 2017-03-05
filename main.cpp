//
//  main.cpp
//  Othello
//
//  Created by Jack on 2/10/17.
//  Copyright © 2017 Jack. All rights reserved.
//

#include <iostream>
using namespace std;

char board[8][8]; // blank = '_', white = O, black = X
int turnCount;
bool gameEnd;

int newBoard();
int drawBoard();
int move();
bool isLegal(int, int);
char getMark(int turn = turnCount);
int test(int, int, char);
int flip(int, int);
int lineTest(int, int, int, int, char);
int lineFlip(int, int, int, int, char);
char count();

int main(int argc, const char * argv[]) {
    
    while(1){
        turnCount=1;
        gameEnd=0;
        newBoard();
        drawBoard();
        cout << "Start game";
        while(!gameEnd){
            if(!move()){
                break;
            }
            drawBoard();
            if(turnCount>=8) gameEnd=1;
            cout << "Turn " << turnCount << endl;
            turnCount++;
        }
        cout << "End game: " << endl;
        switch(count()){
            case 'X':
                cout << "X wins\n";
                break;
            case 'O':
                cout << "O wins\n";
                break;
            case '_':
                cout << "Tie\n";
                break;
            default:
                cout << "Problem with count";
        }
        break;
    }
    return 1;
}

int newBoard(){
    
    char mark;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if((i==3&&j==3)||(i==4&&j==4)) mark = 'O';
            else if((i==4&&j==3)||(i==3&&j==4)) mark = 'X';
            else mark = '_';
            board[i][j] = mark;
        }
    }
    return 1;
}


int drawBoard(){
    cout << endl;
    for(int i=7;i>=0;i--){  //prints lines (increments through y axis)
        cout << i;
        for(int j=0;j<8;j++){  //prints spaces (increments through x axis)
            cout << '|';
            cout << board[j][i]; //print all values of var 1 (x) for given var 2 (y) for a given line.
        }
        cout << '|' << endl;
    }
    cout << "  0 1 2 3 4 5 6 7\n";
    return 0;
}

int move(){
    cout << "  " << endl;
    char mark = getMark();
    int x;
    int y;
    cout << "Enter move: " << mark << endl;
    cin >> x;
    if(x==9){       //Exit code, basically the thing exits if you enter 9 for either move.  Had to be a number or it would be more complicated
        return 0;
    }
    cin >> y;
    if(y==9){
        return 0;
    }
    cin.clear();
    cin.ignore();      //If an invalid input causes an error these fix the problem
    if(isLegal(x,y)){
        board[x][y] = mark;
        flip(x,y);
    }
    else{
        cout << "Illegal move";
        turnCount--;
    }
    
    return 1;
}

bool isLegal(int x, int y){
    
    char mark = getMark(turnCount-1);
    
    //Case 0: Out of Bounds
    if(x<0||x>7||y<0||y>7){
        cout << "Out of Bounds...";
        return 0;
    }
    
    //Case 1: Space is full
    if(board[x][y]!='_'){
        cout << "Space is not empty...";
        return 0;
    }
    
    //Case 2: No adjacent enemy piece
    int flag = test(x-1, y-1, mark)
             + test(x-1, y, mark)
             + test(x-1, y+1, mark)
             + test(x, y-1, mark)
             + test(x, y+1, mark)
             + test(x+1, y-1, mark)
             + test(x+1, y, mark)
             + test(x+1, y+1, mark);
    if(!flag){
        cout << "No adjacent enemy pieces...";
        return 0;
    }
    
    //Case 3: Can't capture
    flag = lineTest(x, y, -1, -1, mark)
         + lineTest(x, y, -1, 0, mark)
         + lineTest(x, y, -1, 1, mark)
         + lineTest(x, y, 0, -1, mark)
         + lineTest(x, y, 0, 1, mark)
         + lineTest(x, y, 1, -1, mark)
         + lineTest(x, y, 1, 0, mark)
         + lineTest(x, y, 1, 1, mark);
    if(!flag){
        cout << "Can't capture anything...";
        return 0;
    }
    
    //Final Case: Everything works
    return 1;
}

int test(int x, int y, char mark){
    if(board[x][y]==mark) return 1;
    return 0;
}

int lineTest(int x, int y, int dx, int dy, char mark){
    
    //If next cell is >7 or <0, fail
    if((x+dx)<0||(y+dy)<0||(x+dx)>7||(y+dy)>7){
        return 0;
    }
    
    //If next cell holds '_', fail
    if(board[x+dx][y+dy]=='_'){
        return 0;
    }
    
    //If next cell is mark, keep going
    if(board[x+dx][y+dy]==mark){
        return lineTest(x+dx, y+dy, dx, dy, mark);
    }
    
    //If next cell is anti-mark, and we are mark, success
    if(board[x][y]==mark){
        return 1;
    }
    
    //If next cell is anti-mark, and we are anti-mark, fail
    return 0;
}

int flip(int x, int y){
    char mark = getMark(turnCount -1);
    lineFlip(x,y,-1,-1, mark);
    lineFlip(x,y,-1,0, mark);
    lineFlip(x,y,-1,1, mark);
    lineFlip(x,y,0,-1, mark);
    lineFlip(x,y,0,1, mark);
    lineFlip(x,y,1,-1, mark);
    lineFlip(x,y,1,0, mark);
    lineFlip(x,y,1,1, mark);
    return 1;
}

int lineFlip(int x, int y, int dx, int dy, char mark){ //mark is the enemy pieces we're flipping
    
    //If next cell is >7 or <0, fail
    if((x+dx)<0||(y+dy)<0||(x+dx)>7||(y+dy)>7){
        return 0;
    }
    
    //If next cell holds '_', fail
    if(board[x+dx][y+dy]=='_'){
        return 0;
    }
    
    //If next cell is mark, call lineFlip on that cell. Proceed if legal, otherwise fail
    if(board[x+dx][y+dy]==mark){
        switch(lineFlip(x+dx, y+dy, dx, dy, mark)){
            case 1:
                break;
            case 0:
                return 0;
        }
    }
    
    //If next cell is anti-mark, and we are mark, flip and return
    if(board[x][y]==mark){
        cout << board[x+dx][y+dy];
        board[x][y]=board[x+dx][y+dy];
        return 1;
    }
    
    //If next cell is anti-mark, and we are anti-mark, fail
    return 0;
}

char getMark(int turn){
    char mark;
    switch(turn%2){
        case 0:
            mark = 'X';
            break;
        case 1:
            mark = 'O';
            break;
        default:
            cout << "error in getMark";
    }
    return mark;
}

char count(){
    char result;
    int xSum=0;
    int oSum=0;
    for(int i=7;i>=0;i--){  //prints lines (increments through y axis)
        for(int j=0;j<8;j++){  //prints spaces (increments through x axis)
            switch(board[i][j]){
                case 'X':
                    xSum++;
                    break;
                case 'O':
                    oSum++;
                    break;
                default:
                    break;
            }
        }
    }
    if(xSum>oSum){
        result = 'X';
    }
    else if(xSum<oSum){
        result = 'O';
    }
    else if(xSum==oSum){
        result = '_';
    }
    else result = 0;
    return result;
}
