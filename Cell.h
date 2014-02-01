/*
 * Cell.h
 *
 *  Created on: 09-nov-2013
 *      Author: Samuel Martin
 */

#ifndef CELL_H_
#define CELL_H_

using namespace std;
#include <string>
#include <iostream>
class Cell { // Es una clase abstracta, con metodos virtuales puros
public:
	//Cell(unsigned int filas, unsigned int columnas);
	Cell();
	virtual ~Cell(); // Este destructor es el único virtual ya que tiene clases hijas cuyos objetos deben destruirse

	virtual int getCellValueAsInt()=0; // metodo virtual puro
	virtual double getCellValueAsDouble()=0;  // metodo virtual puro
	virtual string getCellValueAsString()=0;  // metodo virtual puro


};

#endif /* CELL_H_ */
