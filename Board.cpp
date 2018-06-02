//
// Created by tal on 06/05/18.
//

#include <string>
#include <iostream>
#include <fstream>
#include "Board.h"
#include "Coordinate.hpp"
#include "IllegalCoordinateException.h"
#include "IllegalCharException.h"

Board::Board(int size)
        : _size(size), _board(new vector<Symbol>(size * size)){
}

Board::Board()
        : _size(0), _board(new vector<Symbol>(0)){}

Board::Board(Board& board)
    : _board(new vector<Symbol>(board.getSize() * board.getSize())), _size(board.getSize()){
	//copy symbols
	for (int row = 0; row < _size; ++row) {
		for (int col = 0; col < _size; ++col) {
			char charToCopy = board[{row,col}].getChar();
			_board->at(row*_size+col).setChar(charToCopy);
		}
	}
}

Board::~Board() {
	delete _board;
}

vector<Symbol>* Board::getBoard() const {
    return _board;
}

ostream& operator<<(ostream &out, Board &board){
    string ans = "";

	for (int row = 0; row < board.getSize(); ++row) {
		for (int col = 0; col < board.getSize(); ++col) {
			out << board[{row,col}].getChar();
		}
	}
    return out;
}

ostream& operator<<(ostream &out, const Board &board){
    string ans = "";

	for (int row = 0; row < board.getSize(); ++row) {
		for (int col = 0; col < board.getSize(); ++col) {
			out << board[{row,col}].getChar();
		}
	}
    return out;
}

istream &operator>>( istream  &input, Board &board ) {
    int size = 0;
    //delete all existing symbols
    while (!(board.getBoard()->empty())){
        board.getBoard()->pop_back();
    }
    //copy all symbols
    string line;
    while (input >> line){
        size++;
        for (char& symbol : line){
            board.getBoard()->push_back(symbol);
        }
    }

    //update size
    board._size = size;
    //finish
    return input;
}

Board& Board::operator=(char symbol) {

	for (int row = 0; row < _size; ++row) {
		for (int col = 0; col < _size; ++col) {
			(*this)[{row,col}] = symbol;
		}
	}

    return *this;
}

Board& Board::operator=(Board& board) {
	delete _board;
	_board = new vector<Symbol>(board.getSize()*board.getSize());
	_size = board.getSize();

	for (int row = 0; row < _size; ++row) {
		for (int col = 0; col < _size; ++col) {
			Symbol symbolToCopy = Symbol(board[{row,col}]);
			_board->push_back(symbolToCopy);
		}
	}

	return *this;
}

Symbol& Board::operator[] (Coordinate coordinate) const{
    if (!isInBound(coordinate)){
        throw IllegalCoordinateException(coordinate.getRow(), coordinate.getCol());
    }
	else {
    	return _board->at(coordinate.getRow()*_size+coordinate.getCol());
	}
}

bool Board::isInBound(Coordinate& coordinate) const{
	int desiredIndex = coordinate.getRow()*_size+coordinate.getCol();
    if (desiredIndex <= getSize()*getSize() && coordinate.getRow()*coordinate.getCol() >= 0){
        return true;
    }
    return false;
}

Symbol::Symbol()
    : _val('.'){}

Symbol::Symbol(char c)
    : _val(c){}

char Symbol::getChar() {
	return _val;
}

void Symbol::setChar(char c) {
    _val = c;
}

Symbol & Symbol::operator=(char c) {
	if (c != 'X' && c != 'O' && c != '.') throw IllegalCharException(c + "");
	else _val = c;
	return *this;
}

//Board::operator char() {
//	return _val;
//}

string Board::draw(int n) {
	ofstream imgFile("cpp.ppm", ios::out | ios::binary);
	imgFile << "P6" << endl << n << " " << n << endl << 255 << endl;

	Pixel img[n*n];

	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			img[n*x + y]._red = 255;
			img[n*x + y]._green = 255;
			img[n*x + y]._blue = 255;
		}
	}

	int rows, cols;
	rows = cols = _size;
	int step_x = n / cols;
	int step_y = n / rows;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			drawShape(&((*this)[{row,col}]), img, n, row*step_x, col*step_y, (row + 1)*step_x, (col + 1)*step_y, n);
		}
	}

    for (int row = 1; row < cols; ++row) {
        for (int col = 1; col < rows; ++col) {
            drawShape(&((*this)[{row,col}]), img, n, row*step_x, col*step_y, (row + 1)*step_x, (col + 1)*step_y, n);
        }
    }

	imgFile.write(reinterpret_cast<char*>(&img), 3 * n*n);
	imgFile.close();
	return "cpp.ppm";
}

void Board::drawShape(Symbol* symbol, Pixel img[], int img_size, int start_x, int start_y, int end_x, int end_y, int n) {
	int x_pixels_amnt = end_x - start_x;
	int y_pixels_amnt = end_y - start_y;
	int pixels = (end_x - start_x) * 0.1;

	switch (symbol->getChar()) {
		case 'X':
			for (int x = start_x; x < start_x+pixels; ++x) {
				for (int i = x, j = start_y; i < end_x && j < end_y; ++i, ++j) {
					img[n*j + i]._red = 0;
					img[n*j + i]._green = 0;
					img[n*j + i]._blue = 0;
				}
			}
			for (int x = end_x - 1 ; x >= end_x - 1 - pixels; --x) {
				for (int i = x, j = start_y; i >= start_x && j < end_y; --i, ++j) {
					img[n*j + i]._red = 0;
					img[n*j + i]._green = 0;
					img[n*j + i]._blue = 0;
				}
			}
			break;
		case 'O':
			for (int x = start_x + (x_pixels_amnt * 0.1); x < start_x + (x_pixels_amnt * 0.9); ++x) {
				for (int y = start_y + (y_pixels_amnt * 0.1); y < start_y + (y_pixels_amnt * 0.9); ++y) {
					img[n*y + x]._red = 0;
					img[n*y + x]._green = 0;
					img[n*y + x]._blue = 0;
				}
			}

			for (int x = start_x + (x_pixels_amnt * 0.2); x < start_x + (x_pixels_amnt * 0.8); ++x) {
				for (int y = start_y + (y_pixels_amnt * 0.2); y < start_y + (y_pixels_amnt * 0.8); ++y) {
					img[n*y + x]._red = 255;
					img[n*y + x]._green = 255;
					img[n*y + x]._blue = 255;
				}
			}
			break;
		case '.':
			for (int x = start_x; x < start_x + (x_pixels_amnt * 0.2); ++x) {
				for (int y = start_y + (y_pixels_amnt * 0.8); y < end_y; ++y) {
					img[n*y + x]._red = 0;
					img[n*y + x]._green = 0;
					img[n*y + x]._blue = 0;
				}
			}
			break;
	}

    for (int x = start_x; x < end_x; ++x) {
        //top
	    for (int y = start_y; y < start_y + 3; ++y) {
            img[n*y + x]._red = 100;
            img[n*y + x]._green = 100;
            img[n*y + x]._blue = 100;
        }
        //bottom
        for (int y = end_y - 3; y < end_y; ++y) {
            img[n*y + x]._red = 100;
            img[n*y + x]._green = 100;
            img[n*y + x]._blue = 100;
        }
    }

    for (int y = start_y; y < end_y; ++y) {
        //left
        for (int x = start_x; x < start_x + 3; ++x) {
            img[n*y + x]._red = 100;
            img[n*y + x]._green = 100;
            img[n*y + x]._blue = 100;
        }
        //right
        for (int x = end_x - 3; x < end_x; ++x) {
            img[n*y + x]._red = 100;
            img[n*y + x]._green = 100;
            img[n*y + x]._blue = 100;
        }
    }

}
