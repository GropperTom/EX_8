//
// Created by tal on 06/05/18.
//

#include "Coordinate.hpp"

Coordinate::Coordinate(int row, int col)
    :   _col(col), _row(row) {}

Coordinate::Coordinate(const Coordinate &other)
    : _row(other.getRow()), _col(other.getCol()){}

int Coordinate::getCol() const {
    return _col;
}

int Coordinate::getRow() const {
    return _row;
}

bool Coordinate::operator==(const Coordinate& rhs) {
	return getCol() == rhs.getCol() && getRow() == rhs.getRow();
}