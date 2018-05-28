//
// Created by tal on 06/05/18.
//

#ifndef INC_6_BOARD_H
#define INC_6_BOARD_H

#include <vector>
#include <iosfwd>
#include "Coordinate.hpp"

class Pixel;

using namespace std;

class Board {
private:
    //members
    class Symbol {
    private:
        char _val;
    public:
        char getChar();

        Symbol(char c);

        Symbol& operator= (char c);
        operator char();
    };

    int _size;
    vector<vector<Symbol>*>* _board;
    bool isInBound(Coordinate& coordinate) const;
	void delBoard();
public:

    Board (int size);
	Board (Board& board);
    ~Board();
    vector<vector<Symbol>*>* getBoard() const;
	int getSize() const { return _size; }

    friend ostream& operator<< (ostream& out, Board& board) ;
    friend ostream& operator<< (ostream& out, const Board& board);
    Board& operator= (char c);
	Board& operator= (Board& board);
    Symbol& operator[] (Coordinate coordinate)const;

	string draw(int n);
	void drawShape(Symbol* symbol, Pixel* img, int img_size, int start_x, int start_y, int end_x, int end_y);
};

#endif //INC_6_BOARD_H
