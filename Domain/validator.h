#pragma once

#include "entity.h"

class Validator {
public:
	/**
	 * @brief Valideaza o disciplina si arunca erori in caz este invalida
	 * @param disc 
	 * @throws Denumire invalida
	 * @throws NrOre invalide
	 * @throws tip invalid
	 * @throws profesor invalid
	 */
	static void valideaza_disciplina(const Disciplina& disc);
};