//
// Created by tal on 06/05/18.
//

#include "Coordinate.hpp"
#include "IllegalCoordinateException.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

IllegalCoordinateException::IllegalCoordinateException(int row, int col) : _row(row), _col(col) {}

string IllegalCoordinateException::theCoordinate() const {
	return to_string(_row) + ", " + to_string(_col);
}