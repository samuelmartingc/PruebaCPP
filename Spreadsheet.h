/*
 * Spreadsheet.h
 *
 *  Created on: 09-nov-2013
 *      Author: Samuel Martin
 */

#ifndef SPREADSHEET_H_
#define SPREADSHEET_H_
#include <string>
#include "Cell.h"
#include "IntegerCell.h"
#include "FloatingPointCell.h"
#include "TextCell.h"
#include <sstream>
using namespace std;
class Spreadsheet {
public:
	Spreadsheet(string nombreFichero); // Al crearse el objeto se cargan los datos desde un fichero
	~Spreadsheet(); // destructor
	unsigned int getRows()const;
	unsigned int getCols()const;
	double sumarValoresFila(const unsigned int fila)const;
	double sumarValoresColumna(const unsigned int columna)const;
	void guardarSpreadsheetEnFichero(const string nombreFichero);
	void setCelda(const unsigned int fila,const unsigned int columna,const string valor);
	//se le puede pasar cualquier tipo de dato como string y lo transforma en lo que sea necesario.
	void setCelda(const unsigned int fila,const unsigned int columna,const double valor);
	void setCelda(const unsigned int fila,const unsigned int columna,const int valor);
	Spreadsheet& operator=(const Spreadsheet & hojaAux);
	const string operator()(unsigned int fila, unsigned int columna) const;






private:
	int queTipoEs(const string valor)const; // int = 0;  double = 1;  string = 2
	unsigned int filas,columnas;

protected:
	Cell ***contenido;
	// se encuentra en protected para poder implementar el operator= sin usar el operator() por si se quiere modificar el () en el futuro
	// si no, podría ser private y se llamaria al otro spreadsheet con el operador ()

};// fin clase
#endif /* SPREADSHEET_H_ */
