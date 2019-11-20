/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 * 	Ammended on : May 4th, 2018
 * 		Author: engbergt
 */

#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include "MinimaxPlayer.h"


/* Start: Tarren's functions */



std::vector<action> MinimaxPlayer::successors(const OthelloBoard& state, int depth, char playerSymbol) { // (AKA 'actions') needs to return an set of legal board states. There should already be a function for state legality.
//    std::cout << "made it to successor func" << std::endl;
	std::vector<action> validSuccessors;

	for(int c = 0; c < state.get_num_cols(); c++){
		for(int r = 0; r < state.get_num_rows(); r++){
			if(state.is_legal_move(c, r, playerSymbol)){
				action tempAction(state);
				tempAction.resultantBoard.play_move(c, r, playerSymbol);
				//tempAction.resultantBoard.display();
				tempAction.column = c;
				tempAction.row = r;
                tempAction.depth = depth + 1;
				validSuccessors.push_back(tempAction);
				// OthelloBoard tempBoard = state; // Clone the board ?? Ask Glen.
				// tempBoard.play_move(c,r,????) // Add a piece to this c,r space, on the clone.
				// validSuccessors.push_back(state); // Push clone to the possible successors 
			}
		}
	}
	return validSuccessors;
}

int MinimaxPlayer::utility(const OthelloBoard& state) { 
	int p1score = state.count_score(state.get_p1_symbol());
	int p2score = state.count_score(state.get_p2_symbol());
	return p1score - p2score; // the utility of a board state is the max players on board points subtract the min players on board points.
}



// Minimax functions

action MinimaxPlayer::maxValue(const action& move){
//    std::cout << "made it to maxValue func: " << move.depth << std::endl;


	std::vector<action> succs = successors(move.resultantBoard, move.depth, move.resultantBoard.get_p1_symbol());
	if(succs.size() == 0){
//        std::cout << "finishing in maxValue func: " << move.depth << std::endl;
        action blah = move;
        blah.mmValue = utility(move.resultantBoard);
        return blah;
	}
	action bestMove = minValue(succs[0]);
    

	for(int i = 1; i < succs.size(); i++){
		action temp = minValue(succs[i]);
		if(temp.mmValue > bestMove.mmValue){
			bestMove = temp;
            
		}
		
	}
//    std::cout << "Best move: (" << bestMove.column << "," << bestMove.row << ")" << std::endl;
    action blah = move;
    blah.mmValue = bestMove.mmValue;
    return blah;
}

action MinimaxPlayer::minValue(const action& move){
//    std::cout << "made it to minValue func: " << move.depth << std::endl;


	std::vector<action> succs = successors(move.resultantBoard, move.depth, move.resultantBoard.get_p2_symbol());
    if(succs.size() == 0){
//        std::cout << "finishing minValue func: " << move.depth << std::endl;
        action blah = move;
        blah.mmValue = utility(move.resultantBoard);
        return blah;
    }
    action bestMove = maxValue(succs[0]);
    
    
	for(int i = 1; i < succs.size(); i++){
		action temp = maxValue(succs[i]);
		if(temp.mmValue < bestMove.mmValue){
			bestMove = temp;
		}
	}
    
//    std::cout << "Best move: (" << bestMove.column << "," << bestMove.row << ")" << std::endl;
    action blah = move;
    blah.mmValue = bestMove.mmValue;
	return blah;
}

action MinimaxPlayer::minimax(const OthelloBoard& state) {
//    std::cout << "made it to minmax func" << std::endl;
	std::vector<action> succs = successors(state, 0, state.get_p2_symbol());
	action bestMove = maxValue(succs[0]);

	for(int i = 1; i < succs.size(); i++){
		action temp = maxValue(succs[i]);
		if(temp.mmValue < bestMove.mmValue){
			bestMove = temp;
		}
		
	}
	return bestMove;

}



/* End: Tarren's functions */



MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
	
	action ourMove = minimax(*b);
	
	col = ourMove.column;
	row = ourMove.row;

}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
