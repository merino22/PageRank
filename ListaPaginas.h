#ifndef LISTAPAGINAS_H
#define LISTAPAGINAS_H
#include "Nodo.h"
#include <dirent.h>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

class ListaPaginas
{
private:
	Nodo* primero;
	Nodo* ultimo;
	string nombrePag;
public:
	ListaPaginas(void);
	ListaPaginas(Nodo*, Nodo*, string);
	void agregar(string);
	void agregarLinks(string);
	bool estaVacia(void);
	bool siguienteVacio(void);
	void readFile(string);
	void readLinks();
	vector<string> readKeywords(void);
	//array<string, 100>& readKeywords(void);
	void imprimirLista(void);
	void imprimirKeywords(vector<string>&);
	void verfiyKeywords(vector<string>&, string);
	void printPr(void);
	int countHrefs(Nodo*);

	void prCalculate(void);

	list<string> crearListaImportancia(void);
	void printListaImportancia(list<string>&);
	int getSizeLista(void);

};

#endif