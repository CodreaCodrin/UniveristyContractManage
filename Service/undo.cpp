#include "undo.h"

ActiuneUndo::~ActiuneUndo()
{
}

UndoAdauga::UndoAdauga(GeneralRepository& repo, const Disciplina& adaugata)
	: repo(repo), adaugata(adaugata){
}

void UndoAdauga::DoUndo()
{
	repo.delete_from_list(adaugata);
}

UndoSterge::UndoSterge(GeneralRepository& repo, const Disciplina& stearsa)
	: repo(repo), stearsa(stearsa){
}

void UndoSterge::DoUndo()
{
	repo.add_to_list(stearsa);
}

UndoModifica::UndoModifica(GeneralRepository& repo, const Disciplina& veche, const Disciplina& noua) 
: repo(repo), veche(veche), noua(noua) {
}

void UndoModifica::DoUndo()
{
	repo.delete_from_list(noua);
	repo.add_to_list(veche);
}
