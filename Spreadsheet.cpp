/*
 * Spreadsheet.cpp
 *
 *  Created on: 09-nov-2013
 *      Author: Samuel Martin
 */
#include <iostream>
#include <fstream>
#include "Spreadsheet.h"

using namespace std;
// --------------------------------Constructor -----------------------------------------------------
Spreadsheet::Spreadsheet(string nombreFichero) {
	ifstream lectura; //para leer del fichero (se presupone que en la interfaz estará controlado que el fichero existe)
	lectura.open(nombreFichero.c_str()); // no lee string standar, si no c_string
	int aux;
	char cadena[1001];
	lectura.getline(cadena,1000); // primera linea
	string ptrString;
	char *ptr; // para strtok
	char lastChar; /* para comprobar cual es el ultimo caracter de una cadena,
					y tratar las palabras separadas por espacios que empiecen y acaben por comillas (") */
	ptr = strtok( cadena, " " );
	this->filas = atoi(ptr);
	ptr = strtok( NULL, " " );
	this->columnas = atoi(ptr);
	// Una vez he almacenado las filas y columnas, voy a reservar memoria para el contenido e ir rellenando el array
	this->contenido = new Cell**[filas];
	for (unsigned i = 0; i < filas; i++) {
		this->contenido[i] = new Cell*[columnas];
		lectura.getline(cadena,1000); // una vez por linea
		for (unsigned j = 0; j < columnas; j++) {
			ptrString = "";
			if (j==0){ // la primera palabra de la linea necesita que se le introduzca la variable cadena a la funcion strtok
				ptr = strtok( cadena, " " );
				ptrString = ptr;
				if (ptr[0] == '\"'){ // Esto controla si la primera letra es una ",
					// si esto es asi, se siguen extrayendo palabras hasta que en alguna de estas la ultima letra sea "

					lastChar = ptrString.at( ptrString.length() - 1 );
					while ((lastChar != '\"' ) &&(ptr != "")){// se busca una palabra en la que su ultimo caracter sea "
						ptr = strtok( NULL, " " );
						ptrString = ptrString + " " + ptr;
						lastChar = ptrString.at( ptrString.length() - 1 );
					}
				}// fin if del ptr[0]
			} // fin if (j==0)
			else{
				ptr = strtok( NULL, " " );
				ptrString = ptr;
				if (ptr[0] == '\"'){ // análogo a lo que se hace en el if anterior
					lastChar = ptrString.at( ptrString.length() - 1 );
						while ((lastChar != '\"' )&&(ptr != "")){
							ptr = strtok( NULL, " " );
							ptrString = ptrString + " " + ptr;
							lastChar = ptrString.at( ptrString.length() - 1 );
						}
				}// fin if ptr[0]
			}// fin else
			aux = queTipoEs(ptrString); // devuelve un 0 para los enteros, un 1 para los double y un 2 para los string
			switch(aux)	{
				case 0: this->contenido[i][j] = new IntegerCell(atoi(ptr));
				break;
				case 1: this->contenido[i][j] = new FloatingPointCell(atof(ptr));
				break;
				case 2: this->contenido[i][j] = new TextCell(ptrString);
				break;
				default: cout << "error en la creacion de la hoja de calculo" << endl; // no debería darse nunca este caso

				}// fin switch
		}// fin for j
	}// fin for i
	lectura.close(); // cierre del fichero
} // fin del constructor

//------------------------------------Destructor----------------------------------------------------
Spreadsheet::~Spreadsheet() {
	for (unsigned i = 0; i < filas; i++) {
		for (unsigned j = 0; j < columnas; j++) {
			delete contenido[i][j];
		}
		delete contenido[i];
	}
	delete contenido;
	contenido = NULL;
	// si en el futuro quiero hacer una funcion que pregunte si hay algo en el objeto, podre preguntar si es = NULL
	// y asi descarto problemas con valores basura que puedan quedar despues del delete

}// Fin del destructor

// --------------------------------------------------Métodos -----------------------------------------
unsigned int Spreadsheet::getRows()const {
	return filas;
}

unsigned int Spreadsheet::getCols()const {
	return columnas;
}


double Spreadsheet::sumarValoresFila(const unsigned int fila)const{ // devuelve con un double la suma de los valores de una fila
	double contador=0;
	if (fila > (filas - 1)){
		cout << endl << " ha escrito mal la fila" << endl;
	}
	else{
		for (unsigned j = 0; j < columnas; j++) {
			contador += contenido[fila-1][j]->getCellValueAsDouble();
		}// fin for j
	}
	return contador;
}



double Spreadsheet::sumarValoresColumna(const unsigned int columna)const{ // devuelve con un double la suma de los valores de una columna
	double contador=0;
	if (columna > columnas - 1){
		cout << endl << " ha escrito mal la columna" << endl;
	}
	else{
		for (unsigned j = 0; j < filas; j++) {
			contador += contenido[j][columna-1]->getCellValueAsDouble();
		}// fin for j
	}
	return contador;
}


void Spreadsheet::guardarSpreadsheetEnFichero(const string nombreFichero){
	ofstream escritura;
	escritura.open(nombreFichero.c_str(),ios::trunc);
	// si se quiere escribir en un archivo que ya existe se sobreescribe
	escritura << filas << " " << columnas << endl; // para la primera línea

	for (unsigned i = 0; i < filas; i++) {
		for (unsigned j = 0; j < columnas; j++) {
			escritura << contenido[i][j]->getCellValueAsString(); // se escriben todos los campos
			if (j == (columnas-1)){
				escritura << endl; // salto de linea al final de cada linea
			}
			else{
				escritura << " "; // espacio entre las celdas
			}
		}// fin for j
	}// fin for i
	escritura.close();
}// fin guardarSpreadsheetEnFichero


/* Este método funciona independientemente de que el string contenga un entero, un double u otra cosa
 * ya que se comprueba el contenido de la cadena y se convierte al tipo correspondiente su valor.
 * Tambien están implementados otros dos metodos set que leen double e integer, como pide el enunciado de la práctica
 *
 * Los strings que contengan varias palabras separadas por espacio deben escribirse entre comillas para evitar errores
 * Esto estaría implementado en una posible interfaz que utilizara este programa
 */
void Spreadsheet::setCelda(const unsigned int fila,const unsigned int columna,const string valor){
	int aux;
	if (((fila < 1) || (fila > (filas+1)) ) || ((columna < 1) || (columna > (columnas+1)) ) ) {
		cout << "filas o columnas fuera de rango, por favor tenga cuidado" << endl;
	}
	else{
		aux = queTipoEs(valor); // devuelve 0 = Int, 1=Double, 2= string
		switch(aux)	{
		case 0: delete contenido[fila-1][columna-1]; // se borra lo que tuviera la celda anteriormente (por si es de otro tipo)
		this->contenido[fila-1][columna-1] = new IntegerCell(atoi(valor.c_str())); // se añade el nuevo valor
		break;
		case 1: delete contenido[fila-1][columna-1];
		this->contenido[fila-1][columna-1] = new FloatingPointCell(atof(valor.c_str()));
		break;
		case 2: delete contenido[fila-1][columna-1];
		this->contenido[fila-1][columna-1] = new TextCell(valor);
		break;
		default: cout << "error" << endl;
		}
	}//fin else

}// fin funcion set string

void Spreadsheet::setCelda(const unsigned int fila,const unsigned int columna,const double valor){
	if (((fila < 1) || (fila > (filas+1)) ) || ((columna < 1) || (columna > (columnas+1)) ) ) {
		cout << "filas o columnas fuera de rango, por favor tenga cuidado" << endl;
	}
	else{
		delete contenido[fila-1][columna-1];
		this->contenido[fila-1][columna-1] = new FloatingPointCell(valor);
	}//fin else

}// fin funcion set double

void Spreadsheet::setCelda(const unsigned int fila,const unsigned int columna,const int valor){
	if (((fila < 1) || (fila > (filas+1)) ) || ((columna < 1) || (columna > (columnas+1)) ) ) {
		cout << "filas o columnas fuera de rango, por favor tenga cuidado" << endl;
	}
	else{
		delete contenido[fila-1][columna-1];
		this->contenido[fila-1][columna-1] = new IntegerCell(valor);
	}//fin else

}// fin funcion set integer

 int Spreadsheet::queTipoEs(const string valor)const{ // Esta función la he creado para averiguar el tipo del contenido de un string
	 // int = 0;  double = 1;  string = 2
	 const char *p;
	 p=valor.c_str();
	 bool esEntero = true;
	 int i = 0;
	 do { // esta parte del entero es mas larga porque tiene que diferenciar valores como 3.0(double) de otros como 3(int)
	 	if ( (i == 0) && (p[i] == '-') ){ // es negativo?
	 		i++;
	 		esEntero=false; // por si solo el - no es un número
	 	}
	 	else{
	 	// es un digito válido?
	 		if (isdigit(p[i])){
	 			i++;
	 			esEntero = true;
	 		}
	 		else{
	 			i++;
	 			esEntero = false;
	 			break;
	 		}// fin else
	 	}// fin else
	 	} while (p[i] != '\0');
	 if (esEntero) {
		 return 0; // es un entero
	 }

	 if (atof(p) != 0) {
	 	return 1; // es double
	 }
	 return 2; // es string
 }

//------------------------------------Operadores Sobrecargados ----------------------------------------------------

// Operador =
 Spreadsheet& Spreadsheet::operator=(const Spreadsheet & hojaAux) {
	 // libero la memoria de lo que contenía el objeto this
	 for (unsigned i = 0; i < filas; i++) {
	 	for (unsigned j = 0; j < columnas; j++) {
	 		delete contenido[i][j];
	 	}
	 	delete contenido[i];
	 }
	 
	 delete contenido;
	 // Se actualizan los atributos
	 this->columnas = hojaAux.getCols();
	 this->filas = hojaAux.getRows();
	 string contenidoString;
	 const char *contenidoChar;
	 int aux;
	 this->contenido = new Cell**[filas];
	 for (unsigned i = 0; i < filas; i++) {
	 	this->contenido[i] = new Cell*[columnas];
	 	for (unsigned j = 0; j < columnas; j++) {
	 		contenidoString = hojaAux.contenido[i][j]->getCellValueAsString();
	 		contenidoChar = contenidoString.c_str();
	 		aux = queTipoEs(contenidoString); // 0 para int, 1 para double,  2 para string
	 		switch(aux)	{
	 			case 0: this->contenido[i][j] = new IntegerCell(atoi(contenidoChar));
	 			break;
	 			case 1: this->contenido[i][j] = new FloatingPointCell(atof(contenidoChar));
	 			break;
	 			case 2: this->contenido[i][j] = new TextCell(contenidoString);
	 			break;
	 			default: cout << "error en operator = " << endl;
	 		}// fin switch
	 	}// fin del for j
	 }// fin del for i
return *this;
 }// fin del operador =


// Operador ()
 const string Spreadsheet::operator()(unsigned int fila, unsigned int columna) const {
	 if (((fila > filas) || (fila < 1)) || ((columna > columnas) || (columna < 1))) {
		 return "error al introducir los datos";
	 }
	 else
		 return this->contenido[fila-1][columna-1]->getCellValueAsString();
 }

