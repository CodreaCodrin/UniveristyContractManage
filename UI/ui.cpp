#include "ui.h"

#include <iostream>

Ui::Ui(Service& controller) noexcept : _controller(controller)
{
}

void Ui::run() const
{
	while (true)
	{
		print_menu();
		char cmd;
		printf(">>");
		cin >> cmd;
		switch (cmd)
		{
		case 'p':
			if(&_controller)
				ui_printall(_controller.GetAll());
			break;
		case '1':
			ui_adaugare();
			break;
		case '2':
			ui_stergere();
			break;
		case '3':
			ui_modificare();
			break;
		case '4':
			ui_cautare();
			break;
		case '5':
			ui_filtrare();
			break;
		case '6':
			ui_sortare();
			break;
		case '7':
			ui_contract();
			break;
		case '8':
			ui_do_undo();
			break;
		case 'e':
			return;
		default:
			printf("Comanda invalida");
			break;
		}
	}
}

bool Ui::CitesteInt(int& n) const
{
	cin >> n;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
	return true;
}

void Ui::print_menu() const noexcept
{
	printf("\np. Afiseaza elementele listei \n");
	printf("1. Adauga in lista \n");
	printf("2. Sterge din lista \n");
	printf("3. Modifica in lista \n");
	printf("4. Cauta disciplina \n");
	printf("5. Filtrare discipline \n");
	printf("6. Sortare discipline \n");
	printf("7. Meniu contract \n");
	printf("8. Undo last action \n");
	printf("e. Exit \n");
}

void Ui::print_contract_menu() const noexcept
{
	printf("\np. Afiseaza elementele contract \n");
	printf("1. Adauga in contract \n");
	printf("2. Sterge contract \n");
	printf("3. Genereaza contract \n");
	printf("4. Exporta contract \n");
	printf("e. Exit \n");
}

void Ui::ui_printall(const vector<Disciplina>& lista) const
{
	for (size_t i = 0; i < lista.size(); i++)
		cout << lista.at(i).to_string() << '\n';
}

void Ui::ui_adaugare() const
{
	string denumire, tip, prof;
	int nrore;
	READ_DISCIPLINA(denumire, nrore, tip, prof);
	try
	{
		_controller.Adauga(denumire, nrore, tip, prof);
	}
	catch (MyException& ex)
	{
		cout <<ex.get_type() << ex.what();
	}
}

void Ui::ui_stergere() const
{
	string denumire, tip, prof;
	int nrore;
	READ_DISCIPLINA(denumire, nrore, tip, prof);
	try
	{
		_controller.Sterge(denumire, nrore, tip, prof);
	}
	catch (MyException& ex)
	{
		cout << ex.get_type() << ex.what();
	}
}

void Ui::ui_modificare() const
{
	string denumire, tip, prof;
	int nrore;
	READ_DISCIPLINA(denumire, nrore, tip, prof);
	string newdenumire, newtip, newprof;
	int newnrore;
	READ_DISCIPLINA(newdenumire, newnrore, newtip, newprof);
	try
	{
		_controller.Modifica(denumire, nrore, tip, prof, newdenumire, newnrore, newtip, newprof);
	}
	catch (MyException& ex)
	{
		cout << ex.get_type() << ex.what();
	}
}

void Ui::ui_cautare() const
{
	string denumire, tip, prof;
	int nrore;
	READ_DISCIPLINA(denumire, nrore, tip, prof);
	if (_controller.Cauta(denumire, nrore, tip, prof))
		printf("Da");
	else
		printf("Nu");
}

void Ui::ui_filtrare() const
{
	char option = 'd';
	int nrore = 0;
	string prof;
	printf("Introoduceti optiunea: ");
	cin >> option;
	switch (option)
	{
	case '1':
		if (!CitesteInt(nrore)) return;
		ui_printall(_controller.filtrare_dupa_ore(nrore));
		break;
	case '2':
		cin >> prof;
		ui_printall(_controller.filtrare_dupa_prof(prof));
		break;
	default:
		printf("Optiune invalida");
		break;
	}
}

void Ui::ui_sortare() const
{
	char option;
	printf("Introoduceti optiunea: ");
	cin >> option;
	switch (option)
	{
	case '1':
		ui_printall(_controller.Sortare(Service::ComparareDupaDenumire));
		break;
	case '2':
		ui_printall(_controller.Sortare(Service::ComparareDupaOre));
		break;
	case '3':
		ui_printall(_controller.Sortare(Service::ComparareDupaTipProf));
		break;
	default:
		printf("Optiune invalida");
		break;
	}
}

void Ui::ui_contract() const
{
	while (true)
	{
		print_contract_menu();
		char cmd;
		printf(">>");
		cin >> cmd;
		switch (cmd)
		{
		case 'p':
			if (&_controller)
				ui_printall(_controller.GetAllContract());
			break;
		case '1':
			ui_adaugare_disciplina_in_contract();
			if (&_controller)
				printf("Sunt %zd elemente in contract la momentul actual",
					_controller.GetAllContract().size());
			break;
		case '2':
			if (&_controller)
				_controller.Curata_contract();
			if (&_controller)
				printf("Sunt %zd elemente in contract la momentul actual",
					_controller.GetAllContract().size());
			break;
		case '3':
			ui_generare_contract();
			if (&_controller)
				printf("Sunt %zd elemente in contract la momentul actual",
					_controller.GetAllContract().size());
			break;
		case '4':
			ui_exporta_contract();
			if (&_controller)
				printf("Sunt %zd elemente in contract la momentul actual",
					_controller.GetAllContract().size());
			break;
		case 'e':
			return;
		default:
			printf("Comanda invalida");
			break;
		}
	}
}

void Ui::ui_adaugare_disciplina_in_contract() const
{
	string denumire;
	printf("Denumire Disciplina: ");
	cin >> denumire;
	try {
		_controller.Adauga_disc_in_contract(denumire);
	}
	catch (MyException& ex)
	{
		cout << ex.get_type() << ex.what();
	}
}

void Ui::ui_generare_contract() const
{
	printf("Nr Discipline: ");
	int nr;
	if (!CitesteInt(nr)) {
		printf("Validator Exeption: Numarul trebuie sa fie nr intreg");
		return;
	}
	const int numar_elemente_adaugate = _controller.Genereaza_contract(nr);
	printf("Au fost adaugate %d elemente", numar_elemente_adaugate);
}

void Ui::ui_exporta_contract() const
{
	printf("Numarul fisierului in care se doreste a exporta: ");
	string expfile;
	cin >> expfile;
	try {
		_controller.Exporta_contract(expfile);
	}
	catch (MyException& ex)
	{
		cout << ex.get_type() << ex.what();
	}
}

void Ui::ui_do_undo() const
{
	const bool status = _controller.Undo();
	switch (status)
	{
	case(true):
		printf("Undo facut cu succes! \n");
		break;
	default:
		printf("Nu se mai poate face undo \n");
		break;
	}
}
