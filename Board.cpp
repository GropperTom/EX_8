//
// Created by tal on 06/05/18.
//

#include <vector>
#include <string>
#include <iostream>
#include "Board.h"
#include "Coordinate.hpp"
#include "IllegalCoordinateException.h"
#include "IllegalCharException.h"

Board::Board(int size)
        : _size(size), _board(new vector<vector<Symbol>*>()){
    for (int innerVector = 0; innerVector < _size; ++innerVector) {
        _board->push_back(new vector<Symbol>());
    }
    for (vector<Symbol>* vec : *_board){
        for (int SymbolCoordinate = 0; SymbolCoordinate < _size; ++SymbolCoordinate){
            vec->push_back(Board::Symbol('.'));
        }
    }
}

Board::Board(Board& board) {
	_board = new vector<vector<Symbol>*>();
	_size = board._size;
	for (vector<Symbol>* row : *board._board) {
		vector<Symbol>* new_row = new vector<Symbol>();
		_board->push_back(new_row);
		for (Symbol symbol : *row) {
			new_row->push_back(*(new Symbol(symbol.getChar())));
		}
	}
}

Board::~Board() {
	delBoard();
}

void Board::delBoard() {
	for (vector<Board::Symbol>* vectorToRemove : *_board) {
		delete vectorToRemove;
	}
	delete _board;
}

vector<vector<Board::Symbol>*>* Board::getBoard() const {
    return _board;
}

ostream& operator<<(ostream &out, Board &board){
    string ans = "";
    for(vector<Board::Symbol>* vector : *(board.getBoard())){
        for(Board::Symbol Symbol : *vector){
            out << Symbol.getChar();
        }
        out << endl;
    }
    return out;
}

ostream& operator<<(ostream &out, const Board &board){
    string ans = "";
    for(vector<Board::Symbol>* vector : *(board.getBoard())){
        for(Board::Symbol Symbol : *vector){
            out << Symbol.getChar();
        }
        out << endl;
    }
    return out;
}

Board& Board::operator=(char Symbol) {
    for(vector<Board::Symbol>* vector : *(_board)) {
        for (Board::Symbol& SymbolToChange : *vector) {
            SymbolToChange = Symbol;
        }
    }
    return *this;
}

Board& Board::operator=(Board& board) {
	delBoard();
	_board = new vector<vector<Symbol>*>();
	_size = board._size;
	for (vector<Symbol>* row : *board._board) {
		vector<Symbol>* new_row = new vector<Symbol>();
		_board->push_back(new_row);
		for (Symbol symbol : *row) {
			new_row->push_back(*(new Symbol(symbol.getChar())));
		}
	}
	return *this;
}

Board::Symbol& Board::operator[] (Coordinate coordinate) const{
    if (!isInBound(coordinate)){
        throw IllegalCoordinateException(coordinate.getRow(), coordinate.getCol());
    }
	else {
		vector<Symbol>* vec = (*_board)[coordinate.getRow()];
		return vec->at(coordinate.getCol());
	}
}

bool Board::isInBound(Coordinate& coordinate) const{
    if (coordinate.getRow() < 0 || coordinate.getRow()>= _size){
        return false;
    }
    if (coordinate.getCol() < 0 || coordinate.getCol()>= _size){
        return false;
    }
    return true;
}

Board::Symbol::Symbol(char c) {
	_val = c;
}

char Board::Symbol::getChar() {
	return _val;
}

Board::Symbol & Board::Symbol::operator=(char c) {
	if (c != 'X' && c != 'O' && c != '.') throw IllegalCharException(c + "");
	else _val = c;
	return *this;
}

Board::Symbol::operator char() {
	return _val;
}