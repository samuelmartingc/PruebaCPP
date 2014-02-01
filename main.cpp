/*
 * main.cpp
 *
 *  Created on: 07-nov-2013
 *      Author: Samuel Martín
 */
using namespace std;
#include <iostream>
#include <fstream>
#include "Spreadsheet.h"
int main (void){

string fichero1 = "HojaCalculo1.csv";
string fichero2= "HojaCalculo2.csv";


	// Un menu para comprobar la funcionalidad de la práctica
	// En lugar de implementar el método que cargue los datos del fichero
	// he optado por cargarlos en el constructor, pasándole el nombre de archivo que abrirá
	Spreadsheet hojaCalculo(fichero1);
	Spreadsheet hojaCalculo2(fichero2);


	// Uso del operador sobrecargado ()
	cout << " El operador de consulta sobrecargado () devuelve como string " << endl;
	cout << "el valor que contiene la celda (i,j) numeradas desde 1 hasta n" << endl;
	cout << hojaCalculo2(4,1) << " ";
	cout << hojaCalculo2(4,2) << " ";
	cout << hojaCalculo2(4,3) << " " << endl;
	cout << " Estan controlados los valores que salen de rango -> " <<  hojaCalculo2(4,4) << " " << endl;

	// Uso del método set, admite strings y luego los convierte a el tipo necesario para el polimorfismo
	cout << "El set va modificando una misma celda, se le puede llamar de diferentes modos : ";
	hojaCalculo.setCelda(1,1,3);
	cout << hojaCalculo(1,1) << " -> ";
	hojaCalculo.setCelda(1,1,5.6);
	cout << hojaCalculo(1,1) << " -> ";

	hojaCalculo.setCelda(1,1,"3");
	cout << hojaCalculo(1,1) << " -> ";
	hojaCalculo.setCelda(1,1,"5.6");
	cout << hojaCalculo(1,1) << " -> ";
	hojaCalculo.setCelda(1,1,"C++");
	cout << hojaCalculo(1,1) << endl;


	// Contiene la informacion introducida en hojaCalculo
	hojaCalculo.guardarSpreadsheetEnFichero("H1ficheroSalidaGuardado.csv");



	// Uso del operador sobrecargado =
	cout << "Antes : " << hojaCalculo(1,1) << endl;
	hojaCalculo = hojaCalculo2;
	cout << "Despues : " << hojaCalculo(1,1) << endl;

	//Contiene la informacion introducida en hojaCalculo (que ahora es igual a la de hojaCalculo2)
	hojaCalculo.guardarSpreadsheetEnFichero("H2ficheroSalidaGuardado.csv");

	//sumarValoresFila y sumarValoresColumna
	cout << endl << "los la suma de la columna 1 es : " << hojaCalculo.sumarValoresColumna(1);
	cout << endl << "los la suma de la fila 1 es : " << hojaCalculo.sumarValoresFila(1);
	return 0;
}
