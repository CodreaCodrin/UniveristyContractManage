#pragma once

#include "../Domain/entity.h"
#include <exception>
#include <vector>
#include <fstream>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class GeneralRepository {
public:
	/**
	 * @brief adauga o entitate in lista
	 * @param entity
	 * @throws "entity already in list" daca entitatea este deja prezenta in lista
	 */
	virtual void add_to_list(const Disciplina& entity) = 0;

	/**
	 * @brief verifica daca entitatea se afla in lista
	 * @param entity
	 * @return true/false
	 */
	virtual bool is_in_list(const Disciplina& entity) const noexcept = 0;

	/**
	 * @brief verifica daca entitatea se afla in lista
	 * @param denuimire
	 * @return disciplina
	 */
	virtual Disciplina take_from_list_name_search(const string& denumire) const = 0;

	/**
	 * @brief sterge o entitate din lista
	 * @param entity
	 * @throws "entity not in list" daca entitatea nu este in lista
	 */
	virtual void delete_from_list(const Disciplina& entity) = 0;

	/**
	 * @brief modifica o entitate din lista
	 * @param oldentity
	 * @param newentity
	 * @throws "entity not in list" sau "entity already in list"
	 */
	virtual void modify_from_list(const Disciplina& oldentity, const Disciplina& newentity) = 0;

	/**
	 * @return nr de etitati stocate
	 */
	virtual size_t size_of_list() const noexcept = 0;

	/**
	 * @brief returneaza vectorul
	 * @return the vector
	 */
	virtual const vector<Disciplina>& get_all() const noexcept = 0;
};

class InMemoryRepository : public GeneralRepository {
protected:
	vector<Disciplina> _v;
public:

	void add_to_list(const Disciplina& entity) override;
	bool is_in_list(const Disciplina& entity) const noexcept override;
	Disciplina take_from_list_name_search(const string& denumire) const override;
	void delete_from_list(const Disciplina& entity) override;
	void modify_from_list(const Disciplina& oldentity, const Disciplina& newentity) override;
	size_t size_of_list() const noexcept override;
	const vector<Disciplina>& get_all() const noexcept override;
};

class Contract : public InMemoryRepository {
public:
	void clear_contract() noexcept;
};

class RepoToFile {
private:
	void OpenFile() {
		std::ifstream in(file);
		if (!in.good())
			throw MyException("Repo Exeption: ", "Error file is invalid or nonexistent");
		in.close();
		std::ofstream out(file);
		out << "\0";
		out.close();
	}
	string file;
public:
	RepoToFile(string file) : file{ file } {
		OpenFile();
	};
	void set_file(string new_file) {
		file = new_file;
		OpenFile();
	}
	void Export(const vector<Disciplina>& vec) {
		std::ofstream out(file);
		for (const auto& d : vec) {
			out << d.get_denumire() << ", " << d.get_ore() << ", " << d.get_tip() << ", " << d.get_profesor() << std::endl;
		}
		out.close();
	}
};

class InFileRepository : public InMemoryRepository {
private:
	string filePath;
public:
	InFileRepository(const string& filePath);

	void add_to_list(const Disciplina& entity) override;
	void delete_from_list(const Disciplina& entity) override;
	void modify_from_list(const Disciplina& oldentity, const Disciplina& newentity) override;
private:
	void ReadFromFile();
	void WriteToFile() const;
};

class DictRepository : public GeneralRepository {
private:
	unordered_map<string, Disciplina> _v;
	float p;

	void check_prob() const;
public:
	DictRepository(float prob);
	
	void add_to_list(const Disciplina& entity) override;
	bool is_in_list(const Disciplina& entity) const noexcept override;
	Disciplina take_from_list_name_search(const string& denumire) const override;
	void delete_from_list(const Disciplina& entity) override;
	void modify_from_list(const Disciplina& oldentity, const Disciplina& newentity) override;
	size_t size_of_list() const noexcept override;
	const vector<Disciplina>& get_all() const noexcept override;
};