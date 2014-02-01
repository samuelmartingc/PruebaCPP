/*
 * TextCell.cpp
 *
 *  Created on: 11-nov-2013
 *      Author: Samuel Martin
 */

#include "TextCell.h"

TextCell::TextCell(string valor) {
	this->valor=valor;
}

TextCell::~TextCell() {
	// TODO Auto-generated destructor stub

}

int TextCell::getCellValueAsInt(){
	return 0;
}
double TextCell::getCellValueAsDouble(){
	return 0.0;
}
string TextCell::getCellValueAsString(){
	return valor;
}


