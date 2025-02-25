#include "validator.h"

#include <exception>
using std::exception;

void Validator::valideaza_disciplina(const Disciplina& disc)
{
	MyException errorlist("Validator exeption: ", "");
	if (disc.get_denumire() == "")
		errorlist += "Denumire invalida; ";
	if (disc.get_ore() < 0)
		errorlist += "NrOre invalid; ";
	if (disc.get_tip() == "")
		errorlist += "Tip invalid; ";
	if (disc.get_profesor() == "")
		errorlist += "Profesor invalid; ";
	if (errorlist.what() != "")
		throw errorlist;
}
