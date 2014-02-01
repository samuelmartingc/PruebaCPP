/*
 * IntegerCell.cpp
 *
 *  Created on: 11-nov-2013
 *      Author: Samuel Martin
 */

#include "IntegerCell.h"
#include <string>
#include <sstream>
IntegerCell::IntegerCell(int valor) {
	this->valor = valor;

}

int IntegerCell::getCellValueAsInt(){
	return valor;
}
double IntegerCell::getCellValueAsDouble(){
	return (double) valor;
}
string IntegerCell::getCellValueAsString(){
	stringstream s;
	s << valor;
	return s.str();
}

IntegerCell::~IntegerCell() {
	// TODO Auto-generated destructor stub

}
