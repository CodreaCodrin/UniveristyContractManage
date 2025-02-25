#include "teste.h"
#include <iostream>

void Teste::test_all()
{
	//Run all tests
	//Domain
	test_entity();
	test_validator_of_entity();
	//Repo
 	test_mylist();
	//Service
	test_Adauga();
	test_Sterge();
	test_Modifica();
	test_undo();
	test_filtare_ore();
	test_filtare_prof();
	test_sortare();
	//MyVector
	//test_vector();
	//Contract
	test_contract();
	test_add_contract();
	test_dictionar();
	test_repo_dictionar();
}

void Teste::test_entity()
{
	Disciplina gd_disc = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina other_gd_disc = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina bd_disc = Disciplina("", -1, "", "");
	Disciplina empty = Disciplina();

	assert(gd_disc == other_gd_disc);
	assert(bd_disc != other_gd_disc);

	assert(gd_disc.get_denumire() == "ASC");
	assert(gd_disc.get_ore() == 5);
	assert(gd_disc.get_tip() == "Info");
	assert(gd_disc.get_profesor() == "Vancea");

	gd_disc.set_denumire("Analiza");
	gd_disc.set_ore(4);
	gd_disc.set_tip("Mate");
	gd_disc.set_profesor("Berinde");

	assert(gd_disc.get_denumire() == "Analiza");
	assert(gd_disc.get_ore() == 4);
	assert(gd_disc.get_tip() == "Mate");
	assert(gd_disc.get_profesor() == "Berinde");

	string txt = "Denumire: Analiza | NrOre: 4 | Tip: Mate | Prof: Berinde";
	string csv = "Analiza,4,Mate,Berinde";
	assert(gd_disc.to_string() == txt);
	assert(gd_disc.to_csv() == csv);
	assert(Disciplina::from_csv(csv) == gd_disc);

	MyException exeption;
	assert(exeption.get_type() == "");
}

void Teste::test_validator_of_entity()
{
	Disciplina gd_disc = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina bd_disc = Disciplina("", -1, "", "");

	EXEPTION_WAS_NOT_THROWN(Validator::valideaza_disciplina(gd_disc));
	EXEPTION_WAS_THROWN(Validator::valideaza_disciplina(bd_disc))
}

void Teste::test_mylist()
{
	Disciplina disc1 = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina disc2 = Disciplina("Analiza", 4, "Mate", "Berinde");
	Disciplina disc3 = Disciplina("Logica", 4, "Logica", "Pop");
	InMemoryRepository list;

	list.add_to_list(disc1);
	list.add_to_list(disc2);
	list.add_to_list(disc3);
	assert(list.size_of_list() == 3);
	assert(list.take_from_list_name_search("ASC") == disc1);
	EXEPTION_WAS_THROWN(list.add_to_list(disc2));
	EXEPTION_WAS_THROWN(list.take_from_list_name_search("BDM") == disc1);

	list.delete_from_list(disc2);
	assert(list.size_of_list() == 2);
	EXEPTION_WAS_THROWN(list.delete_from_list(disc2));

	list.modify_from_list(disc3, disc2);
	assert(list.get_all().at(1) == disc2);
	//_____________________________________________________________
	Disciplina disc12 = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina disc22 = Disciplina("Analiza", 4, "Mate", "Berinde");
	Disciplina disc32 = Disciplina("Logica", 4, "Logica", "Pop");
	InFileRepository list2("test.csv");

	assert(list2.size_of_list() == 3);
	assert(list2.take_from_list_name_search("ASC") == disc12);
	EXEPTION_WAS_THROWN(list2.add_to_list(disc22));
	EXEPTION_WAS_THROWN(list2.take_from_list_name_search("BDM") == disc12);

	list2.delete_from_list(disc22);
	assert(list2.size_of_list() == 2);
	EXEPTION_WAS_THROWN(list2.delete_from_list(disc22));

	list2.modify_from_list(disc32, disc22);
	assert(list2.get_all().at(1) == disc22);
	list2.add_to_list(disc32);
}

void Teste::test_Adauga()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("ASM", 4, "Mate", "Vancea");
	assert(controller.GetAll().size() == 2);
	assert(controller.GetAll().at(0) == Disciplina("ASC", 5, "Info", "Vancea"));
	EXEPTION_WAS_THROWN(controller.Adauga("", -1, "", ""));

	assert(controller.Cauta("ASC", 5, "Info", "Vancea"));
	assert(controller.cauta_dupa_nume("ASC") == Disciplina("ASC", 5, "Info", "Vancea"));
}

void Teste::test_Sterge()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("ASC", 5, "Info", "Vancea");
	assert(controller.GetAll().at(0) == Disciplina("ASC", 5, "Info", "Vancea"));
	controller.Sterge("ASC", 5, "Info", "Vancea");
	assert(controller.GetAll().size() == 0);
	EXEPTION_WAS_THROWN(controller.Sterge("ASC", 5, "Info", "Vancea"));
}

void Teste::test_Modifica()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("ASC", 5, "Info", "Vancea");
	assert(controller.GetAll().at(0) == Disciplina("ASC", 5, "Info", "Vancea"));
	EXEPTION_WAS_THROWN(controller.Modifica("ASC", 5, "Info", "Vancea", "ASC", 5, "Info", "Vancea"));
	controller.Modifica("ASC", 5, "Info", "Vancea", "Analiza", 4, "Mate", "Berinde");
	assert(controller.GetAll().at(0) == Disciplina("Analiza", 4, "Mate", "Berinde"));
}

void Teste::test_undo()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("ASM", 4, "Mate", "Vancea");

	controller.Sterge("ASC", 5, "Info", "Vancea");
	controller.Undo();

	controller.Modifica("ASC", 5, "Info", "Vancea", "ASMMS", 5, "Mate", "Vancea");
	controller.Undo();

	assert(controller.Undo() == true);
	assert(controller.GetAll().size() == 1);
	assert(controller.GetAll().at(0) == Disciplina("ASC", 5, "Info", "Vancea"));

	assert(controller.Undo() == true);
	assert(controller.GetAll().size() == 0);

	assert(controller.Undo() == false);
}

void Teste::test_filtare_ore()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("Analiza", 4, "Mate", "Berinde");
	controller.Adauga("Logica", 4, "Logica", "Pop");
	assert(controller.GetAll().size() == 3);

	assert(controller.filtrare_dupa_ore(4).size() == 2);
	assert(controller.filtrare_dupa_ore(5).size() == 1);
	assert(controller.filtrare_dupa_ore(6).size() == 0);
}

void Teste::test_filtare_prof()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("Analiza", 4, "Mate", "Berinde");
	controller.Adauga("Logica", 4, "Logica", "Berinde");
	assert(controller.GetAll().size() == 3);

	assert(controller.filtrare_dupa_prof("Berinde").size() == 2);
	assert(controller.filtrare_dupa_prof("Vancea").size() == 1);
	assert(controller.filtrare_dupa_prof("Pop").size() == 0);
}

void Teste::test_sortare()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("Logica", 4, "Logica", "Logica");
	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("Analiza", 4, "Mate", "Berinde");

	assert(controller.Sortare(Service::ComparareDupaDenumire).at(0)
		== Disciplina("ASC", 5, "Info", "Vancea"));
	assert(controller.Sortare(Service::ComparareDupaDenumire).at(1)
		== Disciplina("Analiza", 4, "Mate", "Berinde"));
	assert(controller.Sortare(Service::ComparareDupaDenumire).at(2)
		== Disciplina("Logica", 4, "Logica", "Logica"));

	assert(controller.Sortare(Service::ComparareDupaOre).at(2)
		== Disciplina("ASC", 5, "Info", "Vancea"));

	controller.Adauga("Analiza", 6, "Mate", "Andreea");

	assert(controller.Sortare(Service::ComparareDupaTipProf).at(2)
		== Disciplina("Analiza", 6, "Mate", "Andreea"));
	assert(controller.Sortare(Service::ComparareDupaTipProf).at(3)
		== Disciplina("Analiza", 4, "Mate", "Berinde"));
	assert(controller.Sortare(Service::ComparareDupaTipProf).at(0)
		== Disciplina("ASC", 5, "Info", "Vancea"));
	assert(controller.Sortare(Service::ComparareDupaTipProf).at(1)
		== Disciplina("Logica", 4, "Logica", "Logica"));
}

void Teste::test_add_contract()
{
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	Disciplina disc1("ASC", 5, "Info", "Vancea");
	Disciplina disc2("ASM", 4, "Mate", "Vancea");

	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("ASM", 4, "Mate", "Vancea");
	controller.Adauga_disc_in_contract("ASM");
	EXEPTION_WAS_THROWN(controller.Adauga_disc_in_contract("FCSB"));
	EXEPTION_WAS_THROWN(controller.Adauga_disc_in_contract("ASM"));
	assert(contract.get_all().at(0) == disc2);

	controller.Curata_contract();
	assert(contract.get_all().size() == 0);

	const int status = controller.Genereaza_contract(5);
	assert(status == 2);
	assert(controller.GetAllContract().size() == 2);

	controller.Exporta_contract("exportedfile.csv");
	EXEPTION_WAS_THROWN(controller.Exporta_contract("exportedfilenu.txt"));
}

void Teste::test_contract()
{
	Disciplina disc1 = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina disc2 = Disciplina("Analiza", 4, "Mate", "Berinde");
	Disciplina disc3 = Disciplina("Logica", 4, "Logica", "Pop");
	Contract list;

	list.add_to_list(disc1);
	list.add_to_list(disc2);
	list.add_to_list(disc3);
	assert(list.size_of_list() == 3);
	EXEPTION_WAS_THROWN(list.add_to_list(disc2));

	list.delete_from_list(disc2);
	assert(list.size_of_list() == 2);
	EXEPTION_WAS_THROWN(list.delete_from_list(disc2));

	list.modify_from_list(disc3, disc2);
	assert(list.get_all().at(1) == disc2);
	list.clear_contract();
	assert(list.size_of_list() == 0);
}

void Teste::test_dictionar()
{
	Disciplina disc1 = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina disc2 = Disciplina("Analiza", 4, "Mate", "Berinde");
	Disciplina disc3 = Disciplina("Logica", 4, "Logica", "Pop");
	
	InMemoryRepository list;
	Contract contract;
	Service controller(list, contract);

	controller.Adauga("Logica", 4, "Logica", "Logica");
	controller.Adauga("Logicamea", 4, "Logica", "Logica");
	controller.Adauga("Logicata", 4, "Logica", "Logica");
	controller.Adauga("ASC", 5, "Info", "Vancea");
	controller.Adauga("Analiza", 4, "Mate", "Berinde");
	controller.Adauga("Bengaleza", 4, "Mate", "Berinde");

	map<string, int> testmap = controller.Creeaza_dictionar();
	assert(testmap.size() == 3);
	assert(testmap.at("Logica") == 3);
	assert(testmap.at("Mate") == 2);
	assert(testmap.at("Info") == 1);
}

void Teste::test_repo_dictionar()
{
	Disciplina disc1 = Disciplina("ASC", 5, "Info", "Vancea");
	Disciplina disc2 = Disciplina("Analiza", 4, "Mate", "Berinde");
	Disciplina disc3 = Disciplina("Logica", 4, "Logica", "Pop");
	DictRepository list(0.0);
	
	try {
		list.add_to_list(disc1);
		list.add_to_list(disc2);
		list.add_to_list(disc3);
		assert(list.size_of_list() == 3);
		assert(list.take_from_list_name_search("ASC") == disc1);
		EXEPTION_WAS_THROWN(list.add_to_list(disc2));
		EXEPTION_WAS_THROWN(list.take_from_list_name_search("BDM") == disc1);

		list.delete_from_list(disc2);
		assert(list.size_of_list() == 2);
		EXEPTION_WAS_THROWN(list.delete_from_list(disc2));

		list.modify_from_list(disc3, disc2);
		assert(list.get_all().at(1) == disc2);
	}
	catch (MyException& ex) {
		std::cout << ex.get_type() << ex.what();
	}
}

//void Teste::test_vector()
//{
//	int a = 1, b = 2, c = 3;
//	MyVector<int> v;
//	assert(v.get_size() == 0);
//	v.add(a);
//	v.add(b);
//	v.add(c);
//	assert(v.get_size() == 3);
//	MyVector<int> vcopie = v;
//	assert(vcopie.get_size() == 3);
//	assert(vcopie[2] == 3);
//	MyVector<int> valtul;
//	valtul = v;
//	v = v;
//	const int ci = 4;
//	v.add(ci);
//	assert(v[3] == ci);
//	IteratorVector<int> i(v, 2);
//	assert(*i == 3);
//
//	v.erase(i);
//	assert(v.get_size() == 3);
//	assert(v[0] == 1 && v[1] == 2 && v[2] == 4);
//	IteratorVector<int> i2 = v.begin();
//	assert(*i2 == 1);
//	IteratorVector<int> i3 = v.final();
//	assert(*i3 == 4);
//	++i;
//	assert(i.valid() == false);
//}
