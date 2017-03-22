//
//  AI.hpp
//  Othello Project
//
//  Created by Jack on 3/16/17.
//  Copyright © 2017 A_J_T. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include <iostream>

int newBoard();
int drawBoard();
int move();
bool isLegal(int, int);
int test(int, int, char);
int flip(int, int);
int lineTest(int, int, int, int, char);
int lineFlip(int, int, int, int, char);
char count();
bool areLegalMoves();
char nextMark();


#endif /* AI_hpp */
