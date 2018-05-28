//
// Created by tal on 06/05/18.
//

#include "IllegalCharException.h"
using namespace std;

IllegalCharException::IllegalCharException(string badChar)
	: _badChar(badChar) {}

string IllegalCharException::theChar() const{
	return _badChar;
}