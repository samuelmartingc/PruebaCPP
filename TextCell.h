/*
 * TextCell.h
 *
 *  Created on: 11-nov-2013
 *      Author: Samuel Martin
 */

#ifndef TEXTCELL_H_
#define TEXTCELL_H_
#include "Cell.h"
class TextCell: public Cell {
public:
	TextCell(string valor);

	~TextCell();

	int getCellValueAsInt();
	double getCellValueAsDouble();
	string getCellValueAsString();



private:
	string valor;

};

#endif /* TEXTCELL_H_ */
