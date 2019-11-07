#include "ListaPaginas.h"
#include <vector>

using namespace std;

ListaPaginas::ListaPaginas(void): primero(0), ultimo(0), nombrePag(""){}

ListaPaginas::ListaPaginas(Nodo* _prim, Nodo* _ult, string _name)
{
	this->primero = _prim;
	this->ultimo = _ult;
	this->nombrePag = _name;
}

void ListaPaginas::agregar(string value)
{
	Nodo* nuevo = new Nodo();
	nuevo->nombre = value;
	bool check = false;
	if (estaVacia())
	{
		primero = nuevo;
		ultimo = nuevo;
		return;
	}
	else
	{
		ultimo->abajo = nuevo;
		ultimo = nuevo;
	}
}

void ListaPaginas::agregarLinks(string value)
{
	NodoRedir* nuevo = new NodoRedir();
	nuevo->nombre = value;
	Nodo* actual = ultimo;
	NodoRedir* actualRedir = 0;

	actualRedir = actual->siguiente;
	if (siguienteVacio())
	{
		actual->siguiente = nuevo;
		return;
	}
	else
	{
		while (actualRedir != 0)
		{
			if (actualRedir->siguiente == 0)
			{
				actualRedir->siguiente = nuevo;
				return;
			}
			actualRedir = actualRedir->siguiente;
		}
	}
	
}

bool ListaPaginas::estaVacia(void)
{
	return primero == nullptr;
}

bool ListaPaginas::siguienteVacio(void)
{
	return ultimo->siguiente == 0;
}

void ListaPaginas::readDIR(string xKeyWord)
{
	DIR* dir;
	struct dirent* cdr;
	string html = "..html";
	ListaPaginas lista;
	if ((dir = opendir("C:\\Users\\aaron\\Desktop\\PageRank")) != NULL) {
		while ((cdr = readdir(dir)) != NULL) {
			if (html.find(cdr->d_name))
			{
				//cout << "\n" << cdr->d_name;
				nombrePag = cdr->d_name;
				vector<string>key = readKeywords();

				for (auto it = key.begin(); it != key.end(); ++it)
				{
					if (*it == xKeyWord)
					{
						agregar(nombrePag);
						readLinks();
					}
				}
			}
		}
		closedir(dir);
	}
	else {
		perror("Error opening Directory!");
		return;
	}
}

void ListaPaginas::readLinks()
{
	ifstream file;
	string path = "C:\\Users\\aaron\\Desktop\\PageRank\\";
	file.open(path + nombrePag);
	while (!file.eof())
	{
		string line, save = "";
		getline(file, line);
		string delimiter = "href=";
		size_t pos = 0;
		std::string token;

		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			cout << endl;
			std::cout << line;
			//delimiter = "\"";

			int count = 0;

			for (int y = 0; y < line.size(); y++)
			{
				if (line.at(y) == '\"')
				{
					y++;

					while (line.at(y) != '\"')
					{
						save = save + line.at(y);
						y++;
					}
					cout << "\n\n" << save;
					agregarLinks(save);
				}
			}
			
		}
		//ff = true;
	}

}

vector<string> ListaPaginas::readKeywords(void)
{
	ifstream file;
	vector<string>extKeywords;
	string path = "C:\\Users\\aaron\\Desktop\\PageRank\\";
	file.open(path + nombrePag);
	while (!file.eof())
	{
		string line, save = "";
		getline(file, line);
		//cout << line << endl;
		string delimiter = "content=";
		string delimiter2 = ", ";
		size_t pos = 0;
		std::string token;
		//ff = false;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			cout << endl;
			std::cout << line;
			//delimiter = "\"";

			int count = 0;

			for (int y = 0; y < line.size(); y++)
			{
				if (line.at(y) == '\"')
				{
					y++;

					while (line.at(y) != '\"')
					{
						save = save + line.at(y);
						y++;
						size_t pos = 0;
						std::string token;
						while ((pos = save.find(delimiter2)) != std::string::npos) {
							token = save.substr(0, pos);
							//std::cout << token << std::endl;
							save.erase(0, pos + delimiter2.length());
							extKeywords.push_back(token);
						}
					}
					extKeywords.push_back(save);
					imprimirKeywords(extKeywords);
					//cout << "\n\n" << save;
					//agregarLinks(save);
				}
			}

		}
	}
	return extKeywords;
}

void ListaPaginas::imprimirLista(void)
{
	Nodo* actual = primero;
	NodoRedir* actualRedir = 0;
	cout << "\n=== PRINT LISTA ===" << endl;

	while (actual != 0)
	{
		cout << actual->nombre << endl;
		actualRedir = actual->siguiente;
		while (actualRedir != 0)
		{
			cout << actualRedir->nombre << endl;
			actualRedir = actualRedir->siguiente;
		}
		actual = actual->abajo;
		cout << "\n";
	}
}

void ListaPaginas::imprimirKeywords(vector<string>& vect)
{
	for (auto it = vect.begin(); it != vect.end(); it++)
	{
		cout << *it << endl;

	}
}

void ListaPaginas::verfiyKeywords(vector<string>& tvect, string xKeyWord)
{
	for (auto it = tvect.begin(); it != tvect.end(); it++)
	{
		if (xKeyWord == *it)
		{
			cout << "iiii";
		}
	}
}

void ListaPaginas::printPr(void)
{
	Nodo* actual = primero;

	while (actual != 0)
	{
		cout << '\n';
		cout << "==== PRINT PAGERANK ====";
		cout << '\n';
		cout << actual->nombre << endl;
		cout << actual->pr;
		actual = actual->abajo;
	}
}

int ListaPaginas::countHrefs(Nodo* inicio)
{
	Nodo* actual = inicio;
	NodoRedir* actualRedir = actual->siguiente;
	int count = 0;

	while (actualRedir != 0)
	{
		count++;
		actualRedir = actualRedir->siguiente;
	}
	return count;
}

void ListaPaginas::prCalculate(void)
{
	Nodo* actual = primero;
	NodoRedir* actualRedir = 0;
	Nodo* actualComp = primero;
	double render = 0;
	double result = 0;
	double prResult = 0;
	

	while (actual != 0)
	{
		for (int i = 0; i < 1000; i++)
		{
			while (actualComp != 0)
			{
				if (countHrefs(actual) == 0)
				{
					prResult = 0.15;
					actualComp->pr = prResult;
					return;
				}
				render = (actualComp->pr / countHrefs(actualComp));
				result += render;
				//prResult += result;
				//actualComp->pr = prResult;
				actualComp = actualComp->abajo;
			}
			prResult += 0.15 + (0.85 * result);
		}
		actual->pr = prResult;
		actual = actual->abajo;
	}
	printPr();
	list<string>nueva = crearListaImportancia();
	printListaImportancia(nueva);
}

list<string> ListaPaginas::crearListaImportancia(void)
{
	list<string>listaImp;
	Nodo* actual = primero;

	while (actual != 0)
	{
		listaImp.push_front(actual->nombre);
		actual = actual->abajo;
	}
	return listaImp;
}

void ListaPaginas::printListaImportancia(list<string>& lista)
{
	cout << '\n';
	cout << "==== PRINT LISTA IMPORTANCIA ====";
	cout << '\n';
	for (auto it = lista.begin(); it != lista.end(); it++)
	{
		cout << *it << endl;
	}
}

int ListaPaginas::getSizeLista(void)
{
	Nodo* actual = primero;
	int amount = 0;

	while (actual != 0)
	{
		amount++;
		actual = actual->abajo;
	}
	return amount;
}
