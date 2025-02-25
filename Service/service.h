#pragma once

#include "../Repository/dataBase.h"
#include "../Domain/validator.h"
#include "undo.h"

#include <map>
#include <stack>
#include <memory>

using std::map;
using std::stack;
using std::unique_ptr;

class Service {
private:
	GeneralRepository& _repo;
	Contract& _crepo;
private:
	stack<unique_ptr<ActiuneUndo>> _undoLIFO;
public:
	Service(GeneralRepository& repo, Contract& crepo) noexcept;
	/**
	 * @brief adauga o noua disciplina in memorie
	 * @param denumire 
	 * @param ore 
	 * @param tip 
	 * @param profesor 
	 * @throws exceptie daca disciplina este deja in lista, sau daca nu e valida
	 */
	void Adauga(const string& denumire, int ore, const string& tip, const string& profesor);

	/**
	 * @brief sterge o disciplina din memorie
	 * @param denumire 
	 * @param ore 
	 * @param tip 
	 * @param profesor 
	 * @throws exceptie daca disciplina nu deja in lista, sau daca nu e valida
	 */
	void Sterge(const string& denumire, int ore, const string& tip, const string& profesor);

	/**
	 * @brief modifica o disciplina din lista
	 * @param olddenumire 
	 * @param oldore 
	 * @param oldtip 
	 * @param oldprofesor 
	 * @param newdenumire 
	 * @param newore 
	 * @param newtip 
	 * @param newprofesor 
	 * @throws exceptie daca disciplinele nu sunt valide, sau daca nu corespund cu pre: oldentity is in list, newentity is in list
	 */
	void Modifica(const string& olddenumire, int oldore, const string& oldtip, const string& oldprofesor
	, const string& newdenumire, int newore, const string& newtip, const string& newprofesor);
	
	/**
	 * @brief Cauta o disciplina in lista
	 * @param denumire 
	 * @param ore 
	 * @param tip 
	 * @param profesor 
	 * @return true/false
	 */
	bool Cauta(const string& denumire, int ore, const string& tip, const string& profesor) const;

	Disciplina cauta_dupa_nume(const string& denumire);

	/**
	 * @brief returneaza disciplinele stocate in memorie
	 * @return vector
	 */
	const vector<Disciplina>& GetAll() const noexcept;

	/**
	 * @brief returneaza o lista de discipline filtrata dupa ore
	 * @param ore 
	 * @return lista de discipline
	 */
	vector<Disciplina> filtrare_dupa_ore(int ore) const;

	/**
	 * @brief returneaza o lista de discipline filtrata dupa profesor
	 * @param profesor 
	 * @return lista de discipline
	 */
	vector<Disciplina> filtrare_dupa_prof(const string& profesor) const;

	typedef bool (*FunctieComparare)(const Disciplina& disc1, const Disciplina& disc2);

	/**
	 * @brief compara doua discipline dupa denumire
	 * @param disc1 
	 * @param disc2 
	 */
	static bool ComparareDupaDenumire(const Disciplina& disc1, const Disciplina& disc2) noexcept;
	/**
	 * @brief compara doua discipline dupa ora
	 * @param disc1 
	 * @param disc2 	 
	 */
	static bool ComparareDupaOre(const Disciplina& disc1, const Disciplina& disc2) noexcept;
	/**
	 * @brief compara doua discipline dupa tip si profesor
	 * @param disc1 
	 * @param disc2 
	 */
	static bool ComparareDupaTipProf(const Disciplina& disc1, const Disciplina& disc2) noexcept;

	/**
	 * @brief returneaza o lista sortata dupa o functie
	 * @param functieComparare 
	 * @return lista de discipline
	 */
	vector<Disciplina> Sortare(FunctieComparare functieComparare) const;

	void Adauga_disc_in_contract(const string& denumire);
	void Curata_contract() noexcept;
	int Genereaza_contract(int nr);
	const vector<Disciplina>& GetAllContract() const noexcept;
	void Exporta_contract(const string& whatfile) const;

	map<string, int> Creeaza_dictionar() const;

	bool Undo();
};