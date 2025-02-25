#include "entity.h"

Disciplina::Disciplina(const string& denumire, int ore, const string& tip, const string& profesor)
{
	_denumire = denumire;
	_ore = ore;
	_tip = tip;
	_profesor = profesor;
}

Disciplina::Disciplina()
{
	_denumire = "";
	_ore = 0;
	_tip = "";
	_profesor = "";
}

const string& Disciplina::get_denumire() const noexcept
{
	return _denumire;
}

int Disciplina::get_ore() const noexcept
{
	return _ore;
}

const string& Disciplina::get_tip() const noexcept
{
	return _tip;
}

const string& Disciplina::get_profesor() const noexcept
{
	return _profesor;
}

void Disciplina::set_denumire(const string& newdenumire)
{
	_denumire = newdenumire;
}

void Disciplina::set_ore(int newore) noexcept
{
	_ore = newore;
}

void Disciplina::set_tip(const string& newtip)
{
	_tip = newtip;
}

void Disciplina::set_profesor(const string& newprofesor)
{
	_profesor = newprofesor;
}

bool Disciplina::operator==(const Disciplina& other) const noexcept
{
	if (_denumire != other._denumire or _ore != other._ore
		or _tip != other._tip or _profesor != other._profesor)
		return false;
	return true;
}

bool Disciplina::operator!=(const Disciplina& other) const noexcept
{
	return !(*this == other);
}

string Disciplina::to_string() const
{
	string txt = "Denumire: " + _denumire + " | NrOre: " + std::to_string(_ore) 
		+ " | Tip: " + _tip + " | Prof: " + _profesor;
	return txt;
}

string Disciplina::to_csv() const
{
	string csv = _denumire + "," + std::to_string(_ore) + "," + _tip + "," + _profesor;
	return csv;
}

Disciplina Disciplina::from_csv(const string& csv)
{
	string denumire, ore, tip, profesor;
	size_t i = 0;
	while (i < csv.size() && csv.at(i) != ',')
	{
		denumire += csv.at(i);
		i++;
	}
	i++;
	while (i < csv.size() && csv.at(i) != ',')
	{
		ore += csv.at(i);
		i++;
	}
	i++;
	while (i < csv.size() && csv.at(i) != ',')
	{
		tip += csv.at(i);
		i++;
	}
	i++;
	while (i < csv.size())
	{
		profesor += csv.at(i);
		i++;
	}

	return Disciplina(denumire, std::stoi(ore), tip, profesor);
}

MyException::MyException(){
	type = "";
	message = "";
}

MyException::MyException(const string& tp, const string& messg){
	type = tp;
	message = messg;
}

string& MyException::get_type() noexcept
{
	return type;
}

string& MyException::what() noexcept
{
	return message;
}

MyException& MyException::operator+=(const string& other)
{
	message += other;
	return *this;
}