#include <iostream>
#include <string>
#include <string.h>
#include "ListaPaginas.h"
using namespace std;

int main()
{
	ListaPaginas* obj = new ListaPaginas();
	string keyword;
	//obj->readKeywords();
	cout << "\nEnter keyword: ";
	cin >> keyword;
	obj->readFile(keyword);
	obj->imprimirLista();
	obj->prCalculate();
}