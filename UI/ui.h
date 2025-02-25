#pragma once

#include "../Service/service.h"

using namespace std;

#define READ_DISCIPLINA(denumire, nrore, tip, prof) \
	printf("Denumire: "); \
	cin>>denumire; \
	printf("NrOre: "); \
	if(!CitesteInt(nrore)){ \
	printf("Validator Exeption: Numara de ore trebuie sa fie nr intreg"); \
	return; }\
	printf("Tip: "); \
	cin>>tip; \
	printf("Profesor: "); \
	cin>>prof; \

class Ui {
public:
	Ui(Service& controller) noexcept;
	void run() const;
private:
	Service& _controller;
	bool CitesteInt(int& n) const;
	void print_menu() const noexcept;
	void print_contract_menu() const noexcept;
	void ui_printall(const vector<Disciplina>& lista) const;
	void ui_adaugare() const;
	void ui_stergere() const;
	void ui_modificare() const;
	void ui_cautare() const;
	void ui_filtrare() const;
	void ui_sortare() const;
	void ui_contract() const;
	void ui_adaugare_disciplina_in_contract() const;
	void ui_generare_contract() const;
	void ui_exporta_contract() const;
	void ui_do_undo() const;
};