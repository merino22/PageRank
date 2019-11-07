#ifndef NODOREDIR_H
#define NODOREDIR_H

#include <string>

using namespace std;

struct NodoRedir
{
	string nombre;
	NodoRedir* siguiente;

	NodoRedir()
	{
		nombre = "";
		siguiente = 0;
	}
};

#endif
