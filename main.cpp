#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Teste/teste.h"
#include "UI/gui.h"

int main(int argc, char* argv[])
{
	{
		/*Teste tester;
		tester.test_all();*/
	}
	_CrtDumpMemoryLeaks();
	QApplication a(argc, argv);
	InFileRepository Lista("Storage/discipline.csv");
	Contract contract;
	Service controller(Lista, contract);
	Gui* interface = new Gui{ controller };
	interface->show();
	return a.exec();
}