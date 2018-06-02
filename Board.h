//
// Created by tal on 06/05/18.
//

#ifndef INC_6_BOARD_H
#define INC_6_BOARD_H

#include <vector>
#include <iosfwd>
#include <stdint.h>
#include "Coordinate.hpp"

class Symbol {
private:
    char _val;
public:

    Symbol();
    Symbol(char c);

    char getChar();
    void setChar(char c);

    Symbol& operator= (char c);
    operator char();
};

struct Pixel {
    uint8_t _red, _green, _blue;

public:
    Pixel() {}
    Pixel(uint8_t red, uint8_t green, uint8_t blue) : _red(red), _green(green), _blue(blue) {}
};

using namespace std;

class Board {
private:
    //members
    int _size;
    vector<Symbol>* _board;
    bool isInBound(Coordinate& coordinate) const;
	void delBoard();
public:

    Board();
    Board (int size);
	Board (Board& board);
    ~Board();
    vector<Symbol>* getBoard() const;
	int getSize() const { return _size; }

    friend ostream& operator<< (ostream& out, Board& board) ;
    friend ostream& operator<< (ostream& out, const Board& board);

    friend istream &operator>>( istream  &input, Board& board);

    Board& operator= (char c);
	Board& operator= (Board& board);
    Symbol& operator[] (Coordinate coordinate)const;

	string draw(int n);
	void drawShape(Symbol* symbol, Pixel* img, int img_size, int start_x, int start_y, int end_x, int end_y, int n);
};

#endif //INC_6_BOARD_H
