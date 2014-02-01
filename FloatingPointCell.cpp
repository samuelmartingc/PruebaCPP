/*
 * FloatingPointCell.cpp
 *
 *  Created on: 11-nov-2013
 *      Author: Samuel Martin
 */

#include "FloatingPointCell.h"
#include <string>
#include <sstream>
#include <iostream>
FloatingPointCell::FloatingPointCell(double valor) {
	this->valor=valor;

}

FloatingPointCell::~FloatingPointCell() {
	// TODO Auto-generated destructor stub

}


int FloatingPointCell::getCellValueAsInt(){
	return (int)valor;
}
double FloatingPointCell::getCellValueAsDouble(){
	return valor;
}
string FloatingPointCell::getCellValueAsString(){
	stringstream s;
	s << valor;
	// esta parte sirve para que un double como 5.0 no pierda el .0 en el archivo de salida y parezca un int
	const char *s1 = s.str().c_str();
	char *resp;
	resp = strstr(s1,".");
	if (resp == NULL){
		s << ".0";
	}
	return s.str();
}


