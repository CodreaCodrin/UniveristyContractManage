#include "dataBase.h"

using std::exception;

#include <random>

void InMemoryRepository::add_to_list(const Disciplina& entity)
{
	if (is_in_list(entity))
		throw MyException("Repo Exeption: ", "entity already in list");
	_v.push_back(entity);
}

bool InMemoryRepository::is_in_list(const Disciplina& entity) const noexcept
{
	for (const auto& obj : _v)
		if (entity == obj)
			return true;
	return false;
}

Disciplina InMemoryRepository::take_from_list_name_search(const string& denumire) const
{
	for (const auto& obj : _v)
		if (denumire == obj.get_denumire())
			return obj;
	throw MyException("Repo Exeption: ", "entity not in list");
}

void InMemoryRepository::delete_from_list(const Disciplina& entity)
{
	if (!is_in_list(entity))
		throw MyException("Repo Exeption: ", "entity not in list");
	_v.erase(std::find(_v.begin(), _v.end(), entity));
}

void InMemoryRepository::modify_from_list(const Disciplina& oldentity, const Disciplina& newentity)
{
	if(oldentity == newentity)
		throw MyException("Repo Exeption: ", "entity not modified");
	delete_from_list(oldentity);
	add_to_list(newentity);
}

size_t InMemoryRepository::size_of_list() const noexcept
{
	return _v.size();
}

const vector<Disciplina>& InMemoryRepository::get_all() const noexcept
{
	return _v;
}

void Contract::clear_contract() noexcept
{
	_v.clear();
}

InFileRepository::InFileRepository(const string& filePath) : filePath {filePath}
{
	ReadFromFile();
}

void InFileRepository::add_to_list(const Disciplina& entity)
{
	InMemoryRepository::add_to_list(entity);
	WriteToFile();
}

void InFileRepository::delete_from_list(const Disciplina& entity)
{
	InMemoryRepository::delete_from_list(entity);
	WriteToFile();
}

void InFileRepository::modify_from_list(const Disciplina& oldentity, const Disciplina& newentity)
{
	InMemoryRepository::modify_from_list(oldentity, newentity);
	WriteToFile();
}

void InFileRepository::ReadFromFile()
{
	std::ifstream file(filePath);
	if (file.fail()) return;

	std::string line;
	while (std::getline(file, line))
		InMemoryRepository::add_to_list(Disciplina::from_csv(line));

	file.close();
}

void InFileRepository::WriteToFile() const
{
	std::ofstream file(filePath);

	for (const auto& a : _v)
		file << a.to_csv() << '\n';

	file.close();
}

//____________________________new dict_______________________________

void DictRepository::check_prob() const
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 100); // define the range
	const int randomnumber = distr(gen);

	if(randomnumber < int(p*100)) throw MyException("Repo Exeption: ", "Nu s-a putu efectua din cauza probabilitatii");
}

DictRepository::DictRepository(float prob) : p{prob}
{
}

void DictRepository::add_to_list(const Disciplina& entity)
{
	check_prob();
	if(is_in_list(entity))
		throw MyException("Repo Exeption: ", "entity already in list");
	_v.emplace(std::make_pair(entity.get_denumire(), entity));
}

bool DictRepository::is_in_list(const Disciplina& entity) const noexcept
{
	for (const auto& elem : _v)
		if (elem.second == entity)
			return true;
	return false;
}

Disciplina DictRepository::take_from_list_name_search(const string& denumire) const
{
	check_prob();
	for (const auto& elem : _v)
		if (denumire == elem.first)
			return elem.second;
	throw MyException("Repo Exeption: ", "entity not in list");
}

void DictRepository::delete_from_list(const Disciplina& entity)
{
	check_prob();
	if (!is_in_list(entity))
		throw MyException("Repo Exeption: ", "entity not in list");
	auto it = _v.begin();
	for (it; it != _v.end() && it->second != entity; it++);
	_v.erase(it);
}

void DictRepository::modify_from_list(const Disciplina& oldentity, const Disciplina& newentity)
{
	check_prob();
	delete_from_list(oldentity);
	add_to_list(newentity);
}

size_t DictRepository::size_of_list() const noexcept
{
	check_prob();
	return _v.size();
}

const vector<Disciplina>& DictRepository::get_all() const noexcept
{
	check_prob();
	vector<Disciplina> *v = new vector<Disciplina>;
	for (const auto& elem : _v)
		v->push_back(elem.second);
	return *v;
}
