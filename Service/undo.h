#pragma once

#include "../Repository/dataBase.h"

class ActiuneUndo
{
public:
	/**
	 * @brief Face undo la ultima actiune de tip adauga, sterge sau modifica
	 */
	virtual void DoUndo() = 0;

	virtual ~ActiuneUndo();
};

class UndoAdauga : public ActiuneUndo
{
public:
	UndoAdauga(GeneralRepository& repo, const Disciplina& adaugata);
	void DoUndo() override;

private:
	GeneralRepository& repo;
	Disciplina adaugata;
};

class UndoSterge : public ActiuneUndo
{
public:
	UndoSterge(GeneralRepository& repo, const Disciplina& stearsa);
	void DoUndo() override;

private:
	GeneralRepository& repo;
	Disciplina stearsa;
};

class UndoModifica : public ActiuneUndo
{
public:
	UndoModifica(GeneralRepository& repo, const Disciplina& veche, const Disciplina& noua);
	void DoUndo() override;

private:
	GeneralRepository& repo;
	Disciplina veche;
	Disciplina noua;
};