#include "service.h"
#include <algorithm>

//random engina
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
//______________________________________________

Service::Service(GeneralRepository& repo, Contract& crepo) noexcept : _repo(repo), _crepo(crepo)
{
}

void Service::Adauga(const string& denumire, int ore, const string& tip, const string& profesor)
{
	Disciplina disc = Disciplina(denumire, ore, tip, profesor);
	Validator::valideaza_disciplina(disc);

	_repo.add_to_list(disc);

	_undoLIFO.push(std::make_unique<UndoAdauga>(_repo, disc));
}

void Service::Sterge(const string& denumire, int ore, const string& tip, const string& profesor)
{
	Disciplina disc = Disciplina(denumire, ore, tip, profesor);
	Validator::valideaza_disciplina(disc);

	_repo.delete_from_list(disc);

	_undoLIFO.push(std::make_unique<UndoSterge>(_repo, disc));
}

void Service::Modifica(const string& olddenumire, int oldore, const string& oldtip, const string& oldprofesor, const string& newdenumire, int newore, const string& newtip, const string& newprofesor)
{
	Disciplina olddisc = Disciplina(olddenumire, oldore, oldtip, oldprofesor);
	Disciplina newdisc = Disciplina(newdenumire, newore, newtip, newprofesor);

	Validator::valideaza_disciplina(olddisc);
	Validator::valideaza_disciplina(newdisc);

	_repo.modify_from_list(olddisc, newdisc);

	_undoLIFO.push(std::make_unique<UndoModifica>(_repo, olddisc, newdisc));
}

bool Service::Cauta(const string& denumire, int ore, const string& tip, const string& profesor) const
{
	Disciplina disc = Disciplina(denumire, ore, tip, profesor);
	Validator::valideaza_disciplina(disc);

	return _repo.is_in_list(disc);
}

Disciplina Service::cauta_dupa_nume(const string& denumire)
{
	return _repo.take_from_list_name_search(denumire);
}

const vector<Disciplina>& Service::GetAll() const noexcept
{
	return _repo.get_all();
}

vector<Disciplina> Service::filtrare_dupa_ore(int ore) const
{
	vector<Disciplina> rezultat;
	vector<Disciplina> list = _repo.get_all();
	for (const auto& obj : list)
	{
		Disciplina disc = obj;
		if (disc.get_ore() == ore)
			rezultat.push_back(disc);
	}
	return rezultat;
}

vector<Disciplina> Service::filtrare_dupa_prof(const string& profesor) const
{
	vector<Disciplina> rezultat;
	vector<Disciplina> list = _repo.get_all();
	for (const auto& obj : list)
	{
		Disciplina disc = obj;
		if (disc.get_profesor() == profesor)
			rezultat.push_back(disc);
	}
	return rezultat;
}

bool Service::ComparareDupaDenumire(const Disciplina& disc1, const Disciplina& disc2) noexcept
{
	if (disc1.get_denumire() <= disc2.get_denumire()) return false;
	return true;
}

bool Service::ComparareDupaOre(const Disciplina& disc1, const Disciplina& disc2) noexcept
{
	if (disc1.get_ore() <= disc2.get_ore()) return false;
	return true;
}

bool Service::ComparareDupaTipProf(const Disciplina& disc1, const Disciplina& disc2) noexcept
{
	if (disc1.get_tip() < disc2.get_tip()) return false;
	else if (disc1.get_tip() == disc2.get_tip() and disc1.get_profesor() <= disc2.get_profesor()) return false;
	return true;
}

vector<Disciplina> Service::Sortare(FunctieComparare functieComparare) const
{
	// Copie
	vector<Disciplina> rezultat = _repo.get_all();
	if(!functieComparare) return rezultat;

	//// Bubble sort
	//bool sortat = false;
	//while (!sortat)
	//{
	//	sortat = true;
	//	for (int i = 0; i < rezultat.size() - 1; i++)
	//	{
	//		if (functieComparare(rezultat.at(i), rezultat.at(i+1)))
	//		{
	//			sortat = false;

	//			Disciplina aux = rezultat.at(i);
	//			rezultat.at(i) = rezultat.at(i+1);
	//			rezultat.at(i+1) = aux;
	//		}
	//	}
	//}

	//stl sort
	sort(rezultat.begin(), rezultat.end(),
		[&](const Disciplina& disc1, const Disciplina& disc2) noexcept 
		{ return functieComparare(disc2, disc1); });

	return rezultat;
}

void Service::Adauga_disc_in_contract(const string& denumire)
{
	_crepo.add_to_list(_repo.take_from_list_name_search(denumire));
}

void Service::Curata_contract() noexcept
{
	_crepo.clear_contract();
}

int Service::Genereaza_contract(int nr)
{
	Curata_contract();
	vector<Disciplina> list = _repo.get_all();
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(list.begin(), list.end(), std::default_random_engine(static_cast<int>(seed)));

	int i;
	for (i = 0; i < nr and i < list.size(); i++)
		_crepo.add_to_list(list.at(i));
	return i;
}

const vector<Disciplina>& Service::GetAllContract() const noexcept
{
	return _crepo.get_all();
}

void Service::Exporta_contract(const string& whatfile) const
{
	RepoToFile exportator(whatfile);
	exportator.Export(_crepo.get_all());
}

map<string, int> Service::Creeaza_dictionar() const
{
	map<string, int> MyMap;
	vector<Disciplina> list_of_obj = Sortare(Service::ComparareDupaTipProf);
	string prec;
	int nr = 1;
	if (list_of_obj.size() > 0) {
		prec = list_of_obj.at(0).get_tip();
		nr = 1; } else return MyMap;

	string last_added_key;
	vector<Disciplina>::const_iterator it = list_of_obj.begin();
	it++;
	for (it; it != list_of_obj.end(); it++)
	{
		if ((*it).get_tip() == prec) nr++;
		else {
			MyMap.emplace(std::make_pair(prec, nr));
			last_added_key = prec;
			nr = 1;
		}
		prec = (*it).get_tip();
	}

	if (prec == last_added_key) { nr++; MyMap.emplace(std::make_pair(prec, nr)); }
	else
		MyMap.emplace(std::make_pair(prec, nr));

	return MyMap;
}

bool Service::Undo()
{
	if(_undoLIFO.empty()) return false;

	_undoLIFO.top()->DoUndo();
	_undoLIFO.pop();

	return true;
}
