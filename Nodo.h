#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include "NodoRedir.h"

using namespace std;

struct Nodo
{
	string nombre;
	double pr;
	Nodo* abajo;
	NodoRedir* siguiente;

	Nodo()
	{
		nombre = "";
		pr = 1;
		abajo = 0;
		siguiente = 0;
	}
};

#endif