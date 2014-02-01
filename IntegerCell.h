/*
 * IntegerCell.h
 *
 *  Created on: 11-nov-2013
 *      Author: Samuel Martin
 */

#ifndef INTEGERCELL_H_
#define INTEGERCELL_H_

#include "Cell.h"
class IntegerCell: public Cell {
public:
	IntegerCell(int valor);
	~IntegerCell();

	int getCellValueAsInt();
	double getCellValueAsDouble();
	string getCellValueAsString();


private:
	int valor;
};

#endif /* INTEGERCELL_H_ */
