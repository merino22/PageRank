#include <iostream>
#include <string>
#include <string.h>
#include "ListaPaginas.h"
using namespace std;

int main(int a,const char* b[])
{
	ListaPaginas* obj = new ListaPaginas();
	string as(b[1]);
	obj->run(as);
}