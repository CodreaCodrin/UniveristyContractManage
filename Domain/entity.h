#pragma once

#include <string>

using std::string;

class Disciplina {
private:
	string _denumire;
	int _ore;
	string _tip;
	string _profesor;

public:

	/**
	 * @brief Construieste un obiect de tip Disciplina
	 * @param denumire 
	 * @param ore 
	 * @param tip 
	 * @param profesor 
	 */
	Disciplina(const string& denumire, int ore, const string& tip, const string& profesor);

	Disciplina();

	/**
	 * @brief get denumire
	 * @return denumirea
	 */
	const string& get_denumire() const noexcept;

	/**
	 * @brief get NrOre
	 * @return NrOre
	 */
	int get_ore() const noexcept;

	/**
	 * @brief get tip
	 * @return tip
	 */
	const string& get_tip() const noexcept;

	/**
	 * @brief get profesor
	 * @return profesor
	 */
	const string& get_profesor() const noexcept;

	void set_denumire(const string& newdenumire);
	void set_ore(int newore) noexcept;
	void set_tip(const string& newtip);
	void set_profesor(const string& newprofesor);

	bool operator==(const Disciplina& other) const noexcept;
	bool operator!=(const Disciplina& other) const noexcept;
	string to_string() const;

	string to_csv() const;
	static Disciplina from_csv(const string& csv);
};

class MyException {
private:
	string type;
	string message;
public:
	MyException();
	MyException(const string& tp, const string& messg);
	string& get_type() noexcept;
	string& what() noexcept;
	MyException& operator+=(const string& other);
};