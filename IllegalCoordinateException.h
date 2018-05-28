//
// Created by tal on 06/05/18.
//

#ifndef INC_6_ILLEGALCOORDINATEEXCEPTION_H
#define INC_6_ILLEGALCOORDINATEEXCEPTION_H

#include <string>
class Coordinate;

class IllegalCoordinateException : public std::exception{
private:
    int _row, _col;

public:
    IllegalCoordinateException(int row, int col);
    std::string theCoordinate() const;
};

#endif //INC_6_ILLEGALCOORDINATEEXCEPTION_H
