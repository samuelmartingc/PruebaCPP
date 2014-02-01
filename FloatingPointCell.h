/*
 * FloatingPointCell.h
 *
 *  Created on: 11-nov-2013
 *      Author: Samuel Martin
 */

#ifndef FLOATINGPOINTCELL_H_
#define FLOATINGPOINTCELL_H_
#include "Cell.h"

class FloatingPointCell: public Cell {
public:
	FloatingPointCell(double valor);
	~FloatingPointCell();

	int getCellValueAsInt();
	double getCellValueAsDouble();
	string getCellValueAsString();


private:
	double valor;
};

#endif /* FLOATINGPOINTCELL_H_ */
