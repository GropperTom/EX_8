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

string Board::draw(int n) {
	struct Pixel {
		uint8_t _red, _green, _blue;

	public:
		Pixel() {}
		Pixel(uint8_t red, uint8_t green, uint8_t blue) : _red(red), _green(green), _blue(blue) {}
	};

	ofstream imgFile("cpp.ppm", ios::out | ios::binary);
	imgFile << "P6" << endl << n << " " << n << endl << 255 << endl;

	Pixel img[n*n];

	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			img[n*x + y].red = 255;
			img[n*x + y].green = 255;
			img[n*x + y].blue = 255;
		}
	}

	int rows = _board->size()
	int cols = _board->at(0)->size();
	int step_x = n / cols;
	int step_y = n / rows;
	for (int x = 0, y = 0; x < cols && y < rows; x += step_x, y += step_y) {
		drawShape(&(_board[{x, y}]), img, n, x*step_x, y*step_y, (x + 1)*step_x, (y + 1)*step_y);
	}

	imgFile.write(reinterpret_cast<char*>(&img), 3 * n*n);
	imgFile.close();
	return 0;
}

void Board::drawShape(Symbol* symbol, Pixel* img, int img_size, int start_x, int start_y, int end_x, int end_y) {
	switch (symbol->getChar()) {
		case 'X':
			int pixels_per_line = (end_x - start_x) / 10;

			for (int x = start_x, ; x < pixels_per_line; ++x) {
				for (int i = x, int j = start_y; i < end_x && j < end_y; ++i, ++j) {
					img[n*j + i].red = 0;
					img[n*j + i].green = 0;
					img[n*j + i].blue = 0;
				}
			}
			for (int x = end_x - 1, ; x < end_x - 1 - pixels_per_line; ++x) {
				for (int i = x, int j = start_y; i >= start_x && j < end_y; --i, ++j) {
					img[n*j + i].red = 0;
					img[n*j + i].green = 0;
					img[n*j + i].blue = 0;
				}
			}
		case 'O':
			
	}
}